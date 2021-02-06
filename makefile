kernel.hex:
	avr-gcc -o kernel *.S *.c -mmcu=atmega328p -DF_CPU=16000000UL -fno-stack-protector -Os -fshort-enums
	avr-objcopy -O ihex -R .eeprom kernel kernel.hex
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -U flash:w:kernel.hex
