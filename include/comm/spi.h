#ifndef	SPI_H
#define	SPI_H
#include <avr/io.h>

#if USE_ETHERNET == 1

#define	SPI_SCK		PB5
#define	SPI_MISO	PB4
#define	SPI_MOSI	PB3
#define	SPI_SS		PB2

#define	SPI_SS_LOW()	PORTB &= ~(1 << SPI_SS)
#define	SPI_SS_HIGH()	PORTB |= (1 << SPI_SS)

void spi_init();

void spi_send( uint8_t *buffer, uint16_t bytes );

void spi_receive( uint8_t *buffer, uint16_t bytes );

#endif

#endif
