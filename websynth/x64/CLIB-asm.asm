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

global rand_asm
global _ftol_asm


%ifidn __OUTPUT_FORMAT__, elf64
section .note.GNU-stack noalloc noexec nowrite progbits
section .text progbits alloc exec nowrite align=16
%else
section .text code align=16
%endif
%ifidn __OUTPUT_FORMAT__, win64
section_prolog:
        SECTION_PROLOG
%endif

align 16
rand_asm:

; [esp] = return address

        mov eax, [rand_value]
        imul eax, 214013
        add eax, 2531011
        mov [rand_value], eax
        sar eax, 16
        and eax, 0x7fff
        RET

; end procedure rand_asm


align 16
_ftol_asm:

; st0   = num
; [esp] = return address

        sub r11d, byte 12
        fstcw [r11d + 10] ; save original control word
        wait
        mov ax, [r11d + 10]
        or ah, 0x0c ; set rounding control to round to zero
        mov [r11d + 8], ax
        fldcw [r11d + 8]
        fistp qword [r11d]
        fldcw [r11d + 10] ; restore original control word
        mov eax, [r11d]
        mov edx, [r11d + 4]
        add r11d, byte 12
        RET

; end procedure _ftol_asm

%ifidn __OUTPUT_FORMAT__, win64
section_end:

section .pdata rdata align=4
        P_UNWIND_INFO section_prolog, section_end, x_common
section .xdata rdata align=8
align 8
x_common:
        X_UNWIND_INFO section_prolog
%endif


%ifidn __OUTPUT_FORMAT__, elf64
section .data progbits alloc noexec write align=4
%else
section .data data align=4
%endif

align 4
rand_value:
dd 1

