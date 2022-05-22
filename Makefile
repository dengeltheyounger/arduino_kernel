TARGET = avr
CC = $(TARGET)-gcc
PROJDIRS := mem usr sys tmr

CFLAGS = -mmcu=atmega328p

OBJS = $(wildcard *.c) $(foreach DIR,$(PROJDIRS),$(wildcard $(PROJDIRS)/*.c))

%.o: %.c 
	$(CC) $(CFLAGS) -c -o $@ $< $(CFLAGS)

%.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $< $(CFLAGS)

kernel: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)
	$(OCOPY) -O ihex -R .eeprom kernel kernel.hex


install: kernel
	$(ADUDE) -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -U flash:w:kernel.hex

.PHONY: clean

clean:
	rm kernel *.o *.hex
