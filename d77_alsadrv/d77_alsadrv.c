/**
 *
 *  Copyright (C) 2022-2026 Roman Pauer
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

#define _FILE_OFFSET_BITS 64
#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <pwd.h>
#include <alsa/asoundlib.h>
#include "websynth.h"


static const char midi_name[] = "WebSynth D-77";
static const char port_name[] = "WebSynth D-77 port";

static snd_seq_t *midi_seq;
static int midi_port_id;
static pthread_t midi_thread;
static snd_pcm_t *midi_pcm;
static volatile int midi_init_state;
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

#if defined(INDIRECT_64BIT) || defined(PTROFS_64BIT)
static uint8_t *midi_buffer;
static uint32_t *event_buffer;
#else
static uint8_t midi_buffer[65536];
static uint32_t event_buffer[32768 + 16384];
#endif

static volatile int event_read_index;
static volatile int event_write_index;


static void set_thread_scheduler(void) __attribute__((noinline));
static void set_thread_scheduler(void)
{
    struct sched_param param;

    memset(&param, 0, sizeof(struct sched_param));
    param.sched_priority = sched_get_priority_min(SCHED_FIFO);
    if (param.sched_priority > 0)
    {
        sched_setscheduler(0, SCHED_FIFO, &param);
    }
}

static void wait_for_midi_initialization(void) __attribute__((noinline));
static void wait_for_midi_initialization(void)
{
    while (midi_init_state == 0)
    {
        struct timespec req;

        req.tv_sec = 0;
        req.tv_nsec = 10000000;
        nanosleep(&req, NULL);
    };
}

static void subscription_event(snd_seq_event_t *event) __attribute__((noinline));
static void subscription_event(snd_seq_event_t *event)
{
    snd_seq_client_info_t *cinfo;
    int err;

    snd_seq_client_info_alloca(&cinfo);
    err = snd_seq_get_any_client_info(midi_seq, event->data.connect.sender.client, cinfo);
    if (err >= 0)
    {
        if (event->type == SND_SEQ_EVENT_PORT_SUBSCRIBED)
        {
            printf("Client subscribed: %s\n", snd_seq_client_info_get_name(cinfo));
        }
        else
        {
            printf("Client unsubscribed: %s\n", snd_seq_client_info_get_name(cinfo));
        }
    }
    else
    {
        printf("Client unsubscribed\n");
    }
}

static void write_short_events(const uint32_t *events, unsigned int length)
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

    if (length > free_space)
    {
        fprintf(stderr, "Event buffer overflow\n");
        return;
    }

    // write events to event buffer
    for (; length != 0; length--,events++)
    {
        event_buffer[write_index] = *events;
        write_index = (write_index + 1) & 0x7fff;
    }

    // update global volatile variable
    event_write_index = write_index;

    midi_event_written = 1;
}

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

static void process_event(snd_seq_event_t *event)
{
    uint32_t data[4];

    switch (event->type)
    {
        case SND_SEQ_EVENT_NOTEON:
            data[0] = (0x90 | event->data.note.channel) | (event->data.note.note << 8) | (event->data.note.velocity << 16);

            write_short_events(data, 1);

#ifdef PRINT_EVENTS
            printf("Note ON, channel:%d note:%d velocity:%d\n", event->data.note.channel, event->data.note.note, event->data.note.velocity);
#endif

            break;

        case SND_SEQ_EVENT_NOTEOFF:
            data[0] = (0x80 | event->data.note.channel) | (event->data.note.note << 8) | (event->data.note.velocity << 16);

            write_short_events(data, 1);

#ifdef PRINT_EVENTS
            printf("Note OFF, channel:%d note:%d velocity:%d\n", event->data.note.channel, event->data.note.note, event->data.note.velocity);
#endif

            break;

        case SND_SEQ_EVENT_KEYPRESS:
            // Not used by WebSynth D-77
#if 0
            data[0] = (0xA0 | event->data.note.channel) | (event->data.note.note << 8) | (event->data.note.velocity << 16);

            write_short_events(data, 1);
#endif

#ifdef PRINT_EVENTS
            printf("Keypress, channel:%d note:%d velocity:%d\n", event->data.note.channel, event->data.note.note, event->data.note.velocity);
#endif

            break;

        case SND_SEQ_EVENT_CONTROLLER:
            data[0] = (0xB0 | event->data.control.channel) | (event->data.control.param << 8) | (event->data.control.value << 16);

            write_short_events(data, 1);

#ifdef PRINT_EVENTS
            printf("Controller, channel:%d param:%d value:%d\n", event->data.control.channel, event->data.control.param, event->data.control.value);
#endif

            break;

        case SND_SEQ_EVENT_PGMCHANGE:
            data[0] = (0xC0 | event->data.control.channel) | (event->data.control.value << 8);

            write_short_events(data, 1);

#ifdef PRINT_EVENTS
            printf("Program change, channel:%d value:%d\n", event->data.control.channel, event->data.control.value);
#endif

            break;

        case SND_SEQ_EVENT_CHANPRESS:
            data[0] = (0xD0 | event->data.control.channel) | (event->data.control.value << 8);

            write_short_events(data, 1);

#ifdef PRINT_EVENTS
            printf("Channel pressure, channel:%d value:%d\n", event->data.control.channel, event->data.control.value);
#endif

            break;

        case SND_SEQ_EVENT_PITCHBEND:
            data[0] = (0xE0 | event->data.control.channel) | (((event->data.control.value + 0x2000) & 0x7f) << 8) | ((((event->data.control.value + 0x2000) >> 7) & 0x7f) << 16);

            write_short_events(data, 1);

#ifdef PRINT_EVENTS
            printf("Pitch bend, channel:%d value:%d\n", event->data.control.channel, event->data.control.value);
#endif

            break;

        case SND_SEQ_EVENT_CONTROL14:
            if (event->data.control.param >= 0 && event->data.control.param < 32)
            {
                // controller LSB - WebSynth D-77 requires setting data entry LSB before data entry MSB
                data[0] = (0xB0 | event->data.control.channel) | ((event->data.control.param + 32) << 8) | ((event->data.control.value & 0x7f) << 16);
                // controller MSB
                data[1] = (0xB0 | event->data.control.channel) | (event->data.control.param << 8) | (((event->data.control.value >> 7) & 0x7f) << 16);

                write_short_events(data, 2);

#ifdef PRINT_EVENTS
                printf("Controller 14-bit, channel:%d param:%d value:%d\n", event->data.control.channel, event->data.control.param, event->data.control.value);
#endif
            }
            else
            {
#ifdef PRINT_EVENTS
                printf("Unknown controller, channel:%d param:%d value:%d\n", event->data.control.channel, event->data.control.param, event->data.control.value);
#endif
            }


            break;

        case SND_SEQ_EVENT_NONREGPARAM:
            // NRPN MSB
            data[0] = (0xB0 | event->data.control.channel) | (0x63 << 8) | (((event->data.control.param >> 7) & 0x7f) << 16);
            // NRPN LSB
            data[1] = (0xB0 | event->data.control.channel) | (0x62 << 8) | ((event->data.control.param & 0x7f) << 16);
            // data entry LSB - WebSynth D-77 requires setting data entry LSB before data entry MSB
            data[2] = (0xB0 | event->data.control.channel) | (0x26 << 8) | ((event->data.control.value & 0x7f) << 16);
            // data entry MSB
            data[3] = (0xB0 | event->data.control.channel) | (0x06 << 8) | (((event->data.control.value >> 7) & 0x7f) << 16);

            write_short_events(data, 4);

#ifdef PRINT_EVENTS
            printf("NRPN, channel:%d param:%d value:%d\n", event->data.control.channel, event->data.control.param, event->data.control.value);
#endif

            break;

        case SND_SEQ_EVENT_REGPARAM:
            // RPN MSB
            data[0] = (0xB0 | event->data.control.channel) | (0x65 << 8) | (((event->data.control.param >> 7) & 0x7f) << 16);
            // RPN LSB
            data[1] = (0xB0 | event->data.control.channel) | (0x64 << 8) | ((event->data.control.param & 0x7f) << 16);
            // data entry LSB - WebSynth D-77 requires setting data entry LSB before data entry MSB
            data[2] = (0xB0 | event->data.control.channel) | (0x26 << 8) | ((event->data.control.value & 0x7f) << 16);
            // data entry MSB
            data[3] = (0xB0 | event->data.control.channel) | (0x06 << 8) | (((event->data.control.value >> 7) & 0x7f) << 16);

            write_short_events(data, 4);

#ifdef PRINT_EVENTS
            printf("RPN, channel:%d param:%d value:%d\n", event->data.control.channel, event->data.control.param, event->data.control.value);
#endif

            break;

        case SND_SEQ_EVENT_SYSEX:
            // WebSynth D-77 doesn't support sysex fragments
            write_long_event(event->data.ext.ptr, event->data.ext.len);

#ifdef PRINT_EVENTS
            printf("SysEx (fragment) of size %d\n", event->data.ext.len);
#endif

            break;

        case SND_SEQ_EVENT_QFRAME:
            // Not used by WebSynth D-77
#if 0
            data[0] = 0xF1 | (ev->data.control.value << 8);

            write_short_events(data, 1);
#endif

#ifdef PRINT_EVENTS
            printf("MTC Quarter Frame, value:%d\n", event->data.control.value);
#endif

            break;

        case SND_SEQ_EVENT_SONGPOS:
            // Not used by WebSynth D-77
#if 0
            data[0] = 0xF2 | (((event->data.control.value + 0x2000) & 0x7f) << 8) | ((((event->data.control.value + 0x2000) >> 7) & 0x7f) << 16);

            write_short_events(data, 1);
#endif

#ifdef PRINT_EVENTS
            printf("Song Position, value:%d\n", event->data.control.value);
#endif

            break;

        case SND_SEQ_EVENT_SONGSEL:
            // Not used by WebSynth D-77
#if 0
            data[0] = 0xF3 | (ev->data.control.value << 8);

            write_short_events(data, 1);
#endif

#ifdef PRINT_EVENTS
            printf("Song Select, value:%d\n", event->data.control.value);
#endif

            break;

        case SND_SEQ_EVENT_TUNE_REQUEST:
            // Not used by WebSynth D-77
#if 0
            data[0] = 0xF6;

            write_short_events(data, 1);
#endif

#ifdef PRINT_EVENTS
            printf("Tune Request\n");
#endif

            break;

        case SND_SEQ_EVENT_CLOCK:
            // Not used by WebSynth D-77
#if 0
            data[0] = 0xF8;

            write_short_events(data, 1);
#endif

#ifdef PRINT_EVENTS
            printf("Clock\n");
#endif

            break;

        case SND_SEQ_EVENT_TICK:
            // Not used by WebSynth D-77
#if 0
            data[0] = 0xF9;

            write_short_events(data, 1);
#endif

#ifdef PRINT_EVENTS
            printf("Tick\n");
#endif

            break;

        case SND_SEQ_EVENT_START:
            // Not used by WebSynth D-77
#if 0
            data[0] = 0xFA;

            write_short_events(data, 1);
#endif

#ifdef PRINT_EVENTS
            printf("Start\n");
#endif

            break;

        case SND_SEQ_EVENT_CONTINUE:
            // Not used by WebSynth D-77
#if 0
            data[0] = 0xFB;

            write_short_events(data, 1);
#endif

#ifdef PRINT_EVENTS
            printf("Continue\n");
#endif

            break;

        case SND_SEQ_EVENT_STOP:
            // Not used by WebSynth D-77
#if 0
            data[0] = 0xFC;

            write_short_events(data, 1);
#endif

#ifdef PRINT_EVENTS
            printf("Stop\n");
#endif

            break;

        case SND_SEQ_EVENT_SENSING:
            // Not used by WebSynth D-77
#if 0
            data[0] = 0xFE;

            write_short_events(data, 1);
#endif

#ifdef PRINT_EVENTS
            printf("Active Sense\n");
#endif

            break;

        case SND_SEQ_EVENT_RESET:
            // Not used by WebSynth D-77
#if 0
            data[0] = 0xFF;

            write_short_events(data, 1);
#endif

#ifdef PRINT_EVENTS
            printf("Reset\n");
#endif

            break;

        case SND_SEQ_EVENT_PORT_SUBSCRIBED:
            subscription_event(event);
            break;

        case SND_SEQ_EVENT_PORT_UNSUBSCRIBED:
            subscription_event(event);
            break;

        default:
            fprintf(stderr, "Unhandled event type: %i\n", event->type);
            break;
    }
}

static void *midi_thread_proc(void *arg)
{
    snd_seq_event_t *event;

    // try setting thread scheduler (only root)
    set_thread_scheduler();

    // set thread as initialized
    *(int *)arg = 1;

    wait_for_midi_initialization();

    while (midi_init_state > 0)
    {
        if (snd_seq_event_input(midi_seq, &event) < 0)
        {
            continue;
        }

        process_event(event);
    }

    return NULL;
}

static void usage(const char *progname)
{
    static const char basename[] = "d77_alsadrv";

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

#if defined(INDIRECT_64BIT) || defined(PTROFS_64BIT)
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
#if defined(INDIRECT_64BIT) || defined(PTROFS_64BIT)
        D77_FreeMemory(datafile_ptr, datafile_len);
#else
        free(datafile_ptr);
#endif
        return -8;
    }

    return 0;
}


static void stop_synth(void)
{
#if defined(INDIRECT_64BIT) || defined(PTROFS_64BIT)
    D77_FreeMemory(midi_buffer, 65536 + (32768 + 16384) * sizeof(uint32_t));
    D77_FreeMemory(datafile_ptr, datafile_len);
#ifdef INDIRECT_64BIT
    D77_FreeLibrary();
#endif
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

#ifdef PTROFS_64BIT
    if (!D77_InitializePointerOffset())
    {
        fprintf(stderr, "Error initializing pointer offset\n");
        return -1;
    }
#endif

    if (load_data_file() < 0)
    {
        fprintf(stderr, "Error opening DATA file: %s\n", data_filepath);
        return -2;
    }

#if defined(INDIRECT_64BIT) || defined(PTROFS_64BIT)
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
#if defined(INDIRECT_64BIT) || defined(PTROFS_64BIT)
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
    memset(midi_buffer, 0, 65536);


    return 0;
}

static int run_as_daemon(void) __attribute__((noinline));
static int run_as_daemon(void)
{
    int err;

    printf("Running as daemon...\n");

    err = daemon(0, 0);
    if (err < 0)
    {
        fprintf(stderr, "Error running as daemon: %i\n", err);
        return -1;
    }

    return 0;
}

static int open_midi_port(void) __attribute__((noinline));
static int open_midi_port(void)
{
    int err;
    unsigned int caps, type;

    err = snd_seq_open(&midi_seq, "default", SND_SEQ_OPEN_DUPLEX, 0);
    if (err < 0)
    {
        fprintf(stderr, "Error opening ALSA sequencer: %i\n%s\n", err, snd_strerror(err));
        return -1;
    }

    err = snd_seq_set_client_name(midi_seq, midi_name);
    if (err < 0)
    {
        snd_seq_close(midi_seq);
        fprintf(stderr, "Error setting sequencer client name: %i\n%s\n", err, snd_strerror(err));
        return -2;
    }

    caps = SND_SEQ_PORT_CAP_SUBS_WRITE | SND_SEQ_PORT_CAP_WRITE;
    type = SND_SEQ_PORT_TYPE_MIDI_GENERIC | SND_SEQ_PORT_TYPE_MIDI_GM | SND_SEQ_PORT_TYPE_SYNTHESIZER;
    err = snd_seq_create_simple_port(midi_seq, port_name, caps, type);
    if (err < 0)
    {
        snd_seq_close(midi_seq);
        fprintf(stderr, "Error creating sequencer port: %i\n%s\n", err, snd_strerror(err));
        return -3;
    }
    midi_port_id = err;

    printf("%s ALSA address is %i:0\n", midi_name, snd_seq_client_id(midi_seq));

    return 0;
}

static void close_midi_port(void)
{
    snd_seq_delete_port(midi_seq, midi_port_id);
    snd_seq_close(midi_seq);
}


static int set_hw_params(void)
{
    int err, dir;
    unsigned int rate;
    snd_pcm_uframes_t buffer_size, period_size;
    snd_pcm_hw_params_t *pcm_hwparams;

    snd_pcm_hw_params_alloca(&pcm_hwparams);

    err = snd_pcm_hw_params_any(midi_pcm, pcm_hwparams);
    if (err < 0)
    {
        fprintf(stderr, "Error getting hwparams: %i\n%s\n", err, snd_strerror(err));
        return -1;
    }

    err = snd_pcm_hw_params_set_access(midi_pcm, pcm_hwparams, SND_PCM_ACCESS_RW_INTERLEAVED);
    if (err < 0)
    {
        fprintf(stderr, "Error setting access: %i\n%s\n", err, snd_strerror(err));
        return -2;
    }

    err = snd_pcm_hw_params_set_format(midi_pcm, pcm_hwparams, SND_PCM_FORMAT_S16);
    if (err < 0)
    {
        fprintf(stderr, "Error setting format: %i\n%s\n", err, snd_strerror(err));
        return -3;
    }

    err = snd_pcm_hw_params_set_channels(midi_pcm, pcm_hwparams, num_channels);
    if (err < 0)
    {
        fprintf(stderr, "Error setting channels: %i\n%s\n", err, snd_strerror(err));
        return -4;
    }

    rate = frequency;
    dir = 0;
    err = snd_pcm_hw_params_set_rate_near(midi_pcm, pcm_hwparams, &rate, &dir);
    if (err < 0)
    {
        fprintf(stderr, "Error setting rate: %i\n%s\n", err, snd_strerror(err));
        return -5;
    }

    buffer_size = samples_per_call * num_subbuffers;
    err = snd_pcm_hw_params_set_buffer_size_near(midi_pcm, pcm_hwparams, &buffer_size);
    if (err < 0)
    {
        fprintf(stderr, "Error setting buffer size: %i\n%s\n", err, snd_strerror(err));
        return -6;
    }

    period_size = samples_per_call;
    dir = 0;
    err = snd_pcm_hw_params_set_period_size_near(midi_pcm, pcm_hwparams, &period_size, &dir);
    if (err < 0)
    {
        fprintf(stderr, "Error setting period size: %i\n%s\n", err, snd_strerror(err));
        return -7;
    }

    err = snd_pcm_hw_params(midi_pcm, pcm_hwparams);
    if (err < 0)
    {
        fprintf(stderr, "Error setting hwparams: %i\n%s\n", err, snd_strerror(err));
        return -8;
    }

    return 0;
}

static int set_sw_params(void)
{
    snd_pcm_sw_params_t *swparams;
    int err;

    snd_pcm_sw_params_alloca(&swparams);

    err = snd_pcm_sw_params_current(midi_pcm, swparams);
    if (err < 0)
    {
        fprintf(stderr, "Error getting swparams: %i\n%s\n", err, snd_strerror(err));
        return -1;
    }

    err = snd_pcm_sw_params_set_avail_min(midi_pcm, swparams, samples_per_call);
    if (err < 0)
    {
        fprintf(stderr, "Error setting avail min: %i\n%s\n", err, snd_strerror(err));
        return -2;
    }

    err = snd_pcm_sw_params(midi_pcm, swparams);
    if (err < 0)
    {
        fprintf(stderr, "Error setting sw params: %i\n%s\n", err, snd_strerror(err));
        return -3;
    }

    return 0;
}

static int open_pcm_output(void) __attribute__((noinline));
static int open_pcm_output(void)
{
    int err;

    err = snd_pcm_open(&midi_pcm, "default", SND_PCM_STREAM_PLAYBACK, 0);
    if (err < 0)
    {
        fprintf(stderr, "Error opening PCM device: %i\n%s\n", err, snd_strerror(err));
        return -1;
    }

    if (set_hw_params() < 0)
    {
        return -2;
    }

    if (set_sw_params() < 0)
    {
        return -3;
    }

    // set nonblock mode
    snd_pcm_nonblock(midi_pcm, 1);

    snd_pcm_prepare(midi_pcm);

    return 0;
}

static void close_pcm_output(void)
{
    snd_pcm_close(midi_pcm);
}


static int drop_privileges(void)
{
    uid_t uid;
    gid_t gid;
    const char *sudo_id;
    long long int llid;
    const char *xdg_dir;
    char buf[32];
    struct stat statbuf;
    struct passwd *passwdbuf;

    if (getuid() != 0)
    {
        return 0;
    }

    sudo_id = secure_getenv("SUDO_UID");
    if (sudo_id == NULL)
    {
        sudo_id = secure_getenv("PKEXEC_UID");
        if (sudo_id == NULL)
        {
            return -1;
        }
    }

    errno = 0;
    llid = strtoll(sudo_id, NULL, 10);
    uid = (uid_t) llid;
    if (errno != 0 || uid == 0 || llid != (long long int)uid)
    {
        return -2;
    }

    gid = getgid();
    if (gid == 0)
    {
        sudo_id = secure_getenv("SUDO_GID");
        if (sudo_id == NULL)
        {
            passwdbuf = getpwuid(uid);
            if (passwdbuf != NULL)
            {
                gid = passwdbuf->pw_gid;
            }

            if (gid == 0)
            {
                return -3;
            }
        }
        else
        {
            errno = 0;
            llid = strtoll(sudo_id, NULL, 10);
            gid = (gid_t) llid;
            if (errno != 0 || gid == 0 || llid != (long long int)gid)
            {
                return -4;
            }
        }
    }

    if (setgid(gid) != 0)
    {
        return -5;
    }
    if (setuid(uid) != 0)
    {
        return -6;
    }

    printf("Dropped root privileges\n");

    chdir("/");

    // define some environment variables

    xdg_dir = getenv("XDG_RUNTIME_DIR");
    if ((xdg_dir == NULL) || (*xdg_dir == 0))
    {
        snprintf(buf, 32, "/run/user/%lli", (long long int)uid);

        if ((stat(buf, &statbuf) == 0) && ((statbuf.st_mode & S_IFMT) == S_IFDIR) && (statbuf.st_uid == uid))
        {
            // if XDG_RUNTIME_DIR is not defined and directory /run/user/$USER exists then use it for XDG_RUNTIME_DIR
            setenv("XDG_RUNTIME_DIR", buf, 1);

            xdg_dir = getenv("XDG_CONFIG_HOME");
            if ((xdg_dir == NULL) || (*xdg_dir == 0))
            {
                passwdbuf = getpwuid(uid);
                if (passwdbuf != NULL)
                {
                    // also if XDG_CONFIG_HOME is not defined then define it as user's home directory
                    setenv("XDG_CONFIG_HOME", passwdbuf->pw_dir, 1);
                }
            }
        }
    }

    return 0;
}

static int start_thread(void) __attribute__((noinline));
static int start_thread(void)
{
    pthread_attr_t attr;
    int err;
    volatile int initialized;

    // try to increase priority (only root)
    nice(-20);

    err = pthread_attr_init(&attr);
    if (err != 0)
    {
        fprintf(stderr, "Error creating thread attribute: %i\n", err);
        return -1;
    }

    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    midi_init_state = 0;
    initialized = 0;
    err = pthread_create(&midi_thread, &attr, &midi_thread_proc, (void *)&initialized);
    pthread_attr_destroy(&attr);

    if (err != 0)
    {
        fprintf(stderr, "Error creating thread: %i\n", err);
        return -2;
    }

    // wait for thread initialization
    while (initialized == 0)
    {
        struct timespec req;

        req.tv_sec = 0;
        req.tv_nsec = 10000000;
        nanosleep(&req, NULL);
    };

    if (drop_privileges() < 0)
    {
        fprintf(stderr, "Error dropping root privileges\n");
    }

    return 0;
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
    if (!D77_RenderSamples((int16_t *) &(midi_buffer[num * bytes_per_call])))
    {
        return -1;
    }

    return 0;
}

static int output_subbuffer(int num)
{
    snd_pcm_uframes_t remaining;
    snd_pcm_sframes_t written;
    uint8_t *buf_ptr;

    remaining = samples_per_call;
    buf_ptr = &(midi_buffer[num * bytes_per_call]);

    while (remaining)
    {
        written = snd_pcm_writei(midi_pcm, buf_ptr, remaining);
        if (written < 0)
        {
            return -1;
        }

        remaining -= written;
        buf_ptr += written << 2;
    };

    return 0;
}

static void main_loop(void) __attribute__((noinline));
static void main_loop(void)
{
    int is_paused;
    struct timespec last_written_time, current_time;
#if defined(CLOCK_MONOTONIC_RAW)
    clockid_t monotonic_clock_id;

    #define MONOTONIC_CLOCK_TYPE monotonic_clock_id

    if (clock_gettime(CLOCK_MONOTONIC_RAW, &current_time))
    {
        monotonic_clock_id = CLOCK_MONOTONIC;
    }
    else
    {
        monotonic_clock_id = CLOCK_MONOTONIC_RAW;
    }
#else
    #define MONOTONIC_CLOCK_TYPE CLOCK_MONOTONIC
#endif

    for (int i = 2; i < num_subbuffers; i++)
    {
        output_subbuffer(i);
    }

    is_paused = 0;
    // pause pcm playback at the beginning
    if (0 == snd_pcm_pause(midi_pcm, 1))
    {
        is_paused = 1;
        printf("PCM playback paused\n");
    }
    else
    {
        // if pausing doesn't work then set time of last written event as current time, so the next attempt to pause will be in 60 seconds
        clock_gettime(MONOTONIC_CLOCK_TYPE, &last_written_time);
    }

    midi_event_written = 0;
    midi_init_state = 1;

    while (1)
    {
        struct timespec req;
        snd_pcm_state_t pcmstate;
        snd_pcm_sframes_t available_frames;

        req.tv_sec = 0;
        req.tv_nsec = 10000000;
        nanosleep(&req, NULL);

        if (midi_event_written)
        {
            midi_event_written = 0;

            // remember time of last written event
            clock_gettime(MONOTONIC_CLOCK_TYPE, &last_written_time);

            if (is_paused)
            {
                is_paused = 0;
                snd_pcm_pause(midi_pcm, 0);
                printf("PCM playback unpaused\n");
            }
        }
        else
        {
            if (is_paused)
            {
                continue;
            }

            clock_gettime(MONOTONIC_CLOCK_TYPE, &current_time);
            // if more than 60 seconds elapsed from last written event, then pause pcm playback
            if (current_time.tv_sec - last_written_time.tv_sec > 60)
            {
                if (0 == snd_pcm_pause(midi_pcm, 1))
                {
                    is_paused = 1;
                    printf("PCM playback paused\n");
                    continue;
                }
                else
                {
                    // if pausing doesn't work then set time of last written event as current time, so the next attempt to pause will be in 60 seconds
                    last_written_time = current_time;
                }
            }
        }

        pcmstate = snd_pcm_state(midi_pcm);
        if (pcmstate == SND_PCM_STATE_XRUN)
        {
            fprintf(stderr, "Buffer underrun\n");
            snd_pcm_prepare(midi_pcm);
        }

        available_frames = snd_pcm_avail_update(midi_pcm);
        while (available_frames >= (3 * samples_per_call))
        {
            if (render_subbuffer(subbuf_counter) < 0)
            {
                fprintf(stderr, "Error rendering audio data\n");
            }

            if (output_subbuffer(subbuf_counter) < 0)
            {
                fprintf(stderr, "Error writing audio data\n");
                available_frames = 0;
                break;
            }
            else
            {
                available_frames -= samples_per_call;
            }

            subbuf_counter++;
            if (subbuf_counter == num_subbuffers)
            {
                subbuf_counter = 0;
            }
        };
    };
}

int main(int argc, char *argv[])
{
    read_arguments(argc, argv);

    if (start_synth() < 0)
    {
        return 2;
    }

    if (daemonize)
    {
        if (run_as_daemon() < 0)
        {
            stop_synth();
            return 3;
        }
    }

    if (start_thread() < 0)
    {
        stop_synth();
        return 4;
    }

    if (open_pcm_output() < 0)
    {
        midi_init_state = -1;
        stop_synth();
        return 5;
    }

    if (open_midi_port() < 0)
    {
        midi_init_state = -1;
        close_pcm_output();
        stop_synth();
        return 6;
    }

    main_loop();

    midi_init_state = -1;
    close_midi_port();
    close_pcm_output();
    stop_synth();
    return 0;
}

