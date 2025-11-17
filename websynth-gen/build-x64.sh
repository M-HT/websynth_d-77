#! /bin/sh
cd "`echo $0 | sed 's/\/[^\/]*$//'`"
cp x64/*.sci ./
./SRW.exe dswbsWDM.exe-original dswbsWDM.asm >a.a 2>b.a
rm *.sci
./compact_source.py
nasm dswbsWDM.asm -felf64 -Ox -w+orphan-labels -w-number-overflow -i../websynth/x64 -o dswbsWDM.o 2>a.a
./repair_short_jumps.py
nasm dswbsWDM.asm -felf64 -Ox -w+orphan-labels -w-number-overflow -i../websynth/x64 -o dswbsWDM.o 2>a.a
./repair_short_jumps.py
nasm dswbsWDM.asm -felf64 -Ox -w+orphan-labels -w-number-overflow -i../websynth/x64 -o dswbsWDM.o 2>a.a
./repair_short_jumps.py
rm *.a
rm dswbsWDM.resdump
