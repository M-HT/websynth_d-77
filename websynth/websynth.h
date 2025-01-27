/**
 *
 *  Copyright (C) 2025 Roman Pauer
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

#if !defined(_WEBSYNTH_H_INCLUDED_)
#define _WEBSYNTH_H_INCLUDED_

#include <stdint.h>

#pragma pack(4)
typedef struct
{
    uint32_t dwSamplingFreq;    // 22050/44100  load default: 22050 .ini value: 44100   validation value: 22050
    uint32_t dwPolyphony;       // 8-256        load default: 32    .ini value: 64      validation value: 8/256
    uint32_t dwCpuLoadL;        // 20-85        load default: 70    .ini value: 60      validation value: 20/85
    uint32_t dwCpuLoadH;        // 90           load default: 90    .ini value: 90      validation value: 90
    uint32_t dwRevSw;           // 0/1          load default: 1     .ini value: 1       validation value: 1
    uint32_t dwChoSw;           // 0/1          load default: 1     .ini value: 1       validation value: 1
    uint32_t dwMVol;            // 0-200        load default: 100   .ini value: 100     validation value: 200
    uint32_t dwRevAdj;          // 0-200        load default: 83    .ini value: 95      validation value: 200
    uint32_t dwChoAdj;          // 0-200        load default: 60    .ini value: 70      validation value: 200
    uint32_t dwOutLev;          // 0-200        load default: 123   .ini value: 110     validation value: 200
    uint32_t dwRevFb;           // 0-200        load default: 90    .ini value: 95      validation value: 200
    uint32_t dwRevDrm;          // 0-200        load default: 90    .ini value: 80      validation value: 200
    uint32_t dwResoUpAdj;       // 0-100        load default: 55    .ini value: 40      validation value: 100
    uint32_t dwCacheSize;       // 1-20         load default: 10    .ini value: 3       validation value: 1/20
    uint32_t dwTimeReso;        // 40/80        load default: 80    .ini value: 80      validation value: 80
} D77_SETINGS;
#pragma pack()

#pragma pack(2)
typedef struct
{
    uint16_t wChoAdj;
    uint16_t wRevAdj;
    uint16_t wRevDrm;
    uint16_t wRevFb;
    uint16_t wOutLev;
    uint16_t wResoUpAdj;
} D77_PARAMETERS;
#pragma pack()

enum D77_EFFECT
{
    D77_EFFECT_Chorus = 0,
    D77_EFFECT_Reverb = 1
};

#ifdef __cplusplus
extern "C" {
#endif

#ifdef INDIRECT_64BIT
extern int D77_LoadLibrary(const char *libpath);
extern void D77_FreeLibrary(void);

extern void *D77_AllocateMemory(unsigned int size);
extern void D77_FreeMemory(void *mem, unsigned int size);
#endif

extern void D77_ValidateSettings(D77_SETINGS *lpSettings);
extern uint32_t D77_InitializeDataFile(uint8_t *lpDataFile, uint32_t dwLength);
extern uint32_t D77_InitializeSynth(uint32_t dwSamplingFrequency, uint32_t dwPolyphony, uint32_t dwTimeReso_unused);
extern void D77_InitializeUnknown(uint32_t dwUnknown_unused);
extern void D77_InitializeEffect(enum D77_EFFECT dwEffect, uint32_t bEnabled);
extern void D77_InitializeCpuLoad(uint32_t dwCpuLoadLow, uint32_t dwCpuLoadHigh);
extern void D77_InitializeParameters(const D77_PARAMETERS *lpParameters);
extern void D77_InitializeMasterVolume(uint32_t dwMasterVolume);

extern uint32_t D77_GetRenderedSamplesPerCall(void);

extern uint32_t D77_MidiMessageShort(uint32_t dwMessage);
extern uint32_t D77_MidiMessageLong(const uint8_t *lpMessage, uint32_t dwLength);

extern uint32_t D77_RenderSamples(int16_t *lpSamples);

#ifdef __cplusplus
}
#endif

#endif

