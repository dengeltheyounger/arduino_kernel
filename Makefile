CC = $(TARGET)-gcc
PROJDIRS := mem usr kernel arch/$(TARGET)/

SRCFILES := $(shell find $(PROJDIRS) -type f -name "\*.c")
SRCFILES += $(shell find $(PROJDIRS) -type f -name "\*.S")
HDRFILES := $(shell find $(PROJDIRS) -type f -name "\*.h")

OBJS := $(patsubst (%.c,%.S),%.o $(SRCFILES))

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
