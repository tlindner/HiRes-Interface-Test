#!/bin/sh

set -v

rm joy.bin
cmoc -i joy.c hiresjoy.asm
rm joy.dsk
decb dskini joy.dsk
decb copy -2b joy.bin joy.dsk,JOY.BIN
