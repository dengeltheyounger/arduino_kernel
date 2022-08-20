TARGET := avr
CC := $(TARGET)-gcc
INCLUDE := include/
USER_INCLUDE := usr/include/
PROJDIRS := mem usr sys tmr net comm
OCOPY := avr-objcopy
INSTALLER := avrdude
GLOBAL_DEFINES := -DUSE_EEPROM_MEMORY=0 -DDEBUG=1 -DUSE_SOFTWARE_TIMER=1

CFLAGS = -mmcu=atmega328p -I$(INCLUDE) -I$(USER_INCLUDE) $(GLOBAL_DEFINES) -Os

SOURCEFILES := $(shell find . -name "*.c")
SOURCEFILES += $(shell find . -name "*.S")

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
	rm kernel kernel.hex
