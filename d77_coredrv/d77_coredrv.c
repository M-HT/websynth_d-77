/**
 *
 *  Copyright (C) 2022-2025 Roman Pauer
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of
 *  this software and associated documentation files (the "Software"), to deal in
 *  the Software without restriction, including without limitation the rights to
 *  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 *  of the Software, and to permit persons to whom the Software is furnished to do
 *  so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 */

#include <AvailabilityMacros.h>
#include <AudioToolbox/AudioToolbox.h>
#include <CoreMIDI/CoreMIDI.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/mman.h>
#include <pwd.h>
#include <libproc.h>
#include <signal.h>
#include <spawn.h>
#include <crt_externs.h>
#include "websynth.h"

#if defined(MAC_OS_VERSION_11_0) && MAC_OS_X_VERSION_MAX_ALLOWED >= MAC_OS_VERSION_11_0
#if MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_VERSION_11_0
#define MIDI_API 0
#else
#define MIDI_API 1
#endif
#else
#define MIDI_API -1
#endif


#define MIDI_NAME "WebSynth D-77"

static const uint32_t midi_name_crc32 = 0x399ef0ef;

static MIDIClientRef midi_client;
static MIDIEndpointRef midi_endpoint;
static AudioQueueRef midi_pcm_queue;
static volatile int midi_event_written;

static D77_SETINGS d77_settings;
static int daemonize;
static const char *data_filepath = "dswebWDM.dat";
#ifdef INDIRECT_64BIT
static const char *lib_filepath = "d77_lib.so";
#endif

static int datafile_len;
static uint8_t *datafile_ptr;

static unsigned int frequency, num_channels, bytes_per_call, samples_per_call, num_subbuffers, subbuf_counter;

#ifdef INDIRECT_64BIT
static uint8_t *midi_buffer;
static uint32_t *event_buffer;
#else
static uint32_t event_buffer[32768 + 16384];
#endif
static struct AudioQueueBuffer **midi_queue_buffer;

static volatile int event_read_index;
static volatile int event_write_index;


static void write_short_event(uint32_t event)
{
    int read_index, write_index;
    unsigned int free_space;

    // read global volatile variables to local variables
    read_index = event_read_index;
    write_index = event_write_index;

    if (write_index >= read_index)
    {
        free_space = 32767 - (write_index - read_index);
    }
    else
    {
        free_space = (read_index - write_index) - 1;
    }

    if (free_space == 0)
    {
        fprintf(stderr, "Event buffer overflow\n");
        return;
    }

    // write event to event buffer
    event_buffer[write_index] = event;
    write_index = (write_index + 1) & 0x7fff;

    // update global volatile variable
    event_write_index = write_index;

    midi_event_written = 1;
}

#if (MIDI_API <= 0)
static void write_long_event(const uint8_t *event, unsigned int length)
{
    int read_index, write_index;
    unsigned int free_space, len2;

    // read global volatile variables to local variables
    read_index = event_read_index;
    write_index = event_write_index;

    if (write_index >= read_index)
    {
        free_space = 32767 - (write_index - read_index);
    }
    else
    {
        free_space = (read_index - write_index) - 1;
    }

    len2 = 1 + ((length + 3) >> 2);

    if ((len2 > free_space) || (length >= 65536))
    {
        fprintf(stderr, "Event buffer overflow\n");
        return;
    }

    // write event to event buffer
    event_buffer[write_index] = 0xff000000 | length;
    write_index = (write_index + 1) & 0x7fff;

    if ((write_index >= read_index) && (length > (32768 - write_index) << 2))
    {
        // WebSynth D-77 doesn't support sysex fragments
        // instead of splitting the sysex into two parts, continue writing the second part into extra provided area

        memcpy(&(event_buffer[write_index]), event, length);
        write_index = 0;
    }
    else
    {
        memcpy(&(event_buffer[write_index]), event, length);
        write_index = (write_index + ((length + 3) >> 2)) & 0x7fff;
    }

    // update global volatile variable
    event_write_index = write_index;

    midi_event_written = 1;
}

static void midi_read_proc(const MIDIPacketList *pktlist, void * __nullable readProcRefCon, void * __nullable srcConnRefCon)
{
    unsigned int index1, index2;
    const MIDIPacket *packet;

    for (index1 = 0, packet = pktlist->packet; index1 < pktlist->numPackets; index1++, packet = MIDIPacketNext(packet))
    {
        for (index2 = 0; index2 < packet->length; index2++)
        {
            switch ((packet->data[index2] >> 4) & 0x0f) // status
            {
                case 0x08:
                    write_short_event(packet->data[index2] | ((packet->data[index2 + 1] & 0x7f) << 8) | ((packet->data[index2 + 2] & 0x7f) << 16));

#ifdef PRINT_EVENTS
                    printf("Note OFF, channel:%d note:%d velocity:%d\n", packet->data[index2] & 0x0f, packet->data[index2 + 1] & 0x7f, packet->data[index2 + 2] & 0x7f);
#endif

                    index2 += 2;
                    break;

                case 0x09:
                    write_short_event(packet->data[index2] | ((packet->data[index2 + 1] & 0x7f) << 8) | ((packet->data[index2 + 2] & 0x7f) << 16));

#ifdef PRINT_EVENTS
                    printf("Note ON, channel:%d note:%d velocity:%d\n", packet->data[index2] & 0x0f, packet->data[index2 + 1] & 0x7f, packet->data[index2 + 2] & 0x7f);
#endif

                    index2 += 2;
                    break;

                case 0x0a:
                    // Not used by WebSynth D-77
#if 0
                    write_short_event(packet->data[index2] | ((packet->data[index2 + 1] & 0x7f) << 8) | ((packet->data[index2 + 2] & 0x7f) << 16));
#endif

#ifdef PRINT_EVENTS
                    printf("Keypress, channel:%d note:%d velocity:%d\n", packet->data[index2] & 0x0f, packet->data[index2 + 1] & 0x7f, packet->data[index2 + 2] & 0x7f);
#endif

                    index2 += 2;
                    break;

                case 0x0b:
                    write_short_event(packet->data[index2] | ((packet->data[index2 + 1] & 0x7f) << 8) | ((packet->data[index2 + 2] & 0x7f) << 16));

#ifdef PRINT_EVENTS
                    printf("Controller, channel:%d param:%d value:%d\n", packet->data[index2] & 0x0f, packet->data[index2 + 1] & 0x7f, packet->data[index2 + 2] & 0x7f);
#endif

                    index2 += 2;
                    break;

                case 0x0c:
                    write_short_event(packet->data[index2] | ((packet->data[index2 + 1] & 0x7f) << 8));

#ifdef PRINT_EVENTS
                    printf("Program change, channel:%d value:%d\n", packet->data[index2] & 0x0f, packet->data[index2 + 1] & 0x7f);
#endif

                    index2++;
                    break;

                case 0x0d:
                    write_short_event(packet->data[index2] | ((packet->data[index2 + 1] & 0x7f) << 8));

#ifdef PRINT_EVENTS
                    printf("Channel pressure, channel:%d value:%d\n", packet->data[index2] & 0x0f, packet->data[index2 + 1] & 0x7f);
#endif

                    index2++;
                    break;

                case 0x0e:
                    write_short_event(packet->data[index2] | ((packet->data[index2 + 1] & 0x7f) << 8) | ((packet->data[index2 + 2] & 0x7f) << 16));

#ifdef PRINT_EVENTS
                    printf("Pitch bend, channel:%d value:%d\n", packet->data[index2] & 0x0f, ((packet->data[index2 + 1] & 0x7f) | ((packet->data[index2 + 2] & 0x7f) << 7)) - 0x2000);
#endif

                    index2 += 2;
                    break;

                case 0x0f:
                    switch (packet->data[index2])
                    {
                        case 0xf0:
                            // WebSynth D-77 doesn't support sysex fragments
                            write_long_event(packet->data + index2, packet->length - index2);

#ifdef PRINT_EVENTS
                            printf("SysEx (fragment), length:%d\n", packet->length - index2);
#endif

                            index2 = packet->length - 1;
                            break;

                        case 0xf1:
                            // Not used by WebSynth D-77
#if 0
                            write_short_event(packet->data[index2] | ((packet->data[index2 + 1] & 0x7f) << 8));
#endif

#ifdef PRINT_EVENTS
                            printf("MTC Quarter Frame, value:%d\n", packet->data[index2 + 1] & 0x7f);
#endif

                            index2++;
                            break;

                        case 0xf2:
                            // Not used by WebSynth D-77
#if 0
                            write_short_event(packet->data[index2] | ((packet->data[index2 + 1] & 0x7f) << 8) | ((packet->data[index2 + 2] & 0x7f) << 16));
#endif

#ifdef PRINT_EVENTS
                            printf("Song Position, value:%d\n", ((packet->data[index2 + 1] & 0x7f) | ((packet->data[index2 + 2] & 0x7f) << 7)) - 0x2000);
#endif

                            index2 += 2;
                            break;

                        case 0xf3:
                            // Not used by WebSynth D-77
#if 0
                            write_short_event(packet->data[index2] | ((packet->data[index2 + 1] & 0x7f) << 8));
#endif

#ifdef PRINT_EVENTS
                            printf("Song Select, value:%d\n", packet->data[index2 + 1] & 0x7f);
#endif

                            index2++;
                            break;

                        case 0xf6:
                            // Not used by WebSynth D-77
#if 0
                            write_short_event(packet->data[index2]);
#endif

#ifdef PRINT_EVENTS
                            printf("Tune Request\n");
#endif

                            break;

                        case 0xf8:
                            // Not used by WebSynth D-77
#if 0
                            write_short_event(packet->data[index2]);
#endif

#ifdef PRINT_EVENTS
                            printf("Clock\n");
#endif

                            break;

                        case 0xfa:
                            // Not used by WebSynth D-77
#if 0
                            write_short_event(packet->data[index2]);
#endif

#ifdef PRINT_EVENTS
                            printf("Start\n");
#endif

                            break;

                        case 0xfb:
                            // Not used by WebSynth D-77
#if 0
                            write_short_event(packet->data[index2]);
#endif

#ifdef PRINT_EVENTS
                            printf("Continue\n");
#endif

                            break;

                        case 0xfc:
                            // Not used by WebSynth D-77
#if 0
                            write_short_event(packet->data[index2]);
#endif

#ifdef PRINT_EVENTS
                            printf("Stop\n");
#endif

                            break;

                        case 0xfe:
                            // Not used by WebSynth D-77
#if 0
                            write_short_event(packet->data[index2]);
#endif

#ifdef PRINT_EVENTS
                            printf("Active Sense\n");
#endif

                            break;

                        case 0xff:
                            // Not used by WebSynth D-77
#if 0
                            write_short_event(packet->data[index2]);
#endif

#ifdef PRINT_EVENTS
                            printf("Reset\n");
#endif

                            break;

                        default:
                            fprintf(stderr, "Unhandled system message: 0x%x\n", packet->data[index2]);
                            break;
                    }
                    break;
                default:
                    if (index2 == 0)
                    {
                        // WebSynth D-77 doesn't support sysex fragments
#if 0
                        write_long_event(packet->data, packet->length);
#endif

#ifdef PRINT_EVENTS
                        printf("SysEx (fragment) of size %d\n", length);
#endif

                        index2 = packet->length - 1;
                    }
                    else
                    {
                        fprintf(stderr, "Unhandled message: 0x%x\n", packet->data[index2]);
                    }
                    break;
            }
        }
    }
}
#endif

#if (MIDI_API >= 0)
static uint8_t *write_long_event_prepare(unsigned int length)
{
    int read_index, write_index;
    unsigned int free_space, len2;

    // read global volatile variables to local variables
    read_index = event_read_index;
    write_index = event_write_index;

    if (write_index >= read_index)
    {
        free_space = 32767 - (write_index - read_index);
    }
    else
    {
        free_space = (read_index - write_index) - 1;
    }

    len2 = 1 + ((length + 3) >> 2);

    if ((len2 > free_space) || (length >= 65536))
    {
        fprintf(stderr, "Event buffer overflow\n");
        return NULL;
    }

    // write event to event buffer
    event_buffer[write_index] = 0xff000000 | length;
    write_index = (write_index + 1) & 0x7fff;

    return (uint8_t *)&(event_buffer[write_index]);
}

static void write_long_event_finish(unsigned int length)
{
    int read_index, write_index;

    // read global volatile variables to local variables
    read_index = event_read_index;
    write_index = event_write_index;

    // write event to event buffer
    write_index = (write_index + 1) & 0x7fff;

    if ((write_index >= read_index) && (length > (32768 - write_index) << 2))
    {
        // WebSynth D-77 doesn't support sysex fragments
        // instead of splitting the sysex into two parts, continue writing the second part into extra provided area
        write_index = 0;
    }
    else
    {
        write_index = (write_index + ((length + 3) >> 2)) & 0x7fff;
    }

    // update global volatile variable
    event_write_index = write_index;

    midi_event_written = 1;
}


static void midi_receive_proc(const MIDIEventList *evtlist, void * __nullable srcConnRefCon)
{
    unsigned int index1, index2, length, num_data_packets, index3;
    uint8_t *data;
    const MIDIEventPacket *packet;

    for (index1 = 0, packet = evtlist->packet; index1 < evtlist->numPackets; index1++, packet = MIDIEventPacketNext(packet))
    {
        for (index2 = 0; index2 < packet->wordCount; index2++)
        {
            switch ((packet->words[index2] >> 28) & 0x0f) // message type
            {
                // Traditional MIDI 1.0 Functionality
                case kMIDIMessageTypeSystem:
                    switch ((packet->words[index2] >> 16) & 0xff) // status
                    {
                        case kMIDIStatusMTC:
                            // Not used by WebSynth D-77
#if 0
                            if (((packet->words[index2] >> 24) & 0x0f) == 0) // group
                            {
                                write_short_event(0xF1 | (packet->words[index2] & 0x7f00));
                            }
#endif

#ifdef PRINT_EVENTS
                            printf("MTC Quarter Frame, group:%d value:%d\n", (packet->words[index2] >> 24) & 0x0f, (packet->words[index2] >> 8) & 0x7f);
#endif

                            break;

                        case kMIDIStatusSongPosPointer:
                            // Not used by WebSynth D-77
#if 0
                            if (((packet->words[index2] >> 24) & 0x0f) == 0) // group
                            {
                                write_short_event(0xF2 | (packet->words[index2] & 0x7f00) | ((packet->words[index2] & 0x7f) << 16));
                            }
#endif

#ifdef PRINT_EVENTS
                            printf("Song Position, group:%d value:%d\n", (packet->words[index2] >> 24) & 0x0f, (((packet->words[index2] >> 8) & 0x7f) | ((packet->words[index2] & 0x7f) << 7)) - 0x2000);
#endif

                            break;

                        case kMIDIStatusSongSelect:
                            // Not used by WebSynth D-77
#if 0
                            if (((packet->words[index2] >> 24) & 0x0f) == 0) // group
                            {
                                write_short_event(0xF3 | (packet->words[index2] & 0x7f00));
                            }
#endif

#ifdef PRINT_EVENTS
                            printf("Song Select, group:%d value:%d\n", (packet->words[index2] >> 24) & 0x0f, (packet->words[index2] >> 8) & 0x7f);
#endif

                            break;

                        case kMIDIStatusTuneRequest:
                            // Not used by WebSynth D-77
#if 0
                            if (((packet->words[index2] >> 24) & 0x0f) == 0) // group
                            {
                                write_short_event(0xF6);
                            }
#endif

#ifdef PRINT_EVENTS
                            printf("Tune Request, group:%d\n", (packet->words[index2] >> 24) & 0x0f);
#endif

                            break;

                        case kMIDIStatusTimingClock:
                            // Not used by WebSynth D-77
#if 0
                            if (((packet->words[index2] >> 24) & 0x0f) == 0) // group
                            {
                                write_short_event(0xF8);
                            }
#endif

#ifdef PRINT_EVENTS
                            printf("Clock, group:%d\n", (packet->words[index2] >> 24) & 0x0f);
#endif

                            break;

                        case kMIDIStatusStart:
                            // Not used by WebSynth D-77
#if 0
                            if (((packet->words[index2] >> 24) & 0x0f) == 0) // group
                            {
                                write_short_event(0xFA);
                            }
#endif

#ifdef PRINT_EVENTS
                            printf("Start, group:%d\n", (packet->words[index2] >> 24) & 0x0f);
#endif

                            break;

                        case kMIDIStatusContinue:
                            // Not used by WebSynth D-77
#if 0
                            if (((packet->words[index2] >> 24) & 0x0f) == 0) // group
                            {
                                write_short_event(0xFB);
                            }
#endif

#ifdef PRINT_EVENTS
                            printf("Continue, group:%d\n", (packet->words[index2] >> 24) & 0x0f);
#endif

                            break;

                        case kMIDIStatusStop:
                            // Not used by WebSynth D-77
#if 0
                            if (((packet->words[index2] >> 24) & 0x0f) == 0) // group
                            {
                                write_short_event(0xFC);
                            }
#endif

#ifdef PRINT_EVENTS
                            printf("Stop, group:%d\n", (packet->words[index2] >> 24) & 0x0f);
#endif

                            break;

                        case kMIDIStatusActiveSending:
                            // Not used by WebSynth D-77
#if 0
                            if (((packet->words[index2] >> 24) & 0x0f) == 0) // group
                            {
                                write_short_event(0xFE);
                            }
#endif

#ifdef PRINT_EVENTS
                            printf("Active Sense, group:%d\n", (packet->words[index2] >> 24) & 0x0f);
#endif

                            break;

                        case kMIDIStatusSystemReset:
                            // Not used by WebSynth D-77
#if 0
                            if (((packet->words[index2] >> 24) & 0x0f) == 0) // group
                            {
                                write_short_event(0xFF);
                            }
#endif

#ifdef PRINT_EVENTS
                            printf("Reset, group:%d\n", (packet->words[index2] >> 24) & 0x0f);
#endif

                            break;

                        default:
                            fprintf(stderr, "Unhandled system message: 0x%x, group:%d\n", (packet->words[index2] >> 16) & 0xff, (packet->words[index2] >> 24) & 0x0f);
                            break;
                    }
                    break;

                case kMIDIMessageTypeChannelVoice1:
                    switch ((packet->words[index2] >> 20) & 0x0f) // status
                    {
                        case kMIDICVStatusNoteOff:
                            if (((packet->words[index2] >> 24) & 0x0f) == 0) // group
                            {
                                write_short_event(((packet->words[index2] >> 16) & 0xff) | (packet->words[index2] & 0x7f00) | ((packet->words[index2] & 0x7f) << 16));
                            }

#ifdef PRINT_EVENTS
                            printf("Note OFF, group:%d channel:%d note:%d velocity:%d\n", (packet->words[index2] >> 24) & 0x0f, (packet->words[index2] >> 16) & 0x0f, (packet->words[index2] >> 8) & 0x7f, packet->words[index2] & 0x7f);
#endif

                            break;

                        case kMIDICVStatusNoteOn:
                            if (((packet->words[index2] >> 24) & 0x0f) == 0) // group
                            {
                                write_short_event(((packet->words[index2] >> 16) & 0xff) | (packet->words[index2] & 0x7f00) | ((packet->words[index2] & 0x7f) << 16));
                            }

#ifdef PRINT_EVENTS
                            printf("Note ON, group:%d channel:%d note:%d velocity:%d\n", (packet->words[index2] >> 24) & 0x0f, (packet->words[index2] >> 16) & 0x0f, (packet->words[index2] >> 8) & 0x7f, packet->words[index2] & 0x7f);
#endif

                            break;

                        case kMIDICVStatusPolyPressure:
                            // Not used by WebSynth D-77
#if 0
                            if (((packet->words[index2] >> 24) & 0x0f) == 0) // group
                            {
                                write_short_event(((packet->words[index2] >> 16) & 0xff) | (packet->words[index2] & 0x7f00) | ((packet->words[index2] & 0x7f) << 16));
                            }
#endif

#ifdef PRINT_EVENTS
                            printf("Keypress, group:%d channel:%d note:%d velocity:%d\n", (packet->words[index2] >> 24) & 0x0f, (packet->words[index2] >> 16) & 0x0f, (packet->words[index2] >> 8) & 0x7f, packet->words[index2] & 0x7f);
#endif

                            break;

                        case kMIDICVStatusControlChange:
                            if (((packet->words[index2] >> 24) & 0x0f) == 0) // group
                            {
                                write_short_event(((packet->words[index2] >> 16) & 0xff) | (packet->words[index2] & 0x7f00) | ((packet->words[index2] & 0x7f) << 16));
                            }

#ifdef PRINT_EVENTS
                            printf("Controller, group:%d channel:%d param:%d value:%d\n", (packet->words[index2] >> 24) & 0x0f, (packet->words[index2] >> 16) & 0x0f, (packet->words[index2] >> 8) & 0x7f, packet->words[index2] & 0x7f);
#endif

                            break;

                        case kMIDICVStatusProgramChange:
                            if (((packet->words[index2] >> 24) & 0x0f) == 0) // group
                            {
                                write_short_event(((packet->words[index2] >> 16) & 0xff) | (packet->words[index2] & 0x7f00));
                            }

#ifdef PRINT_EVENTS
                            printf("Program change, group:%d channel:%d value:%d\n", (packet->words[index2] >> 24) & 0x0f, (packet->words[index2] >> 16) & 0x0f, (packet->words[index2] >> 8) & 0x7f);
#endif

                            break;

                        case kMIDICVStatusChannelPressure:
                            if (((packet->words[index2] >> 24) & 0x0f) == 0) // group
                            {
                                write_short_event(((packet->words[index2] >> 16) & 0xff) | (packet->words[index2] & 0x7f00));
                            }

#ifdef PRINT_EVENTS
                            printf("Channel pressure, group:%d channel:%d value:%d\n", (packet->words[index2] >> 24) & 0x0f, (packet->words[index2] >> 16) & 0x0f, (packet->words[index2] >> 8) & 0x7f);
#endif

                            break;

                        case kMIDICVStatusPitchBend:
                            if (((packet->words[index2] >> 24) & 0x0f) == 0) // group
                            {
                                write_short_event(((packet->words[index2] >> 16) & 0xff) | (packet->words[index2] & 0x7f00) | ((packet->words[index2] & 0x7f) << 16));
                            }

#ifdef PRINT_EVENTS
                            printf("Pitch bend, group:%d channel:%d value:%d\n", (packet->words[index2] >> 24) & 0x0f, (packet->words[index2] >> 16) & 0x0f, (((packet->words[index2] >> 8) & 0x7f) | ((packet->words[index2] & 0x7f) << 7)) - 0x2000);
#endif

                            break;

                        default:
                            fprintf(stderr, "Unhandled channel voice message: 0x%x, group:%d\n", (packet->words[index2] >> 16) & 0xff, (packet->words[index2] >> 24) & 0x0f);
                            break;
                    }
                    break;

                case kMIDIMessageTypeSysEx:
                    if (((packet->words[index2] >> 24) & 0x0f) == 0) // group
                    {
                        length = 0;
                        num_data_packets = 0;
                        do
                        {
                            length += (packet->words[index2 + num_data_packets * 2] >> 16) & 0x0f;
                            switch ((packet->words[index2 + num_data_packets * 2] >> 20) & 0x0f)
                            {
                                case kMIDISysExStatusComplete:
                                    length += 2;
                                    break;
                                case kMIDISysExStatusStart:
                                case kMIDISysExStatusEnd:
                                    length++;
                                    break;
                                default:
                                    break;
                            }
                            num_data_packets++;
                        } while (index2 + num_data_packets * 2 < packet->wordCount && ((packet->words[index2 + num_data_packets * 2] >> 28) & 0x0f) == kMIDIMessageTypeSysEx && (((packet->words[index2 + num_data_packets * 2] >> 24) & 0x0f) == 0));

                        data = write_long_event_prepare(length);
                        if (data != NULL)
                        {
                            for (index3 = 0; index3 < num_data_packets; index3++)
                            {
                                if (((packet->words[index2 + index3 * 2] >> 20) & 0x0f) == kMIDISysExStatusComplete || ((packet->words[index2 * 2] >> 20) & 0x0f) == kMIDISysExStatusStart)
                                {
                                    *data = 0xf0;
                                    data++;
                                }

                                switch ((packet->words[index2 + index3 * 2] >> 16) & 0x0f)
                                {
                                    case 6:
                                        data[5] = packet->words[index2 + index3 * 2 + 1] & 0x7f;
                                        // fallthrough
                                    case 5:
                                        data[4] = (packet->words[index2 + index3 * 2 + 1] >> 8) & 0x7f;
                                        // fallthrough
                                    case 4:
                                        data[3] = (packet->words[index2 + index3 * 2 + 1] >> 16) & 0x7f;
                                        // fallthrough
                                    case 3:
                                        data[2] = (packet->words[index2 + index3 * 2 + 1] >> 24) & 0x7f;
                                        // fallthrough
                                    case 2:
                                        data[1] = packet->words[index2 + index3 * 2] & 0x7f;
                                        // fallthrough
                                    case 1:
                                        data[0] = (packet->words[index2 + index3 * 2] >> 8) & 0x7f;
                                        // fallthrough
                                    case 0:
                                    default:
                                        break;
                                }

                                data += (packet->words[index2 + index3 * 2] >> 16) & 0x0f;

                                if (((packet->words[index2 + index3 * 2] >> 20) & 0x0f) == kMIDISysExStatusComplete || ((packet->words[index2 * 2] >> 20) & 0x0f) == kMIDISysExStatusEnd)
                                {
                                    *data = 0xf7;
                                    data++;
                                }
                            }

                            write_long_event_finish(length);
                        }

                        index2 += num_data_packets * 2 + 1;

#ifdef PRINT_EVENTS
                        printf("SysEx (fragment), group:%d length:%d\n", 0, length);
#endif
                    }
                    else
                    {
#ifdef PRINT_EVENTS
                        printf("SysEx (fragment), group:%d length:%d\n", (packet->words[index2] >> 24) & 0x0f, (packet->words[index2] >> 16) & 0x0f);
#endif
                        index2++;
                    }

                    break;

                // other types - 1 word
                case kMIDIMessageTypeUtility:
                case 6:
                case 7:
                default:
                    fprintf(stderr, "Unhandled message type: %d\n", (packet->words[index2] >> 28) & 0x0f);
                    break;

                // other types - 2 words
                case kMIDIMessageTypeChannelVoice2:
                case 8:
                case 9:
                case 10:
                    fprintf(stderr, "Unhandled message type: %d\n", (packet->words[index2] >> 28) & 0x0f);
                    index2++;
                    break;

                // other types - 3 words
                case 11:
                case 12:
                    fprintf(stderr, "Unhandled message type: %d\n", (packet->words[index2] >> 28) & 0x0f);
                    index2 += 2;
                    break;

                // other types - 4 words
                case kMIDIMessageTypeData128:
                case 13:
                case 14:
                case 15:
                    fprintf(stderr, "Unhandled message type: %d\n", (packet->words[index2] >> 28) & 0x0f);
                    index2 += 3;
                    break;
            }
        }
    }
}
#endif


static void usage(const char *progname)
{
    static const char basename[] = "d77_coredrv";

    if (progname == NULL)
    {
        progname = basename;
    }
    else
    {
        const char *slash;

        slash = strrchr(progname, '/');
        if (slash != NULL)
        {
            progname = slash + 1;
        }
    }

    printf(
        "%s - WebSynth D-77\n"
        "Usage: %s [OPTIONS]...\n"
        "  -w PATH  Datafile path (path to dsweb*.dat)\n"
#ifdef INDIRECT_64BIT
        "  -b PATH  Library path (path to d77_lib.so)\n"
#endif
        "  -f NUM   Frequency (22050/44100 Hz)\n"
        "  -p NUM   Polyphony (8-256)\n"
        "  -m NUM   Master volume (0-200)\n"
        "  -r NUM   Reverb effect (0=off, 1=on)\n"
        "  -c NUM   Chorus effect (0=off, 1=on)\n"
        "  -l NUM   Cpu load (20-85)\n"
        "  -d       Daemonize\n"
        "  -h       Help\n"
        "Advanced parameters:\n"
        "  -aRevAdj NUM     (0-200)\n"
        "  -aChoAdj NUM     (0-200)\n"
        "  -aOutLev NUM     (0-200)\n"
        "  -aRevFb NUM      (0-200)\n"
        "  -aRevDrm NUM     (0-200)\n"
        "  -aResoUpAdj NUM  (0-100)\n",
        basename,
        progname
    );
    exit(1);
}

static void read_arguments(int argc, char *argv[]) __attribute__((noinline));
static void read_arguments(int argc, char *argv[])
{
    int i, j;

    // default settings from .ini file
    d77_settings.dwSamplingFreq = 44100;
    d77_settings.dwPolyphony = 64;
    d77_settings.dwCpuLoadL = 60;
    d77_settings.dwCpuLoadH = 90;
    d77_settings.dwRevSw = 1;
    d77_settings.dwChoSw = 1;
    d77_settings.dwMVol = 100;
    d77_settings.dwRevAdj = 95;
    d77_settings.dwChoAdj = 70;
    d77_settings.dwOutLev = 110;
    d77_settings.dwRevFb = 95;
    d77_settings.dwRevDrm = 80;
    d77_settings.dwResoUpAdj = 40;
    d77_settings.dwCacheSize = 3;
    d77_settings.dwTimeReso = 80;

    daemonize = 0;

    if (argc <= 1)
    {
        return;
    }

    for (i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-' && argv[i][1] != 0 && argv[i][2] == 0)
        {
            switch (argv[i][1])
            {
                case 'w': // data file
                    if ((i + 1) < argc)
                    {
                        i++;
                        data_filepath = argv[i];
                    }
                    break;
#ifdef INDIRECT_64BIT
                case 'b': // library
                    if ((i + 1) < argc)
                    {
                        i++;
                        lib_filepath = argv[i];
                    }
                    break;
#endif
                case 'f': // frequency
                    if ((i + 1) < argc)
                    {
                        i++;
                        j = atoi(argv[i]);
                        if (j == 22050 || j == 44100)
                        {
                            d77_settings.dwSamplingFreq = j;
                        }
                    }
                    break;
                case 'p': // polyphony
                    if ((i + 1) < argc)
                    {
                        i++;
                        j = atoi(argv[i]);
                        if (j >= 0)
                        {
                            d77_settings.dwPolyphony = j;
                        }
                    }
                    break;
                case 'm': // master volume
                    if ((i + 1) < argc)
                    {
                        i++;
                        j = atoi(argv[i]);
                        if (j >= 0 && j <= 200)
                        {
                            d77_settings.dwMVol = j;
                        }
                    }
                    break;
                case 'r': // reverb effect
                    if ((i + 1) < argc)
                    {
                        i++;
                        j = atoi(argv[i]);
                        if (j >= 0 && j <= 1)
                        {
                            d77_settings.dwRevSw = j;
                        }
                    }
                    break;
                case 'c': // chorus effect
                    if ((i + 1) < argc)
                    {
                        i++;
                        j = atoi(argv[i]);
                        if (j >= 0 && j <= 1)
                        {
                            d77_settings.dwChoSw = j;
                        }
                    }
                    break;
                case 'l': // cpu load
                    if ((i + 1) < argc)
                    {
                        i++;
                        j = atoi(argv[i]);
                        if (j >= 20 && j <= 85)
                        {
                            d77_settings.dwCpuLoadL = j;
                        }
                    }
                    break;
                case 'd': // daemonize
                    daemonize = 1;
                    break;
                case 'h': // help
                    usage(argv[0]);
                default:
                    break;
            }
        }
        else if (argv[i][0] == '-' && argv[i][1] == 'a')
        {
            if (0 == strcmp(argv[i] + 2, "RevAdj"))
            {
                if ((i + 1) < argc)
                {
                    i++;
                    j = atoi(argv[i]);
                    if (j >= 0 && j <= 200)
                    {
                        d77_settings.dwRevAdj = j;
                    }
                }
            }
            else if (0 == strcmp(argv[i] + 2, "ChoAdj"))
            {
                if ((i + 1) < argc)
                {
                    i++;
                    j = atoi(argv[i]);
                    if (j >= 0 && j <= 200)
                    {
                        d77_settings.dwChoAdj = j;
                    }
                }
            }
            else if (0 == strcmp(argv[i] + 2, "OutLev"))
            {
                if ((i + 1) < argc)
                {
                    i++;
                    j = atoi(argv[i]);
                    if (j >= 0 && j <= 200)
                    {
                        d77_settings.dwOutLev = j;
                    }
                }
            }
            else if (0 == strcmp(argv[i] + 2, "RevFb"))
            {
                if ((i + 1) < argc)
                {
                    i++;
                    j = atoi(argv[i]);
                    if (j >= 0 && j <= 200)
                    {
                        d77_settings.dwRevFb = j;
                    }
                }
            }
            else if (0 == strcmp(argv[i] + 2, "RevDrm"))
            {
                if ((i + 1) < argc)
                {
                    i++;
                    j = atoi(argv[i]);
                    if (j >= 0 && j <= 200)
                    {
                        d77_settings.dwRevDrm = j;
                    }
                }
            }
            else if (0 == strcmp(argv[i] + 2, "ResoUpAdj"))
            {
                if ((i + 1) < argc)
                {
                    i++;
                    j = atoi(argv[i]);
                    if (j >= 0 && j <= 100)
                    {
                        d77_settings.dwResoUpAdj = j;
                    }
                }
            }
        }
        else if (strcmp(argv[i], "--help") == 0)
        {
            usage(argv[0]);
        }
    }
}


static int run_as_daemon_start(char *argv[]) __attribute__((noinline));
static int run_as_daemon_start(char *argv[])
{
    pid_t pid;
    int res, err;
    struct sigaction chld_action;
    char pathbuf[PROC_PIDPATHINFO_MAXSIZE];

    // get current signal action for SIGCHLD
    sigaction(SIGCHLD, NULL, &chld_action);

    pid = getpid();
    if (chld_action.sa_handler != SIG_IGN || getpgrp() == pid)
    {
        // spawn a new process (current process is process group leader or signal handler for SIGCHLD is not SIG_IGN)

        signal(SIGCHLD, SIG_IGN);

        res = proc_pidpath(pid, pathbuf, sizeof(pathbuf));
        err = posix_spawn(NULL, (res > 0 && res < sizeof(pathbuf)) ? pathbuf : argv[0], NULL, NULL, argv, *_NSGetEnviron());
        if (err != 0)
        {
            fprintf(stderr, "Error spawning process: %i\n", err);
            return -1;
        }

        exit(0);
    }
    else
    {
        // create new session (current process is not process group leader and signal handler for SIGCHLD is SIG_IGN)

        if (setsid() < 0)
        {
            fprintf(stderr, "Error creating session\n");
            return -2;
        }
    }

    printf("Running as daemon...\n");

    return 0;
}

static void run_as_daemon_finish(void) __attribute__((noinline));
static void run_as_daemon_finish(void)
{
    freopen("/dev/null", "r", stdin);
    freopen("/dev/null", "w", stdout);
    freopen("/dev/null", "w", stderr);
}


static int load_data_file(void)
{
    int data_fd;
    off_t datalen;

    data_fd = open(data_filepath, O_RDONLY);
    if (data_fd < 0)
    {
        char *pathcopy, *slash, *filename;
        DIR *dir;
        struct dirent *entry;

        pathcopy = strdup(data_filepath);
        if (pathcopy == NULL) return -1;

        slash = strrchr(pathcopy, '/');
        if (slash != NULL)
        {
            filename = slash + 1;
            if (slash != pathcopy)
            {
                *slash = 0;
                dir = opendir(pathcopy);
                *slash = '/';
            }
            else
            {
                dir = opendir("/");
            }
        }
        else
        {
            filename = pathcopy;
            dir = opendir(".");
        }

        if (dir == NULL)
        {
            free(pathcopy);
            return -2;
        }

        while (1)
        {
            entry = readdir(dir);
            if (entry == NULL) break;

            if (entry->d_type != DT_UNKNOWN && entry->d_type != DT_REG && entry->d_type != DT_LNK) continue;

            if (0 != strcasecmp(filename, entry->d_name)) continue;

            strcpy(filename, entry->d_name);
            break;
        };

        closedir(dir);

        if (entry == NULL)
        {
            free(pathcopy);
            return -3;
        }

        data_fd = open(pathcopy, O_RDONLY);

        free(pathcopy);

        if (data_fd < 0)
        {
            return -4;
        }
    }

    datalen = lseek(data_fd, 0, SEEK_END);
    if (datalen <= 4)
    {
        close(data_fd);
        return -5;
    }

    if (0 != lseek(data_fd, 0, SEEK_SET))
    {
        close(data_fd);
        return -6;
    }

#ifdef INDIRECT_64BIT
    datafile_ptr = (uint8_t *)D77_AllocateMemory(datalen);
#else
    datafile_ptr = (uint8_t *)malloc(datalen);
#endif
    if (datafile_ptr == NULL)
    {
        close(data_fd);
        return -7;
    }

    datafile_len = datalen;

    while (datalen)
    {
        ssize_t read_bytes;

        read_bytes = read(data_fd, datafile_ptr + datafile_len - datalen, datalen);
        if (read_bytes <= 0) break;

        datalen -= read_bytes;
    }

    close(data_fd);

    if (datalen)
    {
#ifdef INDIRECT_64BIT
        D77_FreeMemory(datafile_ptr, datafile_len);
#else
        free(datafile_ptr);
#endif
        return -8;
    }

    return 0;
}

static void stop_synth(void) __attribute__((noinline));
static void stop_synth(void)
{
#ifdef INDIRECT_64BIT
    D77_FreeMemory(midi_buffer, 65536 + (32768 + 16384) * sizeof(uint32_t));
    D77_FreeMemory(datafile_ptr, datafile_len);
    D77_FreeLibrary();
#else
    free(datafile_ptr);
#endif
}

static int start_synth(void) __attribute__((noinline));
static int start_synth(void)
{
    D77_PARAMETERS *d77_parameters;

#ifdef INDIRECT_64BIT
    if (!D77_LoadLibrary(lib_filepath))
    {
        fprintf(stderr, "Error loading library: %s\n", lib_filepath);
        return -1;
    }
#endif

    if (load_data_file() < 0)
    {
        fprintf(stderr, "Error opening DATA file: %s\n", data_filepath);
        return -2;
    }

#ifdef INDIRECT_64BIT
    midi_buffer = (uint8_t *)D77_AllocateMemory(65536 + (32768 + 16384) * sizeof(uint32_t));
    if (midi_buffer == NULL)
    {
        stop_synth();
        fprintf(stderr, "Error allocating memory buffers\n");
        return -3;
    }
    event_buffer = (uint32_t *)(midi_buffer + 65536);
#endif

    // initialize D77
#ifdef INDIRECT_64BIT
    memcpy(event_buffer, &d77_settings, sizeof(D77_SETINGS));
    D77_ValidateSettings((D77_SETINGS *)event_buffer);
    memcpy(&d77_settings, event_buffer, sizeof(D77_SETINGS));
#else
    D77_ValidateSettings(&d77_settings);
#endif

    if (!D77_InitializeDataFile(datafile_ptr, datafile_len - 4))
    {
        stop_synth();
        fprintf(stderr, "Error initializing DATA file\n");
        return -4;
    }

    if (!D77_InitializeSynth(d77_settings.dwSamplingFreq, d77_settings.dwPolyphony, d77_settings.dwTimeReso))
    {
        stop_synth();
        fprintf(stderr, "Error initializing synth\n");
        return -5;
    }

    D77_InitializeUnknown(0);
    D77_InitializeEffect(D77_EFFECT_Reverb, d77_settings.dwRevSw ? 1 : 0);
    D77_InitializeEffect(D77_EFFECT_Chorus, d77_settings.dwChoSw ? 1 : 0);
    D77_InitializeCpuLoad(d77_settings.dwCpuLoadL, d77_settings.dwCpuLoadH);

    d77_parameters = (D77_PARAMETERS *)event_buffer;
    d77_parameters->wChoAdj = d77_settings.dwChoAdj;
    d77_parameters->wRevAdj = d77_settings.dwRevAdj;
    d77_parameters->wRevDrm = d77_settings.dwRevDrm;
    d77_parameters->wRevFb = d77_settings.dwRevFb;
    d77_parameters->wOutLev = d77_settings.dwOutLev;
    d77_parameters->wResoUpAdj = d77_settings.dwResoUpAdj;

    D77_InitializeParameters(d77_parameters);

    D77_InitializeMasterVolume(d77_settings.dwMVol);


    // prepare output buffer
    num_channels = 2;
    frequency = d77_settings.dwSamplingFreq;
    samples_per_call = D77_GetRenderedSamplesPerCall();
    bytes_per_call = samples_per_call * num_channels * sizeof(int16_t);

    num_subbuffers = (4096 * (int64_t)frequency) / (11025 * (int64_t)samples_per_call);
    if (num_subbuffers > 65536 / bytes_per_call)
    {
        num_subbuffers = 65536 / bytes_per_call;
    }
    if (num_subbuffers < 4)
    {
        stop_synth();
        fprintf(stderr, "Unsupported D77 parameters: %i, %i, %i\n", num_channels, frequency, samples_per_call);
        return -6;
    }


    // prepare variables
    event_read_index = 0;
    event_write_index = 0;
    subbuf_counter = 0;
#ifdef INDIRECT_64BIT
    memset(midi_buffer, 0, 65536);
#endif


    return 0;
}

static int drop_privileges(void)
{
    uid_t uid;
    gid_t gid;
    const char *sudo_id;
    long long int llid;
    struct passwd *passwdbuf;

    if (getuid() != 0)
    {
        return 0;
    }

    if (issetugid())
    {
        return -1;
    }

    sudo_id = getenv("SUDO_UID");
    if (sudo_id == NULL)
    {
        return -2;
    }

    errno = 0;
    llid = strtoll(sudo_id, NULL, 10);
    uid = (uid_t) llid;
    if (errno != 0 || uid == 0 || llid != (long long int)uid)
    {
        return -3;
    }

    gid = getgid();
    if (gid == 0)
    {
        sudo_id = getenv("SUDO_GID");
        if (sudo_id == NULL)
        {
            passwdbuf = getpwuid(uid);
            if (passwdbuf != NULL)
            {
                gid = passwdbuf->pw_gid;
            }

            if (gid == 0)
            {
                return -4;
            }
        }
        else
        {
            errno = 0;
            llid = strtoll(sudo_id, NULL, 10);
            gid = (gid_t) llid;
            if (errno != 0 || gid == 0 || llid != (long long int)gid)
            {
                return -5;
            }
        }
    }

    if (setgid(gid) != 0)
    {
        return -6;
    }
    if (setuid(uid) != 0)
    {
        return -7;
    }

    printf("Dropped root privileges\n");

    chdir("/");

    return 0;
}

static void handle_privileges(void) __attribute__((noinline));
static void handle_privileges(void)
{
    // try to increase priority (only root)
    setpriority(PRIO_PROCESS, 0, -20);

    if (drop_privileges() < 0)
    {
        fprintf(stderr, "Error dropping root privileges\n");
    }
}


static int render_subbuffer(int num)
{
    int read_index, write_index, length;

    // read global volatile variables to local variables
    read_index = event_read_index;
    write_index = event_write_index;

    if (read_index != write_index)
    {
        do
        {
            if (event_buffer[read_index] & 0xff000000)
            {
                length = event_buffer[read_index] & 0x00ffffff;
                read_index = (read_index + 1) & 0x7fff;

                if ((read_index >= write_index) && (length > (32768 - read_index) << 2))
                {
                    // WebSynth D-77 doesn't support sysex fragments
                    // instead of splitting the sysex into two parts, the second part is written into extra provided area

                    D77_MidiMessageLong((uint8_t *)&(event_buffer[read_index]), length);
                    read_index = 0;
                }
                else
                {
                    D77_MidiMessageLong((uint8_t *)&(event_buffer[read_index]), length);
                    read_index = (read_index + ((length + 3) >> 2)) & 0x7fff;
                }
            }
            else
            {
                D77_MidiMessageShort(event_buffer[read_index]);
                read_index = (read_index + 1) & 0x7fff;
            }
        } while (read_index != write_index);

        // update global volatile variable
        event_read_index = read_index;
    }

    // render audio data
#ifdef INDIRECT_64BIT
    if (!D77_RenderSamples((int16_t *) &(midi_buffer[num * bytes_per_call])))
#else
    if (!D77_RenderSamples((int16_t *) midi_queue_buffer[num]->mAudioData))
#endif
    {
        return -1;
    }

    return 0;
}

static void audio_callback_proc(void *inUserData, AudioQueueRef inAQ, AudioQueueBufferRef inBuffer)
{
    if (render_subbuffer(subbuf_counter) < 0)
    {
        fprintf(stderr, "Error rendering audio data\n");
    }
    midi_queue_buffer[subbuf_counter]->mAudioDataByteSize = bytes_per_call;
#ifdef INDIRECT_64BIT
    memcpy(midi_queue_buffer[subbuf_counter]->mAudioData, &(midi_buffer[subbuf_counter * bytes_per_call]), bytes_per_call);
#endif
    AudioQueueEnqueueBuffer(midi_pcm_queue, midi_queue_buffer[subbuf_counter], 0, NULL);
    subbuf_counter++;
    if (subbuf_counter == num_subbuffers)
    {
        subbuf_counter = 0;
    }
}

static int open_pcm_output(void) __attribute__((noinline));
static int open_pcm_output(void)
{
    AudioStreamBasicDescription format;
    OSStatus err;

    format.mSampleRate = frequency;
    format.mFormatID = kAudioFormatLinearPCM;
    format.mFormatFlags = kLinearPCMFormatFlagIsSignedInteger | kLinearPCMFormatFlagIsPacked;
    format.mBytesPerPacket = 2 * num_channels;
    format.mFramesPerPacket = 1;
    format.mBytesPerFrame = 2 * num_channels;
    format.mChannelsPerFrame = num_channels;
    format.mBitsPerChannel = 16;
    format.mReserved = 0;

    err = AudioQueueNewOutput(&format, audio_callback_proc, NULL, NULL, NULL, 0, &midi_pcm_queue);
    if (err != noErr)
    {
        fprintf(stderr, "Error creating PCM queue: %i\n", err);
        return -1;
    }

    midi_queue_buffer = (struct AudioQueueBuffer **)malloc(num_subbuffers * sizeof(void *));
    if (midi_queue_buffer == NULL)
    {
        fprintf(stderr, "Error allocating queue buffer\n");
        return -2;
    }

    for (int i = 0; i < num_subbuffers; i++)
    {
        err = AudioQueueAllocateBuffer(midi_pcm_queue, bytes_per_call, &midi_queue_buffer[i]);
        if (err != noErr)
        {
            fprintf(stderr, "Error allocating queue buffer: %i\n", err);
            return -2;
        }

        midi_queue_buffer[i]->mUserData = (void *)(uintptr_t)i;
    }

    return 0;
}

static void close_pcm_output(void) __attribute__((noinline));
static void close_pcm_output(void)
{
    AudioQueueDispose(midi_pcm_queue, 1);
}


static int open_midi_endpoint(void) __attribute__((noinline));
static int open_midi_endpoint(void)
{
    OSStatus err;

    err = MIDIClientCreate(CFSTR(MIDI_NAME), NULL, NULL, &midi_client);
    if (err != noErr)
    {
        fprintf(stderr, "Error creating MIDI client: %i\n", err);
        return -1;
    }

#if (MIDI_API >= 0)
#if (MIDI_API == 0)
    if (__builtin_available(macOS 11.0, *))
#endif
    {
        err = MIDIDestinationCreateWithProtocol(midi_client, CFSTR(MIDI_NAME), kMIDIProtocol_1_0, &midi_endpoint, ^(const MIDIEventList *evtlist, void * __nullable srcConnRefCon) { midi_receive_proc(evtlist, srcConnRefCon); } );
    }
#endif
#if (MIDI_API <= 0)
#if (MIDI_API == 0)
    else
#endif
    {
        err = MIDIDestinationCreate(midi_client, CFSTR(MIDI_NAME), midi_read_proc, NULL, &midi_endpoint);
    }
#endif
    if (err != noErr)
    {
        MIDIClientDispose(midi_client);
        fprintf(stderr, "Error creating MIDI destination: %i\n", err);
        return -2;
    }

    printf("MIDI destination is %s\n", MIDI_NAME);

    if (MIDIObjectSetIntegerProperty(midi_client, kMIDIPropertyUniqueID, midi_name_crc32) == noErr)
    {
        printf("Unique ID is %i\n", (int)(int32_t)midi_name_crc32);
    }
    else
    {
        for (int i = 0; i < 32; i++)
        {
            int32_t unique_id = midi_name_crc32 ^ (1 << i);
            if (MIDIObjectSetIntegerProperty(midi_client, kMIDIPropertyUniqueID, unique_id) == noErr)
            {
                printf("Unique ID is %i\n", (int)unique_id);
                break;
            }
        }
    }

    return 0;
}

static void close_midi_endpoint(void) __attribute__((noinline));
static void close_midi_endpoint(void)
{
    MIDIEndpointDispose(midi_endpoint);
    MIDIClientDispose(midi_client);
}


static void main_loop(void) __attribute__((noinline));
static void main_loop(void)
{
    int is_paused;
    uint64_t last_written_time, current_time;

    for (int i = 2; i < num_subbuffers; i++)
    {
        midi_queue_buffer[i]->mAudioDataByteSize = bytes_per_call;
        memset(midi_queue_buffer[i]->mAudioData, 0, bytes_per_call);
        AudioQueueEnqueueBuffer(midi_pcm_queue, midi_queue_buffer[i], 0, NULL);
    }

    // pause pcm playback at the beginning
    is_paused = 1;

    midi_event_written = 0;

    for (;;)
    {
        if (is_paused)
        {
            struct timespec req;

            req.tv_sec = 0;
            req.tv_nsec = 10000000;
            nanosleep(&req, NULL);

            if (midi_event_written)
            {
                midi_event_written = 0;

                // remember time of last written event
                last_written_time = clock_gettime_nsec_np(CLOCK_UPTIME_RAW);

                if (AudioQueueStart(midi_pcm_queue, NULL) == noErr)
                {
                    is_paused = 0;
                    printf("PCM playback unpaused\n");
                }
            }
            else
            {
                continue;
            }
        }

        CFRunLoopRunInMode(kCFRunLoopDefaultMode, 1, 0);

        current_time = clock_gettime_nsec_np(CLOCK_UPTIME_RAW);
        if (midi_event_written)
        {
            midi_event_written = 0;

            // remember time of last written event
            last_written_time = current_time;

            continue;
        }

        // if more than 60 seconds elapsed from last written event, then pause pcm playback
        if (current_time - last_written_time > 60000000000ull)
        {
            if (AudioQueuePause(midi_pcm_queue) == noErr)
            {
                is_paused = 1;
                printf("PCM playback paused\n");
            }
            else
            {
                // if pausing doesn't work then set time of last written event as current time, so the next attempt to pause will be in 60 seconds
                last_written_time = current_time;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    read_arguments(argc, argv);

    if (daemonize)
    {
        if (run_as_daemon_start(argv) < 0)
        {
            return 1;
        }
    }

    if (start_synth() < 0)
    {
        return 2;
    }

    handle_privileges();

    if (open_pcm_output() < 0)
    {
        stop_synth();
        return 5;
    }

    if (open_midi_endpoint() < 0)
    {
        close_pcm_output();
        stop_synth();
        return 6;
    }

    if (daemonize)
    {
        run_as_daemon_finish();
    }

    main_loop();

    close_midi_endpoint();
    close_pcm_output();
    stop_synth();
    return 0;
}

