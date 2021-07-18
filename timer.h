#ifndef	TIMER_H
#define	TIMER_H
#include <avr/io.h>
#include <avr/interrupt.h>
#ifndef F_CPU
#define F_CPU	16000000UL
#endif
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>

struct timer {
	// The total number of ms
	uint32_t time;
};

extern struct timer system_time;

/* The timer used is timer 2 on output a. It pulses once every millisecond.
 * Every four millisecond it calls on housekeeping
 */

// It is assumed that the kernel will turn on interrupts
uint8_t set_timer();

#endif
