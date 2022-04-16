#!/bin/sh

set -v

rm joy.bin
cmoc -i joy.c hiresjoy.asm hiresjoy_cm3.asm
rm joy.dsk
decb dskini joy.dsk
decb copy -2b joy.bin joy.dsk,JOY.BIN
decb copy -t joy.bas joy.dsk,JOY.BAS
