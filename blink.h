#ifndef	BLINK_H
#define	BLINK_H
#include <avr/io.h>
#ifndef F_CPU
#define F_CPU	16000000UL
#endif
#include "system.h"

void blink1(void);
void blink2(void);
void blink3(void);
void blink4(void);

#endif
