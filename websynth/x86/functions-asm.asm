;;
;;  Copyright (C) 2025 Roman Pauer
;;
;;  Permission is hereby granted, free of charge, to any person obtaining a copy of
;;  this software and associated documentation files (the "Software"), to deal in
;;  the Software without restriction, including without limitation the rights to
;;  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
;;  of the Software, and to permit persons to whom the Software is furnished to do
;;  so, subject to the following conditions:
;;
;;  The above copyright notice and this permission notice shall be included in all
;;  copies or substantial portions of the Software.
;;
;;  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
;;  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
;;  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
;;  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
;;  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
;;  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
;;  SOFTWARE.
;;

extern ValidateSettings_asm
extern InitializeDataFile_asm
extern InitializeSynth_asm
extern InitializeUnknown_asm
extern InitializeEffect_asm
extern InitializeCpuLoad_asm
extern InitializeParameters_asm
extern InitializeMasterVolume_asm

extern dwRenderedSamplesPerCall_asm

extern MidiMessageShort_asm
extern MidiMessageLong_asm

extern RenderSamples_asm


global D77_ValidateSettings
global _D77_ValidateSettings

global D77_InitializeDataFile
global _D77_InitializeDataFile

global D77_InitializeSynth
global _D77_InitializeSynth

global D77_InitializeUnknown
global _D77_InitializeUnknown

global D77_InitializeEffect
global _D77_InitializeEffect

global D77_InitializeCpuLoad
global _D77_InitializeCpuLoad

global D77_InitializeParameters
global _D77_InitializeParameters

global D77_InitializeMasterVolume
global _D77_InitializeMasterVolume


global D77_GetRenderedSamplesPerCall
global _D77_GetRenderedSamplesPerCall


global D77_MidiMessageShort
global _D77_MidiMessageShort

global D77_MidiMessageLong
global _D77_MidiMessageLong


global D77_RenderSamples
global _D77_RenderSamples


%ifidn __OUTPUT_FORMAT__, elf32
section .note.GNU-stack noalloc noexec nowrite progbits
section .text progbits alloc exec nowrite align=16
%else
section .text code align=16
%endif

align 16
D77_ValidateSettings:
_D77_ValidateSettings:

; [esp +   4] = D77_SETINGS *lpSettings
; [esp      ] = return address

        ; __fastcall
        mov ecx, [esp + 4]

        jmp ValidateSettings_asm

; end procedure D77_ValidateSettings

align 16
D77_InitializeDataFile:
_D77_InitializeDataFile:

; [esp + 2*4] = uint32_t dwLength
; [esp +   4] = uint8_t *lpDataFile
; [esp      ] = return address

        ; __fastcall
        mov ecx, [esp + 4]
        mov edx, [esp + 2*4]

        jmp InitializeDataFile_asm

; end procedure D77_InitializeDataFile

align 16
D77_InitializeSynth:
_D77_InitializeSynth:

; [esp + 3*4] = uint32_t dwTimeReso_unused
; [esp + 2*4] = uint32_t dwPolyphony
; [esp +   4] = uint32_t dwSamplingFrequency
; [esp      ] = return address

        ; __fastcall
        mov ecx, [esp + 4]
        mov edx, [esp + 2*4]
        push dword [esp + 3*4]

        call InitializeSynth_asm

        retn

; end procedure D77_InitializeSynth

align 16
D77_InitializeUnknown:
_D77_InitializeUnknown:

; [esp +   4] = uint32_t dwUnknown_unused
; [esp      ] = return address

        ; __fastcall
        mov ecx, [esp + 4]

        jmp InitializeUnknown_asm

; end procedure D77_InitializeUnknown

D77_InitializeEffect:
_D77_InitializeEffect:

; [esp + 2*4] = uint32_t bEnabled
; [esp +   4] = enum D77_EFFECT dwEffect
; [esp      ] = return address

        ; __fastcall
        mov ecx, [esp + 4]
        mov edx, [esp + 2*4]

        jmp InitializeEffect_asm

; end procedure D77_InitializeEffect

D77_InitializeCpuLoad:
_D77_InitializeCpuLoad:

; [esp + 2*4] = uint32_t dwCpuLoadHigh
; [esp +   4] = uint32_t dwCpuLoadLow
; [esp      ] = return address

        ; __fastcall
        mov ecx, [esp + 4]
        mov edx, [esp + 2*4]

        jmp InitializeCpuLoad_asm

; end procedure D77_InitializeCpuLoad

align 16
D77_InitializeParameters:
_D77_InitializeParameters:

; [esp +   4] = const D77_PARAMETERS *lpParameters
; [esp      ] = return address

        ; __fastcall
        mov ecx, [esp + 4]

        jmp InitializeParameters_asm

; end procedure D77_InitializeParameters

align 16
D77_InitializeMasterVolume:
_D77_InitializeMasterVolume:

; [esp +   4] = uint32_t dwMasterVolume
; [esp      ] = return address

        ; __fastcall
        mov ecx, [esp + 4]

        jmp InitializeMasterVolume_asm

; end procedure D77_InitializeMasterVolume


D77_GetRenderedSamplesPerCall:
_D77_GetRenderedSamplesPerCall:

; [esp      ] = return address

        mov eax, [dwRenderedSamplesPerCall_asm]
        retn

; end procedure D77_GetRenderedSamplesPerCall


D77_MidiMessageShort:
_D77_MidiMessageShort:

; [esp +   4] = uint32_t dwMessage
; [esp      ] = return address

        ; __fastcall
        mov ecx, [esp + 4]
        ; MidiMessageShort_asm has a second (unused) parameter (uint8_t dwMidiPort)
        xor edx, edx

        jmp MidiMessageShort_asm

; end procedure D77_MidiMessageShort

align 16
D77_MidiMessageLong:
_D77_MidiMessageLong:

; [esp + 2*4] = uint32_t dwLength
; [esp +   4] = const uint8_t *lpMessage
; [esp      ] = return address

        ; __fastcall
        mov ecx, [esp + 4]
        mov edx, [esp + 2*4]
        ; MidiMessageLong_asm has a third (unused) parameter (uint8_t dwMidiPort)
        push byte 0

        call MidiMessageLong_asm

        retn

; end procedure D77_MidiMessageLong


align 16
D77_RenderSamples:
_D77_RenderSamples:

; [esp +   4] = int16_t *lpSamples
; [esp      ] = return address

        ; __fastcall
        mov ecx, [esp + 4]

        jmp RenderSamples_asm

; end procedure D77_RenderSamples


