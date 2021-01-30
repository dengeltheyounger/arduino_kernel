#include <avr/io.h>
#include <util/delay.h>

static inline void delay_ms(int ms_delay) {
	while (ms_delay--)
		_delay_ms(1);
}

static inline void set_outputs() {
	DDRB |= _BV(DDB5);
	DDRB |= _BV(DDB4);
	DDRB |= _BV(DDB3);
}

static inline void blink_led(int port, int ms_delay) {
	PORTB |= _BV(port);
	delay_ms(ms_delay);
	PORTB &= ~_BV(port);
}

void blink(void) {
	int delay = 1000;
	int step = 2;
	int multiply = 0;
	/* Change pins to output */
	set_outputs();

	while (1) {
		blink_led(PORTB5, delay);
		blink_led(PORTB4, delay);
		blink_led(PORTB3, delay);

		if (delay <= 25)
			multiply = 1;

		else if (delay >= 1000)
			multiply = 0;

		if (!multiply)
			delay /= 2;

		else
			delay *= 2;
	}
}
