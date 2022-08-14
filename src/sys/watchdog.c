#include "sys/watchdog.h"

ISR(WDT_vect) {
#if DEBUG == 1
	println("Watchdog reset detected.",
		STRLEN("Watchdog reset detected."));
#endif
}

int watchdog_reset_detected() {
	return (MCUSR & (WATCHDOG_SYSTEM_RESET) == 1);
}

void init_watchdog() {
	// Set the prescaler and set to interrupt/reset mode
	cli();
	watchdog_reset();
	WDTCSR |= WDT_CHANGE_ENABLE | WDT_RESET_ENABLE; 
	WDTCSR |= (WDT_RESET_ENABLE | WDT_TIMEOUT_8);
	WDTCSR |= WDT_INTERRUPT_ENABLE;
	sei();
}
