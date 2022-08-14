#include "comm/spi.h"

/*!
 *	\brief Initialize the SPI peripheral.
 *
 *	This sets master, and also sets the interrupt enable. In addition, the
 *	the mode is set to 0.
 */
void spi_init() {
	uint8_t clear;
	DDRB = (1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_SS);

	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);

	SPI_SS_LOW();

	SPI_SS_HIGH();

	clear = SPSR;
	clear = SPDR;
}

/*!
 *	\brief Send one byte over SPI.
 *
 *	do_spi is the only available function because often the exact procedure
 *	for reading or writing multiple bytes can vary between devices.
 *
 *	\param byte
 *	The byte to send.
 */
uint8_t do_spi(uint8_t byte) {
	SPDR = byte;

	while (!(SPSR & (1 << SPIF)));

	return SPDR;
}

