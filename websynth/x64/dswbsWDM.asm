%include "x64inc.inc"
%include "misc.inc"
%include "extern.inc"
global InitializeDataFile_asm
global InitializeSynth_asm
global MidiMessageShort_asm
global MidiMessageLong_asm
global RenderSamples_asm
global InitializeMasterVolume_asm
global InitializeEffect_asm
global InitializeUnknown_asm
global InitializeCpuLoad_asm
global InitializeParameters_asm
global ValidateSettings_asm
global dwRenderedSamplesPerCall_asm


%ifidn __OUTPUT_FORMAT__, elf64
section .note.GNU-stack noalloc noexec nowrite progbits
%endif

%ifidn __OUTPUT_FORMAT__, elf64
section .text progbits alloc exec nowrite align=16
%else
section .text code align=16
%endif
%ifidn __OUTPUT_FORMAT__, win64
section_prolog_0:
SECTION_PROLOG
%endif
imagebase1000:
%include "seg01.inc"
%ifidn __OUTPUT_FORMAT__, win64
section_end_0:
%endif

%ifidn __OUTPUT_FORMAT__, elf64
section .rdata progbits alloc noexec nowrite align=8
%else
section .rdata rdata align=8
%endif
%include "seg02.inc"

%ifidn __OUTPUT_FORMAT__, elf64
section .data progbits alloc noexec write align=4
%else
section .data data align=4
%endif
%include "seg03.inc"

%ifidn __OUTPUT_FORMAT__, elf64
section .bss nobits alloc noexec write align=4
%else
section .bss bss align=4
%endif
%include "seg05.inc"

%ifidn __OUTPUT_FORMAT__, win64
section .pdata rdata align=4
P_UNWIND_INFO section_prolog_0, section_end_0, x_common
section .xdata rdata align=8
align 8
x_common:
X_UNWIND_INFO section_prolog_0
%endif
