#include "usart.h"

#ifdef	USART_ENABLED

void usart_init() {
	USART_INIT
}

void usart_putchar(int c) { }

char usart_getchar() { }

#endif

#endif
