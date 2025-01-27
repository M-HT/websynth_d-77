#! /bin/sh
cd "`echo $0 | sed 's/\/[^\/]*$//'`"
cp x86/*.sci ./
./SRW.exe dswbsWDM.exe-original dswbsWDM.asm >a.a 2>b.a
rm *.sci
./compact_source.py
rm *.a
rm dswbsWDM.resdump
