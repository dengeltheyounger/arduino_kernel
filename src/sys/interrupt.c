#include <avr/interrupt.h>
#include "comm/usart.h"

ISR(__vector_default) {
	println("Entered default interrupt",
		STRLEN("Entered default interrupt"));
}
