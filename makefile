# Makefile

TARGET = hrjoy
BIN = $(TARGET).bin
DSK = $(TARGET).dsk

C_SRCS = hrjoy.c
ASM_SRCS = hiresjoy.asm hiresjoy_cm3.asm

.PHONY: all clean

all: $(DSK)

hrjoy.c: hiresjoyIntrf.h

$(BIN): $(C_SRCS) $(ASM_SRCS)
	cmoc -i $(C_SRCS) $(ASM_SRCS)

$(DSK): $(BIN) normjoy.bas
	rm -f $(DSK)
	decb dskini $(DSK)
	decb copy -2b $(BIN) $(DSK),HRJOY.BIN
	decb copy -t normjoy.bas $(DSK),NORMJOY.BAS

clean:
	rm -f \
		$(BIN) \
		$(DSK) \
		$(TARGET).link \
		$(TARGET).map \
		$(TARGET).lst \
		$(TARGET).o \
		$(TARGET).s \
		hiresjoy.lst \
		hiresjoy.o \
		hiresjoy_cm3.lst \
		hiresjoy_cm3.o
