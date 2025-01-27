# WebSynth D-77

[WebSynth](https://web.archive.org/web/20010506012047/http://www.faith.co.jp/websyn.html) D-77 made by [FAITH,INC.](https://web.archive.org/web/20010429192758/http://www.faith.co.jp/) is a [software synthesizer](https://en.wikipedia.org/wiki/Software_synthesizer) that was bundled with some computers and sound cards.
There's an [article](https://ja.wikipedia.org/wiki/WebSynth) about it on Wikipedia (in japanese).

This project uses a disassembled (or statically recompiled) version of the synthesizer to build some tools (like Linux ALSA driver).


The source code is released with [MIT license](https://spdx.org/licenses/MIT.html).

<hr/>

The projects consists of following parts:

* **websynth**
  * Disassembled (**x86**) / statically recompiled (**llasm**) version of WebSynth D-77 (v1.1 for Windows 2000) synthesizer.
  * This allows using the software synthesizer on other *CPU* architectures (32-bit, 64-bit) and platforms.
  * 64-bit version only works with 32-bit addresses - the code and all data it uses must be in the first 2GB of memory space.
* **d77_alsadrv**
  * Linux daemon which provides [ALSA](https://en.wikipedia.org/wiki/Advanced_Linux_Sound_Architecture) MIDI sequencer interface using *websynth*.
  * It requires the WebSynth D-77 datafile *dswebWDM.dat* (or *dswebsyn.dat*).
  * Compilation for x86 requires [gcc](https://gcc.gnu.org/) and [nasm](https://www.nasm.us/).
  * Compilation for other architectures requires [gcc](https://gcc.gnu.org/), [llvm](https://llvm.org/) and [llasm](https://github.com/M-HT/SR/tree/master/llasm) (from [SR project](https://github.com/M-HT/SR)).
* **d77_pcmconvert**
  * Tool to convert [Standard MIDI File](https://www.midi.org/specifications-old/item/standard-midi-files-smf) to *PCM* (*WAV* or *RAW*) using *websynth*.
  * It requires the WebSynth D-77 datafile *dswebWDM.dat* (or *dswebsyn.dat*).
  * Compilation for x86 requires [gcc](https://gcc.gnu.org/) and [nasm](https://www.nasm.us/).
  * Compilation for other architectures requires [gcc](https://gcc.gnu.org/), [llvm](https://llvm.org/) and [llasm](https://github.com/M-HT/SR/tree/master/llasm) (from [SR project](https://github.com/M-HT/SR)).
* **datafile**
  * WebSynth D-77 (v1.1 for Windows 2000) datafile *dswebWDM.dat*
* **documentation**
  * Websynth soundmap (official) and MIDI implementation (unofficial)
* **websynth-gen**
  * Files required to generate disassembled / statically recompiled version of the synthesizer from original (WebSynth D-77 v1.1 for Windows 2000) executable *dswbsWDM.exe*.
  * [SRW tool](https://github.com/M-HT/SR/tree/master/SRW) (from [SR project](https://github.com/M-HT/SR)) is required.
