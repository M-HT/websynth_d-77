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

global rand_asm
global _ftol_asm


%ifidn __OUTPUT_FORMAT__, elf32
section .note.GNU-stack noalloc noexec nowrite progbits
section .text progbits alloc exec nowrite align=16
%else
section .text code align=16
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
        retn

; end procedure rand_asm


align 16
_ftol_asm:

; st0   = num
; [esp] = return address

        sub esp, byte 12
        fstcw [esp + 10] ; save original control word
        wait
        mov ax, [esp + 10]
        or ah, 0x0c ; set rounding control to round to zero
        mov [esp + 8], ax
        fldcw [esp + 8]
        fistp qword [esp]
        fldcw [esp + 10] ; restore original control word
        mov eax, [esp]
        mov edx, [esp + 4]
        add esp, byte 12
        retn

; end procedure _ftol_asm


%ifidn __OUTPUT_FORMAT__, elf32
section .data progbits alloc noexec write align=4
%else
section .data data align=4
%endif

align 4
rand_value:
dd 1
