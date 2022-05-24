TARGET := avr
CC := $(TARGET)-gcc
PROJDIRS := mem usr sys tmr
OCOPY := avr-objcopy
INSTALLER := avrdue

CFLAGS = -mmcu=atmega328p

SOURCEFILES := $(wildcard *.c) $(wildcard .S) $(wildcard */*.c) $(wildcard */*.S)

OBJS := $(SOURCEFILES)

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $< $(CFLAGS)

%.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $< $(CFLAGS)

kernel: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)
	$(OCOPY) -O ihex -R .eeprom kernel kernel.hex


install: kernel
	$(INSTALLER) -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -U flash:w:kernel.hex

.PHONY: clean

clean:
	rm kernel *.o *.hex
