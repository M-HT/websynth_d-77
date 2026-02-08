/**
 *
 *  Copyright (C) 2025-2026 Roman Pauer
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

#include "x64_stack.h"
#include <stdint.h>
#ifdef INDIRECT_64BIT
#include "functions-32bit.h"
#include <stdlib.h>
#endif


#ifdef INDIRECT_64BIT
static void *library = NULL;

static void (CCALL * c_ValidateSettings)(_stack *stack, void *lpSettings);
static uint32_t (CCALL * c_InitializeDataFile)(_stack *stack, uint8_t *lpDataFile, uint32_t dwLength);
static uint32_t (CCALL * c_InitializeSynth)(_stack *stack, uint32_t dwSamplingFrequency, uint32_t dwPolyphony, uint32_t dwTimeReso_unused);
static void (CCALL * c_InitializeUnknown)(_stack *stack, uint32_t dwUnknown_unused);
static void (CCALL * c_InitializeEffect)(_stack *stack, uint32_t dwEffect, uint32_t bEnabled);
static void (CCALL * c_InitializeCpuLoad)(_stack *stack, uint32_t dwCpuLoadLow, uint32_t dwCpuLoadHigh);
static void (CCALL * c_InitializeParameters)(_stack *stack, const void *lpParameters);
static void (CCALL * c_InitializeMasterVolume)(_stack *stack, uint32_t dwMasterVolume);

static uint32_t *dwRenderedSamplesPerCall_asm;

static uint32_t (CCALL * c_MidiMessageShort)(_stack *stack, uint32_t dwMessage);
static uint32_t (CCALL * c_MidiMessageLong)(_stack *stack, const uint8_t *lpMessage, uint32_t dwLength);

static uint32_t (CCALL * c_RenderSamples)(_stack *stack, int16_t *lpSamples);
#endif


#ifdef __cplusplus
extern "C" {
#endif

extern _stack *x86_initialize_stack(void);
extern void x86_deinitialize_stack(void);

#ifndef INDIRECT_64BIT
extern void CCALL c_ValidateSettings(_stack *stack, void *lpSettings);
extern uint32_t CCALL c_InitializeDataFile(_stack *stack, uint8_t *lpDataFile, uint32_t dwLength);
extern uint32_t CCALL c_InitializeSynth(_stack *stack, uint32_t dwSamplingFrequency, uint32_t dwPolyphony, uint32_t dwTimeReso_unused);
extern void CCALL c_InitializeUnknown(_stack *stack, uint32_t dwUnknown_unused);
extern void CCALL c_InitializeEffect(_stack *stack, uint32_t dwEffect, uint32_t bEnabled);
extern void CCALL c_InitializeCpuLoad(_stack *stack, uint32_t dwCpuLoadLow, uint32_t dwCpuLoadHigh);
extern void CCALL c_InitializeParameters(_stack *stack, const void *lpParameters);
extern void CCALL c_InitializeMasterVolume(_stack *stack, uint32_t dwMasterVolume);

extern uint32_t dwRenderedSamplesPerCall_asm;

extern uint32_t CCALL c_MidiMessageShort(_stack *stack, uint32_t dwMessage);
extern uint32_t CCALL c_MidiMessageLong(_stack *stack, const uint8_t *lpMessage, uint32_t dwLength);

extern uint32_t CCALL c_RenderSamples(_stack *stack, int16_t *lpSamples);
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

    c_ValidateSettings = (void (CCALL *)(_stack *stack, void *lpSettings))find_symbol_32bit(library, "c_ValidateSettings");
    c_InitializeDataFile = (uint32_t (CCALL *)(_stack *stack, uint8_t *lpDataFile, uint32_t dwLength))find_symbol_32bit(library, "c_InitializeDataFile");
    c_InitializeSynth = (uint32_t (CCALL *)(_stack *stack, uint32_t dwSamplingFrequency, uint32_t dwPolyphony, uint32_t dwTimeReso_unused))find_symbol_32bit(library, "c_InitializeSynth");
    c_InitializeUnknown = (void (CCALL *)(_stack *stack, uint32_t dwUnknown_unused))find_symbol_32bit(library, "c_InitializeUnknown");
    c_InitializeEffect = (void (CCALL *)(_stack *stack, uint32_t dwEffect, uint32_t bEnabled))find_symbol_32bit(library, "c_InitializeEffect");
    c_InitializeCpuLoad = (void (CCALL *)(_stack *stack, uint32_t dwCpuLoadLow, uint32_t dwCpuLoadHigh))find_symbol_32bit(library, "c_InitializeCpuLoad");
    c_InitializeParameters = (void (CCALL *)(_stack *stack, const void *lpParameters))find_symbol_32bit(library, "c_InitializeParameters");
    c_InitializeMasterVolume = (void (CCALL *)(_stack *stack, uint32_t dwMasterVolume))find_symbol_32bit(library, "c_InitializeMasterVolume");

    dwRenderedSamplesPerCall_asm = (uint32_t *)find_symbol_32bit(library, "dwRenderedSamplesPerCall_asm");

    c_MidiMessageShort = (uint32_t (CCALL *)(_stack *stack, uint32_t dwMessage))find_symbol_32bit(library, "c_MidiMessageShort");
    c_MidiMessageLong = (uint32_t (CCALL *)(_stack *stack, const uint8_t *lpMessage, uint32_t dwLength))find_symbol_32bit(library, "c_MidiMessageLong");

    c_RenderSamples = (uint32_t (CCALL *)(_stack *stack, int16_t *lpSamples))find_symbol_32bit(library, "c_RenderSamples");

    if ((c_ValidateSettings == NULL) ||
        (c_InitializeDataFile == NULL) ||
        (c_InitializeSynth == NULL) ||
        (c_InitializeUnknown == NULL) ||
        (c_InitializeEffect == NULL) ||
        (c_InitializeCpuLoad == NULL) ||
        (c_InitializeParameters == NULL) ||
        (c_InitializeMasterVolume == NULL) ||
        (dwRenderedSamplesPerCall_asm == NULL) ||
        (c_MidiMessageShort == NULL) ||
        (c_MidiMessageLong == NULL) ||
        (c_RenderSamples == NULL)
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


EXTERNC void CCALL D77_ValidateSettings(void *lpSettings)
{
    _stack *stack;

    CHECK_LIBRARY

    stack = x86_initialize_stack();

    c_ValidateSettings(stack, lpSettings);
}

EXTERNC uint32_t CCALL D77_InitializeDataFile(uint8_t *lpDataFile, uint32_t dwLength)
{
    _stack *stack;

    CHECK_LIBRARY

    stack = x86_initialize_stack();

    return c_InitializeDataFile(stack, lpDataFile, dwLength);
}

EXTERNC uint32_t CCALL D77_InitializeSynth(uint32_t dwSamplingFrequency, uint32_t dwPolyphony, uint32_t dwTimeReso_unused)
{
    _stack *stack;

    CHECK_LIBRARY

    stack = x86_initialize_stack();

    return c_InitializeSynth(stack, dwSamplingFrequency, dwPolyphony, dwTimeReso_unused);
}

EXTERNC void CCALL D77_InitializeUnknown(uint32_t dwUnknown_unused)
{
    _stack *stack;

    CHECK_LIBRARY

    stack = x86_initialize_stack();

    c_InitializeUnknown(stack, dwUnknown_unused);
}

EXTERNC void CCALL D77_InitializeEffect(uint32_t dwEffect, uint32_t bEnabled)
{
    _stack *stack;

    CHECK_LIBRARY

    stack = x86_initialize_stack();

    c_InitializeEffect(stack, dwEffect, bEnabled);
}

EXTERNC void CCALL D77_InitializeCpuLoad(uint32_t dwCpuLoadLow, uint32_t dwCpuLoadHigh)
{
    _stack *stack;

    CHECK_LIBRARY

    stack = x86_initialize_stack();

    c_InitializeCpuLoad(stack, dwCpuLoadLow, dwCpuLoadHigh);
}

EXTERNC void CCALL D77_InitializeParameters(const void *lpParameters)
{
    _stack *stack;

    CHECK_LIBRARY

    stack = x86_initialize_stack();

    c_InitializeParameters(stack, lpParameters);
}

EXTERNC void CCALL D77_InitializeMasterVolume(uint32_t dwMasterVolume)
{
    _stack *stack;

    CHECK_LIBRARY

    stack = x86_initialize_stack();

    c_InitializeMasterVolume(stack, dwMasterVolume);
}


EXTERNC uint32_t CCALL D77_GetRenderedSamplesPerCall(void)
{
#ifdef INDIRECT_64BIT
    CHECK_LIBRARY

    return *dwRenderedSamplesPerCall_asm;
#else
    return dwRenderedSamplesPerCall_asm;
#endif
}


EXTERNC uint32_t CCALL D77_MidiMessageShort(uint32_t dwMessage)
{
    _stack *stack;

    CHECK_LIBRARY

    stack = x86_initialize_stack();

    return c_MidiMessageShort(stack, dwMessage);
}

EXTERNC uint32_t CCALL D77_MidiMessageLong(const uint8_t *lpMessage, uint32_t dwLength)
{
    _stack *stack;

    CHECK_LIBRARY

    stack = x86_initialize_stack();

    return c_MidiMessageLong(stack, lpMessage, dwLength);
}


EXTERNC uint32_t CCALL D77_RenderSamples(int16_t *lpSamples)
{
    _stack *stack;

    CHECK_LIBRARY

    stack = x86_initialize_stack();

    return c_RenderSamples(stack, lpSamples);
}

