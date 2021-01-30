#ifndef	UART_H
#define	UART_H
#include <stdio.h>
#include <avr/io.h>
#define BAUD	9600
#include <util/setbaud.h>

void uart_init();

int uart_putchar(char c, FILE *stream);
int uart_getchar(FILE *stream);

extern FILE uart_output;
extern FILE uart_input;

#endif
