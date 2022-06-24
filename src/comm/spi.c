#include "comm/spi.h"

#if USE_ETHERNET == 1

/*!
 *	\brief Initialize the SPI peripheral.
 *
 *	This sets master, and also sets the interrupt enable. In addition, the
 *	the mode is set to 0.
 */
void spi_init() {
	DDR_SPI = (1 << SPI_MOSI) | (1 << SPI_SCK) | (1 << SPI_SS);

	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0) | (1 << SPIE);
}

/*!
 *	\brief Send one byte over SPI.
 *
 *	\param byte
 *	The byte to send.
 */
void spi_send_byte(uint8_t byte) {
	SPDR = byte;

	while (!(SPSR & (1 << SPIF));
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
	for (uint16_t i = 0; i < bytes; ++i) {
		spi_send_byte(&buffer[i]);
	}
}


