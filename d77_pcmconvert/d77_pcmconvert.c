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

#define _FILE_OFFSET_BITS 64
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "midi_loader.h"

#include "websynth.h"

#if (defined(__WIN32__) || defined(__WINDOWS__)) && !defined(_WIN32)
#define _WIN32
#endif

#ifndef _WIN32
    #include <sys/types.h>
    #include <dirent.h>
#endif

#ifdef __BYTE_ORDER

#if (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define BIG_ENDIAN_BYTE_ORDER
#else
#undef BIG_ENDIAN_BYTE_ORDER
#endif

#elif !defined(_WIN32)

#include <endian.h>
#if (__BYTE_ORDER == __BIG_ENDIAN)
#define BIG_ENDIAN_BYTE_ORDER
#else
#undef BIG_ENDIAN_BYTE_ORDER
#endif

#endif


static const char *arg_input = NULL;
static const char *arg_output = NULL;
static const char *arg_data = "dswebWDM.dat";
#ifdef INDIRECT_64BIT
#ifdef _WIN32
static const char *arg_lib = "d77_lib.dll";
#else
static const char *arg_lib = "d77_lib.so";
#endif
#endif
static int wav_to_file = 1;

static uint32_t current_time;

static unsigned int timediv;
static midi_event_info *midi_events;

static D77_SETINGS d77_settings;
static D77_PARAMETERS *d77_parameters;

#ifdef INDIRECT_64BIT
static uint8_t *input_buffer;
#else
static D77_PARAMETERS d77_param_buffer;
#endif

static int datafile_len;
static uint8_t *datafile_ptr;

static int16_t *output_buffer;
static unsigned int frequency, bytes_per_call, samples_per_call;


static inline void WRITE_LE_UINT16(uint8_t *ptr, uint16_t value)
{
    ptr[0] = value & 0xff;
    ptr[1] = (value >> 8) & 0xff;
}

static inline void WRITE_LE_UINT32(uint8_t *ptr, uint32_t value)
{
    ptr[0] = value & 0xff;
    ptr[1] = (value >> 8) & 0xff;
    ptr[2] = (value >> 16) & 0xff;
    ptr[3] = (value >> 24) & 0xff;
}


static uint8_t *load_data_file(const char *datapath, int *length)
{
    FILE *f;
    uint8_t *mem;
    long datalen;

    f = fopen(datapath, "rb");
    if (f == NULL)
    {
#ifndef _WIN32
        char *pathcopy, *slash, *filename;
        DIR *dir;
        struct dirent *entry;

        pathcopy = strdup(datapath);
        if (pathcopy == NULL) return NULL;

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
            return NULL;
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
            return NULL;
        }

        f = fopen(pathcopy, "rb");

        free(pathcopy);

        if (f == NULL)
        {
            return NULL;
        }
#else
        return NULL;
#endif
    }

    if (fseek(f, 0, SEEK_END))
    {
        fclose(f);
        return NULL;
    }

    datalen = ftell(f);
    if (datalen <= 4)
    {
        fclose(f);
        return NULL;
    }

    if (fseek(f, 0, SEEK_SET))
    {
        fclose(f);
        return NULL;
    }


#ifdef INDIRECT_64BIT
    mem = (uint8_t *)D77_AllocateMemory(datalen);
#else
    mem = (uint8_t *)malloc(datalen);
#endif
    if (mem == NULL)
    {
        fclose(f);
        return NULL;
    }

    if (fread(mem, 1, datalen, f) != datalen)
    {
#ifdef INDIRECT_64BIT
        D77_FreeMemory(mem, datalen);
#else
        free(mem);
#endif
        fclose(f);
        return NULL;
    }

    if (length != NULL)
    {
        *length = datalen;
    }

    return mem;
}

static void usage(const char *progname)
{
    static const char basename[] = "d77_pcmconvert";

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

#ifdef _WIN32
        slash = strrchr(progname, '\\');
        if (slash != NULL)
        {
            progname = slash + 1;
        }
#endif
    }

    printf(
        "%s - WebSynth D-77 pcm convert\n"
        "Usage: %s [OPTIONS]...\n"
        "  -i PATH  Input path (path to .mid)\n"
        "  -s       Output raw data do stdout\n"
        "  -o PATH  Output path (path to .wav)\n"
        "  -w PATH  Datafile path (path to dsweb*.dat)\n"
#ifdef INDIRECT_64BIT
#ifdef _WIN32
        "  -b PATH  Library path (path to d77_lib.dll)\n"
#else
        "  -b PATH  Library path (path to d77_lib.so)\n"
#endif
#endif
        "  -f NUM   Frequency (22050/44100 Hz)\n"
        "  -p NUM   Polyphony (8-256)\n"
        "  -m NUM   Master volume (0-200)\n"
        "  -r NUM   Reverb effect (0=off, 1=on)\n"
        "  -c NUM   Chorus effect (0=off, 1=on)\n"
        "  -l NUM   Cpu load (20-85)\n"
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

int main(int argc, char *argv[])
{
    int return_value;

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

    // parse arguments
    if (argc > 1)
    {
        int i, j;
        for (i = 1; i < argc; i++)
        {
            if (argv[i][0] == '-' && argv[i][1] != 0 && argv[i][2] == 0)
            {
                switch (argv[i][1])
                {
                    case 'i': // input
                        if ((i + 1) < argc)
                        {
                            i++;
                            arg_input = argv[i];
                        }
                        break;
                    case 'o': // output
                        if ((i + 1) < argc)
                        {
                            i++;
                            arg_output = argv[i];
                        }
                        break;
                    case 'w': // data file
                        if ((i + 1) < argc)
                        {
                            i++;
                            arg_data = argv[i];
                        }
                        break;
#ifdef INDIRECT_64BIT
                    case 'b': // library
                        if ((i + 1) < argc)
                        {
                            i++;
                            arg_lib = argv[i];
                        }
                        break;
#endif
                    case 's': // stdout
                        wav_to_file = 0;
                        break;
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

    if (arg_input == NULL)
    {
        fprintf(stderr, "no input file\n");
        usage(argv[0]);
    }
    if (wav_to_file && arg_output == NULL)
    {
        fprintf(stderr, "no output file\n");
        usage(argv[0]);
    }

#ifdef INDIRECT_64BIT
    // load library
    if (!D77_LoadLibrary(arg_lib))
    {
        fprintf(stderr, "error loading library\n");
        return 1;
    }

    input_buffer = (uint8_t *)D77_AllocateMemory(65536);
    if (input_buffer == NULL)
    {
        fprintf(stderr, "error allocating input buffer\n");
        return 2;
    }
#endif

    // load DATA file
    datafile_ptr = load_data_file(arg_data, &datafile_len);
    if (datafile_ptr == NULL)
    {
        fprintf(stderr, "error loading DATA file\n");
        return 3;
    }

    // load MIDI file
    if (load_midi_file(arg_input, &timediv, &midi_events))
    {
        fprintf(stderr, "error loading MIDI file\n");
        return 4;
    }


#ifdef INDIRECT_64BIT
    memcpy(input_buffer, &d77_settings, sizeof(D77_SETINGS));
    D77_ValidateSettings((D77_SETINGS *)input_buffer);
    memcpy(&d77_settings, input_buffer, sizeof(D77_SETINGS));
#else
    D77_ValidateSettings(&d77_settings);
#endif

    if (!D77_InitializeDataFile(datafile_ptr, datafile_len - 4))
    {
        fprintf(stderr, "error initializing DATA file\n");
        return 5;
    }

    if (!D77_InitializeSynth(d77_settings.dwSamplingFreq, d77_settings.dwPolyphony, d77_settings.dwTimeReso))
    {
        fprintf(stderr, "error initializing synth\n");
        return 6;
    }

    D77_InitializeUnknown(0);
    D77_InitializeEffect(D77_EFFECT_Reverb, d77_settings.dwRevSw ? 1 : 0);
    D77_InitializeEffect(D77_EFFECT_Chorus, d77_settings.dwChoSw ? 1 : 0);
    D77_InitializeCpuLoad(d77_settings.dwCpuLoadL, d77_settings.dwCpuLoadH);

#ifdef INDIRECT_64BIT
    d77_parameters = (D77_PARAMETERS *)input_buffer;
#else
    d77_parameters = &d77_param_buffer;
#endif
    d77_parameters->wChoAdj = d77_settings.dwChoAdj;
    d77_parameters->wRevAdj = d77_settings.dwRevAdj;
    d77_parameters->wRevDrm = d77_settings.dwRevDrm;
    d77_parameters->wRevFb = d77_settings.dwRevFb;
    d77_parameters->wOutLev = d77_settings.dwOutLev;
    d77_parameters->wResoUpAdj = d77_settings.dwResoUpAdj;

    D77_InitializeParameters(d77_parameters);

    D77_InitializeMasterVolume(d77_settings.dwMVol);

    frequency = d77_settings.dwSamplingFreq;
    samples_per_call = D77_GetRenderedSamplesPerCall();
    bytes_per_call = samples_per_call * 2 * sizeof(int16_t);

    // allocate output buffer
#ifdef INDIRECT_64BIT
    output_buffer = (int16_t *)D77_AllocateMemory(bytes_per_call);
#else
    output_buffer = (int16_t *)malloc(bytes_per_call);
#endif
    if (output_buffer == NULL)
    {
        fprintf(stderr, "error allocating output buffer\n");
        return 7;
    }


    return_value = 0;


    current_time = 0;

    // play midi
    {
        unsigned int num_calls, remaining_events;
        midi_event_info *cur_event;

        FILE *fout;

        if (wav_to_file)
        {
            uint8_t wav_header[44];
            uint8_t *header_ptr;

            fout = fopen(arg_output, "wb");
            if (fout == NULL)
            {
                free_midi_data(midi_events);
                fprintf(stderr, "error opening output file\n");
                return 8;
            }

            // wav header
            header_ptr = wav_header;
            WRITE_LE_UINT32(header_ptr, 0x46464952);        // "RIFF" tag
            WRITE_LE_UINT32(header_ptr + 4, 36);            // RIFF length - filled later
            WRITE_LE_UINT32(header_ptr + 8, 0x45564157);    // "WAVE" tag
            header_ptr += 12;

            // fmt chunk
            WRITE_LE_UINT32(header_ptr, 0x20746D66);    // "fmt " tag
            WRITE_LE_UINT32(header_ptr + 4, 16);        // chunk length
            header_ptr += 8;

            // PCMWAVEFORMAT structure
            WRITE_LE_UINT16(header_ptr, 1);                 // wFormatTag - 1 = PCM
            WRITE_LE_UINT16(header_ptr + 2, 2);             // nChannels - 2 = stereo
            WRITE_LE_UINT32(header_ptr + 4, frequency);     // nSamplesPerSec
            WRITE_LE_UINT32(header_ptr + 8, 4 * frequency); // nAvgBytesPerSec
            WRITE_LE_UINT16(header_ptr + 12, 4);            // nBlockAlign
            WRITE_LE_UINT16(header_ptr + 14, 16);           // wBitsPerSample
            header_ptr += 16;

            // data chunk
            WRITE_LE_UINT32(header_ptr, 0x61746164);    // "data" tag
            WRITE_LE_UINT32(header_ptr + 4, 0);         // chunk length - filled later
            header_ptr += 8;

            if (fwrite(wav_header, 1, 44, fout) != 44)
            {
                fprintf(stderr, "error writing to output file\n");
                return 9;
            }
        }
        else
        {
            fout = stdout;
        }

        num_calls = 0;
        remaining_events = midi_events[0].len;
        cur_event = midi_events + 1;
        while (current_time < midi_events[0].time + 112)
        {
            uint32_t next_time;

            num_calls++;

            next_time = ((num_calls * samples_per_call + (samples_per_call >> 1)) * (uint64_t)1000) / frequency;
            while ((remaining_events > 0) && (cur_event->time <= next_time))
            {
                if (cur_event->len <= 8)
                {
                    if (cur_event->data[0] != 0xff) // skip meta events
                    {
                        if (cur_event->data[0] == 0xf0)
                        {
#ifdef INDIRECT_64BIT
                            memcpy(input_buffer, cur_event->data, cur_event->len);
                            D77_MidiMessageLong(input_buffer, cur_event->len);
#else
                            D77_MidiMessageLong(cur_event->data, cur_event->len);
#endif
                        }
                        else
                        {
                            D77_MidiMessageShort(cur_event->data[0] | (cur_event->data[1] << 8) | (cur_event->data[2] << 16));
                        }
                    }
                }
                else
                {
                    if (cur_event->sysex[0] != 0xff) // skip meta events
                    {
#ifdef INDIRECT_64BIT
                        if (cur_event->len <= 65536)
                        {
                            memcpy(input_buffer, cur_event->sysex, cur_event->len);
                            D77_MidiMessageLong(input_buffer, cur_event->len);
                        }
#else
                        D77_MidiMessageLong(cur_event->sysex, cur_event->len);
#endif
                    }
                }

                cur_event++;
                remaining_events--;
            }

            current_time = next_time;

            if (!D77_RenderSamples(output_buffer))
            {
                fprintf(stderr, "error rendering samples\n");
                return_value = 10;
                break;
            }


#ifdef BIG_ENDIAN_BYTE_ORDER
            // swap values to little-endian
            {
                int i;
                for (i = 0; i < bytes_per_call; i += 2)
                {
                    uint8_t value;
                    value = output_buffer[i];
                    output_buffer[i] = output_buffer[i + 1];
                    output_buffer[i + 1] = value;
                }
            }
#endif

            if (fwrite(output_buffer, 1, bytes_per_call, fout) != bytes_per_call)
            {
                fprintf(stderr, "error writing to output file\n");
                return_value = 9;
                break;
            }
        }

        if (wav_to_file)
        {
            uint8_t chunk_length[4];

            // RIFF length
            WRITE_LE_UINT32(chunk_length, 36 + num_calls * bytes_per_call);
            fseek(fout, 4, SEEK_SET);
            if (fwrite(chunk_length, 4, 1, fout) != 1)
            {
                fprintf(stderr, "error writing to output file\n");
                return 9;
            }

            // data chunk length
            WRITE_LE_UINT32(chunk_length, num_calls * bytes_per_call);
            fseek(fout, 40, SEEK_SET);
            if (fwrite(chunk_length, 4, 1, fout) != 1)
            {
                fprintf(stderr, "error writing to output file\n");
                return 9;
            }

            fclose(fout);
        }
        else
        {
            fflush(fout);
            fout = NULL;
        }
    }

    // free output buffer, MIDI file, DATA file
#ifdef INDIRECT_64BIT
    D77_FreeMemory(output_buffer, bytes_per_call);
    D77_FreeMemory(datafile_ptr, datafile_len);
    D77_FreeMemory(input_buffer, 65536);
    D77_FreeLibrary();
#else
    free(output_buffer);
    free(datafile_ptr);
#endif
    free_midi_data(midi_events);

    return return_value;
}

