#ifndef	TIMER_H
#define	TIMER_H
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>

/* For now, it is assumed that the timer will be set for 4 ms.
 * The reason for this is because it allows greater resolution
 * since a prescaler does not need to be used. However, in the
 * future, it would be a good idea to allow values greater than 4.
 */

// It is assumed that the kernel will turn on interrupts
uint8_t set_timer();

#endif
