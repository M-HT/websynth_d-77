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

#include "llasm_cpu.h"
#ifdef INDIRECT_64BIT
#include "functions-32bit.h"
#include <stdlib.h>
#endif


#ifdef INDIRECT_64BIT
static void *library = NULL;

static void (*c_ValidateSettings_asm)(CPU);
static void (*c_InitializeDataFile_asm)(CPU);
static void (*c_InitializeSynth_asm)(CPU);
static void (*c_InitializeUnknown_asm)(CPU);
static void (*c_InitializeEffect_asm)(CPU);
static void (*c_InitializeCpuLoad_asm)(CPU);
static void (*c_InitializeParameters_asm)(CPU);
static void (*c_InitializeMasterVolume_asm)(CPU);

static uint32_t *dwRenderedSamplesPerCall_asm;

static void (*c_MidiMessageShort_asm)(CPU);
static void (*c_MidiMessageLong_asm)(CPU);

static void (*c_RenderSamples_asm)(CPU);
#endif


#ifdef __cplusplus
extern "C" {
#endif

extern _cpu *x86_initialize_cpu(void);
extern void x86_deinitialize_cpu(void);

#ifndef INDIRECT_64BIT
extern void c_ValidateSettings_asm(CPU);
extern void c_InitializeDataFile_asm(CPU);
extern void c_InitializeSynth_asm(CPU);
extern void c_InitializeUnknown_asm(CPU);
extern void c_InitializeEffect_asm(CPU);
extern void c_InitializeCpuLoad_asm(CPU);
extern void c_InitializeParameters_asm(CPU);
extern void c_InitializeMasterVolume_asm(CPU);

extern uint32_t dwRenderedSamplesPerCall_asm;

extern void c_MidiMessageShort_asm(CPU);
extern void c_MidiMessageLong_asm(CPU);

extern void c_RenderSamples_asm(CPU);
#endif

#ifdef __cplusplus
}
#endif

#ifdef INDIRECT_64BIT

EXTERNC int D77_LoadLibrary(const char *libpath)
{
    if (library != NULL) return 0;

    library = load_library_32bit(libpath);
    if (library == NULL) return 0;

    c_ValidateSettings_asm = (void (*)(CPU))find_symbol_32bit(library, "c_ValidateSettings_asm");
    c_InitializeDataFile_asm = (void (*)(CPU))find_symbol_32bit(library, "c_InitializeDataFile_asm");
    c_InitializeSynth_asm = (void (*)(CPU))find_symbol_32bit(library, "c_InitializeSynth_asm");
    c_InitializeUnknown_asm = (void (*)(CPU))find_symbol_32bit(library, "c_InitializeUnknown_asm");
    c_InitializeEffect_asm = (void (*)(CPU))find_symbol_32bit(library, "c_InitializeEffect_asm");
    c_InitializeCpuLoad_asm = (void (*)(CPU))find_symbol_32bit(library, "c_InitializeCpuLoad_asm");
    c_InitializeParameters_asm = (void (*)(CPU))find_symbol_32bit(library, "c_InitializeParameters_asm");
    c_InitializeMasterVolume_asm = (void (*)(CPU))find_symbol_32bit(library, "c_InitializeMasterVolume_asm");

    dwRenderedSamplesPerCall_asm = (uint32_t *)find_symbol_32bit(library, "dwRenderedSamplesPerCall_asm");

    c_MidiMessageShort_asm = (void (*)(CPU))find_symbol_32bit(library, "c_MidiMessageShort_asm");
    c_MidiMessageLong_asm = (void (*)(CPU))find_symbol_32bit(library, "c_MidiMessageLong_asm");

    c_RenderSamples_asm = (void (*)(CPU))find_symbol_32bit(library, "c_RenderSamples_asm");

    if ((c_ValidateSettings_asm == NULL) ||
        (c_InitializeDataFile_asm == NULL) ||
        (c_InitializeSynth_asm == NULL) ||
        (c_InitializeUnknown_asm == NULL) ||
        (c_InitializeEffect_asm == NULL) ||
        (c_InitializeCpuLoad_asm == NULL) ||
        (c_InitializeParameters_asm == NULL) ||
        (c_InitializeMasterVolume_asm == NULL) ||
        (dwRenderedSamplesPerCall_asm == NULL) ||
        (c_MidiMessageShort_asm == NULL) ||
        (c_MidiMessageLong_asm == NULL) ||
        (c_RenderSamples_asm == NULL)
       )
    {
        unload_library_32bit(library);
        library = NULL;
        return 0;
    }

    return 1;
}

EXTERNC void D77_FreeLibrary(void)
{
    if (library != NULL)
    {
        unload_library_32bit(library);
        library = NULL;
    }
}


EXTERNC void *D77_AllocateMemory(unsigned int size)
{
    return map_memory_32bit(size, 0);
}

EXTERNC void D77_FreeMemory(void *mem, unsigned int size)
{
    unmap_memory_32bit(mem, size);
}

#define CHECK_LIBRARY { if (library == NULL) exit(3); }

#else

#define CHECK_LIBRARY

#endif


EXTERNC void D77_ValidateSettings(void *lpSettings)
{
    _cpu *cpu;

    CHECK_LIBRARY

    cpu = x86_initialize_cpu();

    // __fastcall
    ecx = (uint32_t)(uintptr_t)lpSettings;

    c_ValidateSettings_asm(cpu);
}

EXTERNC uint32_t D77_InitializeDataFile(uint8_t *lpDataFile, uint32_t dwLength)
{
    _cpu *cpu;

    CHECK_LIBRARY

    cpu = x86_initialize_cpu();

    // __fastcall
    ecx = (uint32_t)(uintptr_t)lpDataFile;
    edx = dwLength;

    c_InitializeDataFile_asm(cpu);

    return eax;
}

EXTERNC uint32_t D77_InitializeSynth(uint32_t dwSamplingFrequency, uint32_t dwPolyphony, uint32_t dwTimeReso_unused)
{
    _cpu *cpu;

    CHECK_LIBRARY

    cpu = x86_initialize_cpu();

    // __fastcall
    ecx = dwSamplingFrequency;
    edx = dwPolyphony;

    esp -= 4;
    *((uint32_t *)REG2PTR(esp)) = dwTimeReso_unused;

    c_InitializeSynth_asm(cpu);

    return eax;
}

EXTERNC void D77_InitializeUnknown(uint32_t dwUnknown_unused)
{
    _cpu *cpu;

    CHECK_LIBRARY

    cpu = x86_initialize_cpu();

    // __fastcall
    ecx = dwUnknown_unused;

    c_InitializeUnknown_asm(cpu);
}

EXTERNC void D77_InitializeEffect(uint32_t dwEffect, uint32_t bEnabled)
{
    _cpu *cpu;

    CHECK_LIBRARY

    cpu = x86_initialize_cpu();

    // __fastcall
    ecx = dwEffect;
    edx = bEnabled;

    c_InitializeEffect_asm(cpu);
}

EXTERNC void D77_InitializeCpuLoad(uint32_t dwCpuLoadLow, uint32_t dwCpuLoadHigh)
{
    _cpu *cpu;

    CHECK_LIBRARY

    cpu = x86_initialize_cpu();

    // __fastcall
    ecx = dwCpuLoadLow;
    edx = dwCpuLoadHigh;

    c_InitializeCpuLoad_asm(cpu);
}

EXTERNC void D77_InitializeParameters(const void *lpParameters)
{
    _cpu *cpu;

    CHECK_LIBRARY

    cpu = x86_initialize_cpu();

    // __fastcall
    ecx = (uint32_t)(uintptr_t)lpParameters;

    c_InitializeParameters_asm(cpu);
}

EXTERNC void D77_InitializeMasterVolume(uint32_t dwMasterVolume)
{
    _cpu *cpu;

    CHECK_LIBRARY

    cpu = x86_initialize_cpu();

    // __fastcall
    ecx = dwMasterVolume;

    c_InitializeMasterVolume_asm(cpu);
}


EXTERNC uint32_t D77_GetRenderedSamplesPerCall(void)
{
#ifdef INDIRECT_64BIT
    CHECK_LIBRARY

    return *dwRenderedSamplesPerCall_asm;
#else
    return dwRenderedSamplesPerCall_asm;
#endif
}


EXTERNC uint32_t D77_MidiMessageShort(uint32_t dwMessage)
{
    _cpu *cpu;

    CHECK_LIBRARY

    cpu = x86_initialize_cpu();

    // __fastcall
    ecx = dwMessage;
    // MidiMessageShort_asm has a second (unused) parameter (uint8_t dwMidiPort)
    edx = 0;

    c_MidiMessageShort_asm(cpu);

    return eax;
}

EXTERNC uint32_t D77_MidiMessageLong(const uint8_t *lpMessage, uint32_t dwLength)
{
    _cpu *cpu;

    CHECK_LIBRARY

    cpu = x86_initialize_cpu();

    // __fastcall
    ecx = (uint32_t)(uintptr_t)lpMessage;
    edx = dwLength;

    // MidiMessageLong_asm has a third (unused) parameter (uint8_t dwMidiPort)
    esp -= 4;
    *((uint32_t *)REG2PTR(esp)) = 0;

    c_MidiMessageLong_asm(cpu);

    return eax;
}


EXTERNC uint32_t D77_RenderSamples(int16_t *lpSamples)
{
    _cpu *cpu;

    CHECK_LIBRARY

    cpu = x86_initialize_cpu();

    // __fastcall
    ecx = (uint32_t)(uintptr_t)lpSamples;

    c_RenderSamples_asm(cpu);

    return eax;
}

