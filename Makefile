TARGET := avr
CC := $(TARGET)-gcc
INCLUDE := include/
PROJDIRS := mem usr sys tmr
OCOPY := avr-objcopy
INSTALLER := avrdue

CFLAGS = -mmcu=atmega328p

SOURCEFILES := $(wildcard *.c) $(wildcard .S) $(wildcard */*.c) $(wildcard */*.S)

OBJS := $(SOURCEFILES)

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $< $(CFLAGS) -I $(INCLUDE)

%.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $< $(CFLAGS) -I $(INCLUDE

kernel: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) -I $(INCLUDE)
	$(OCOPY) -O ihex -R .eeprom kernel kernel.hex


install: kernel
	$(INSTALLER) -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -U flash:w:kernel.hex

.PHONY: clean

clean:
	rm kernel kernel.hex
