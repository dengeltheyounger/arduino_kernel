TARGET := avr
CC := $(TARGET)-gcc
INCLUDE := include/
USER_INCLUDE := usr/include/
PROJDIRS := mem usr sys tmr
OCOPY := avr-objcopy
INSTALLER := avrdue

CFLAGS = -mmcu=atmega328p -I$(INCLUDE)

SOURCEFILES := $(shell find . -name "*.c")
SOURCEFILES += $(shell find . -name "*.S")

OBJS := $(SOURCEFILES)

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $< $(CFLAGS)

%.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $< $(CFLAGS)

kernel: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) -I $(INCLUDE) -I $(USER_INCLUDE)
	$(OCOPY) -O ihex -R .eeprom kernel kernel.hex


install: kernel
	$(INSTALLER) -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -U flash:w:kernel.hex

.PHONY: clean

clean:
	rm kernel kernel.hex
