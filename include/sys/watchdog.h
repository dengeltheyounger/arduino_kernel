#ifndef	WATCHDOG_H
#define	WATCHDOG_H
#include "comm/usart.h"
#include <avr/interrupt.h>
#include <avr/io.h>

#define	WATCHDOG_SYSTEM_RESET	(1 << 3)
#define	WDT_TIMEOUT_8		((1 << 5) | (1 << 0))
#define	WDT_INTERRUPT_ENABLE	(1 << 6)
#define	WDT_RESET_ENABLE	(1 << 3)
#define	WDT_CHANGE_ENABLE	(1 << 4)

static inline void watchdog_reset() {
	asm("WDR\n\t");
}

int watchdog_reset_detected();

void init_watchdog();

#endif
