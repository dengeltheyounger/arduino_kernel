CC =avr-gcc
OCOPY =avr-objcopy
ADUDE =avrdude
CFLAGS := -mmcu=atmega328p -DF_CPU=16000000UL -O0 -fno-stack-protector
CFLAGS += -fshort-enums -fno-pie -ggdb
OBJS=arduino_kernel.o blink.o main.o context.o tasks.o timer.o

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
	rm kernel *.o
