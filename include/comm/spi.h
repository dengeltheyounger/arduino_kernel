#ifndef	SPI_H
#define	SPI_H
#include <avr/io.h>
#include <stdint.h>

#define	SPI_SCK		PB5
#define	SPI_MISO	PB4
#define	SPI_MOSI	PB3
#define	SPI_SS		PB2

#define	SPI_SS_LOW()	PORTB &= ~(1 << SPI_SS)
#define	SPI_SS_HIGH()	PORTB |= (1 << SPI_SS)

void spi_init();

uint8_t do_spi(uint8_t byte);

#endif
