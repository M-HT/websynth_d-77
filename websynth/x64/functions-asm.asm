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

%include "x64inc.inc"

extern ValidateSettings_asm
extern InitializeDataFile_asm
extern InitializeSynth_asm
extern InitializeUnknown_asm
extern InitializeEffect_asm
extern InitializeCpuLoad_asm
extern InitializeParameters_asm
extern InitializeMasterVolume_asm

extern MidiMessageShort_asm
extern MidiMessageLong_asm

extern RenderSamples_asm


global c_ValidateSettings
global c_InitializeDataFile
global c_InitializeSynth
global c_InitializeUnknown
global c_InitializeEffect
global c_InitializeCpuLoad
global c_InitializeParameters
global c_InitializeMasterVolume

global c_MidiMessageShort
global c_MidiMessageLong

global c_RenderSamples


%ifidn __OUTPUT_FORMAT__, win64

%macro PROLOG 0
        SECTION_PROLOG
        mov [rsp+FIRST_PARAMETER_OFFSET], rcx ; store first function parameter in reserved slot
        mov r11d, [rcx] ; load 32-bit stack pointer
%endm

%macro EPILOG 0
        mov rcx, [rsp+FIRST_PARAMETER_OFFSET] ; load first function parameter from reserved slot
        mov [rcx], r11d ; store 32-bit stack pointer
        SECTION_EPILOG
    .end_function: ; end of function for unwinding
%endm

%macro FASTCALL_PARAMS_1 0
    ; __fastcall
        mov ecx, edx
%endm

%macro FASTCALL_PARAMS_2 0
    ; __fastcall
        mov ecx, edx
        mov edx, r8d
%endm

%macro FASTCALL_PARAMS_3 0
    ; __fastcall
        mov ecx, edx
        mov edx, r8d
        PUSH32 r9d
%endm

%macro P_UNWIND 1
        P_UNWIND_INFO %1, %1.end_function, x_common
%endm

%else

%macro PROLOG 0
        push rbp ; save non-volatile register on stack
        push rbx ; save non-volatile register on stack
        push rdi ; save first function parameter on stack (which also alignes the stack to 16 bytes)
        mov r11d, [rdi] ; load 32-bit stack pointer
%endm

%macro EPILOG 0
        pop rdi ; restore first function parameter from stack
        mov [rdi], r11d ; store 32-bit stack pointer
        pop rbx ; restore non-volatile register from stack
        pop rbp ; restore non-volatile register from stack
        ret
%endm

%macro FASTCALL_PARAMS_1 0
        ; __fastcall
        mov ecx, esi
%endm

%macro FASTCALL_PARAMS_2 0
        ; __fastcall
        mov ecx, esi
        ;mov edx, edi
%endm

%macro FASTCALL_PARAMS_3 0
        ; __fastcall
        PUSH32 ecx
        mov ecx, esi
        ;mov edx, edi
%endm

%endif


%ifidn __OUTPUT_FORMAT__, elf64
section .note.GNU-stack noalloc noexec nowrite progbits
section .text progbits alloc exec nowrite align=16
%else
section .text code align=16
%endif

align 16
c_ValidateSettings:

; rsi/rdx = D77_SETINGS *lpSettings
; rdi/rcx = _stack *stack
; [rsp] = return address

        PROLOG

        FASTCALL_PARAMS_1

        CALL ValidateSettings_asm

        EPILOG

; end procedure c_ValidateSettings

align 16
c_InitializeDataFile:

; rdx/r8  = uint32_t dwLength
; rsi/rdx = uint8_t *lpDataFile
; rdi/rcx = _stack *stack
; [rsp] = return address

        PROLOG

        FASTCALL_PARAMS_2

        CALL InitializeDataFile_asm

        EPILOG

; end procedure c_InitializeDataFile

align 16
c_InitializeSynth:

; rcx/r9  = uint32_t dwTimeReso_unused
; rdx/r8  = uint32_t dwPolyphony
; rsi/rdx = uint32_t dwSamplingFrequency
; rdi/rcx = _stack *stack
; [rsp] = return address

        PROLOG

        FASTCALL_PARAMS_3

        CALL InitializeSynth_asm

        EPILOG

; end procedure c_InitializeSynth

align 16
c_InitializeUnknown:

; rsi/rdx = uint32_t dwUnknown_unused
; rdi/rcx = _stack *stack
; [rsp] = return address

        PROLOG

        FASTCALL_PARAMS_1

        CALL InitializeUnknown_asm

        EPILOG

; end procedure c_InitializeUnknown

align 16
c_InitializeEffect:

; rdx/r8  = uint32_t bEnabled
; rsi/rdx = enum D77_EFFECT dwEffect
; rdi/rcx = _stack *stack
; [rsp] = return address

        PROLOG

        FASTCALL_PARAMS_2

        CALL InitializeEffect_asm

        EPILOG

; end procedure c_InitializeEffect

align 16
c_InitializeCpuLoad:

; rdx/r8  = uint32_t dwCpuLoadHigh
; rsi/rdx = uint32_t dwCpuLoadLow
; rdi/rcx = _stack *stack
; [rsp] = return address

        PROLOG

        FASTCALL_PARAMS_2

        CALL InitializeCpuLoad_asm

        EPILOG

; end procedure c_InitializeCpuLoad

align 16
c_InitializeParameters:

; rsi/rdx = const D77_PARAMETERS *lpParameters
; rdi/rcx = _stack *stack
; [rsp] = return address

        PROLOG

        FASTCALL_PARAMS_1

        CALL InitializeParameters_asm

        EPILOG

; end procedure c_InitializeParameters

align 16
c_InitializeMasterVolume:

; rsi/rdx = uint32_t dwMasterVolume
; rdi/rcx = _stack *stack
; [rsp] = return address

        PROLOG

        FASTCALL_PARAMS_1

        CALL InitializeMasterVolume_asm

        EPILOG

; end procedure c_InitializeMasterVolume


align 16
c_MidiMessageShort:

; rsi/rdx = uint32_t dwMessage
; rdi/rcx = _stack *stack
; [rsp] = return address

        PROLOG

        FASTCALL_PARAMS_1
        ; MidiMessageShort_asm has a second (unused) parameter (uint8_t dwMidiPort)
        xor edx, edx ; dwMidiPort

        CALL MidiMessageShort_asm

        EPILOG

; end procedure c_MidiMessageShort

align 16
c_MidiMessageLong:

; rdx/r8  = uint32_t dwLength
; rsi/rdx = const uint8_t *lpMessage
; rdi/rcx = _stack *stack
; [rsp] = return address

        PROLOG

        FASTCALL_PARAMS_2
        ; MidiMessageLong_asm has a third (unused) parameter (uint8_t dwMidiPort)
        PUSH32 0 ; dwMidiPort

        CALL MidiMessageLong_asm

        EPILOG

; end procedure c_MidiMessageLong


align 16
c_RenderSamples:

; rsi/rdx = int16_t *lpSamples
; rdi/rcx = _stack *stack
; [rsp] = return address

        PROLOG

        FASTCALL_PARAMS_1

        CALL RenderSamples_asm

        EPILOG

; end procedure c_RenderSamples


%ifidn __OUTPUT_FORMAT__, win64

section .pdata rdata align=4
        P_UNWIND c_ValidateSettings
        P_UNWIND c_InitializeDataFile
        P_UNWIND c_InitializeSynth
        P_UNWIND c_InitializeUnknown
        P_UNWIND c_InitializeEffect
        P_UNWIND c_InitializeCpuLoad
        P_UNWIND c_InitializeParameters
        P_UNWIND c_InitializeMasterVolume

        P_UNWIND c_MidiMessageShort
        P_UNWIND c_MidiMessageLong

        P_UNWIND c_RenderSamples

section .xdata rdata align=8
align 8
x_common:
        X_UNWIND_INFO c_ValidateSettings

%endif

