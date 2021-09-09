CC = avr-gcc
OCOPY = avr-objcopy
ADUDE = avrdude
CFLAGS := -mmcu=atmega328p -DF_CPU=16000000UL -fno-stack-protector
CFLAGS += -fshort-enums -fno-pie -Os -ggdb
OBJS := arduino_kernel.o blink.o main.o tasks.o timer.o timer_isr.o \
	system.o request.o housekeeper_prelude.o housekeeping.o \

%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.S
	$(CC) -c -o $@ $< $(CFLAGS)

kernel: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)
	$(OCOPY) -O ihex -R .eeprom kernel kernel.hex


install: kernel
	$(ADUDE) -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -U flash:w:kernel.hex

.PHONY: clean

clean:
	rm kernel *.o *.hex
