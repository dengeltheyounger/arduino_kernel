#include "comm/spi.h"

#if USE_ETHERNET == 1

/*!
 *	\brief Initialize the SPI peripheral.
 *
 *	This sets master, and also sets the interrupt enable. In addition, the
 *	the mode is set to 0.
 */
void spi_init() {
	uint8_t clear;
	DDR_SPI = (1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_SS);

	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);

	SPI_SS_LOW();

	SPI_SS_HIGH();

	clear = SPSR;
	clear = SPDR;
}

/*!
 *	\brief Send one byte over SPI.
 *
 *	\param byte
 *	The byte to send.
 */
uint8_t do_spi(uint8_t byte) {
	SPDR = byte;

	while (!(SPSR & (1 << SPIF));

	return SPDR;
}

/*!
 *	\brief Send a string over SPI.
 *
 *	\param buffer
 *	The buffer to write over SPI.
 *
 *	\param bytes
 *	The number of bytes to write.
 *
 */
void spi_send(uint8_t *buffer, uint16_t bytes) {
	
	SPI_SS_LOW();
	for (uint16_t i = 0; i < bytes; ++i) {
		do_spi(&buffer[i]);
	}

	SPI_SS_HIGH();
}

void spi_receive(uint8_t *buffer, uint16_t bytes) {
	uint8_t byte;

	SPI_SS_LOW();

	for (uint16_t i = 0; i < bytes; ++i) {
		byte = do_spi(0xff);
	}

	SPI_SS_HIGH();
}

#endif
