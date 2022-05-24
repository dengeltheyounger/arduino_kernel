TARGET := avr
CC := $(TARGET)-gcc
INCLUDE := include/
PROJDIRS := mem usr sys tmr
OCOPY := avr-objcopy
INSTALLER := avrdue

CFLAGS = -mmcu=atmega328p -I$(INCLUDE)

SOURCEFILES := $(shell find src/ -name "*.c" -o -name "*.S")

OBJS := $(SOURCEFILES)

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $< $(CFLAGS)

%.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $< $(CFLAGS)

kernel: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) -I $(INCLUDE)
	$(OCOPY) -O ihex -R .eeprom kernel kernel.hex


install: kernel
	$(INSTALLER) -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -U flash:w:kernel.hex

.PHONY: clean

clean:
	rm kernel kernel.hex
