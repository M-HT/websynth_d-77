%include "x86inc.inc"
%include "misc.inc"
%include "extern.inc"
global InitializeDataFile_asm
global _InitializeDataFile_asm
global InitializeSynth_asm
global _InitializeSynth_asm
global MidiMessageShort_asm
global _MidiMessageShort_asm
global MidiMessageLong_asm
global _MidiMessageLong_asm
global RenderSamples_asm
global _RenderSamples_asm
global InitializeMasterVolume_asm
global _InitializeMasterVolume_asm
global InitializeEffect_asm
global _InitializeEffect_asm
global InitializeUnknown_asm
global _InitializeUnknown_asm
global InitializeCpuLoad_asm
global _InitializeCpuLoad_asm
global InitializeParameters_asm
global _InitializeParameters_asm
global ValidateSettings_asm
global _ValidateSettings_asm
global dwRenderedSamplesPerCall_asm
global _dwRenderedSamplesPerCall_asm


%ifidn __OUTPUT_FORMAT__, elf32
section .note.GNU-stack noalloc noexec nowrite progbits
%endif

%ifidn __OUTPUT_FORMAT__, elf32
section .text progbits alloc exec nowrite align=16
%else
section .text code align=16
%endif
imagebase1000:
%include "seg01.inc"

%ifidn __OUTPUT_FORMAT__, elf32
section .rdata progbits alloc noexec nowrite align=8
%else
section .rdata rdata align=8
%endif
%include "seg02.inc"

%ifidn __OUTPUT_FORMAT__, elf32
section .data progbits alloc noexec write align=4
%else
section .data data align=4
%endif
%include "seg03.inc"

%ifidn __OUTPUT_FORMAT__, elf32
section .bss nobits alloc noexec write align=4
%else
section .bss bss align=4
%endif
%include "seg05.inc"
