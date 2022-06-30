#include "comm/spi.h"
#include "net/wiznet.h"

#if USE_ETHERNET == 1

#define	W5500_SOCKET_1		0b00000001
#define	W5500_SOCKET_2		0b00000010
#define	W5500_SOCKET_3		0b00000100
#define	W5500_SOCKET_4		0b00001000
#define	W5500_SOCKET_5		0b00010000
#define	W5500_SOCKET_6		0b00100000
#define	W5500_SOCKET_7		0b01000000
#define	W5500_SOCKET_8		0b10000000

struct w5500_socket w5500_socket_set[W5500_SOCKET_COUNT] = {
	{ .socket_num = W5500_SOCKET_ID_0 },
	{ .socket_num = W5500_SOCKET_ID_1 },
	{ .socket_num = W5500_SOCKET_ID_2 },
	{ .socket_num = W5500_SOCKET_ID_3 },
	{ .socket_num = W5500_SOCKET_ID_4 },
	{ .socket_num = W5500_SOCKET_ID_5 },
	{ .socket_num = W5500_SOCKET_ID_6 },
	{ .socket_num = W5500_SOCKET_ID_7 }
};

uint8_t w5500_socket_in_use = 0;

static inline struct w5500_socket *w5500_set_socket(uint8_t value) {
	w5500_socket_in_use |= value;
	return &w5500_socket_set[value];
}

void construct_w5500_eth_handle(struct ethernet_handle *handle) {
	uint8_t socket_num = 0;
	handle->open_socket = w5500_open_socket;
	handle->close_socket = w5500_close_socket;
	handle->send_packet = w5500_send_packet;
	handle->receive_packet = w5500_receive_packet;
	handle->socket = NULL;
}
	
void construct_w5500_eth_ctrl(struct ethernet_controller *eth_ctrl) {
	struct w5500_control w_ctrl = { 0 };
	uint8_t ctrl_byte = 0;
	uint16_t addr;
	w_ctrl.bsb = W5500_COMMON_REG;
	w_ctrl.rwb = W5500_RWB_READ;
	w_ctrl.om = OM_VARIABLE;

	ctrl_byte = w5500_control_select( &w_ctrl );

	
	
}

int w5500_open_socket(struct ethernet_handle *eth_handle) {
	
	if (w5500_socket_in_use & W5500_SOCKET_2) {
		socket_num = W5500_SOCKET_2;
	}

	else if (w5500_socket_in_use & W5500_SOCKET_3) {
		socket_num = W5500_SOCKET_3;
	}

	else if (w5500_socket_in_use & W5500_SOCKET_4) {
		socket_num = W5500_SOCKET_4;
	}

	else if (w5500_socket_in_use & W5500_SOCKET_5) {
		socket_num = W5500_SOCKET_5;
	}

	else if (w5500_socket_in_use & W5500_SOCKET_6) {
		socket_num = W5500_SOCKET_6;
	}

	else if (w5500_socket_in_use & W5500_SOCKET_7) {
		socket_num = W5500_SOCKET_7;
	}

	else if (w5500_socket_in_use & W5500_SOCKET_8) {
		socket_num = W5500_SOCKET_8;
	}

	else if (w5500_socket_in_use & W5500_SOCKET_1) {
		socket_num = W5500_SOCKET_1;
	}

	handle->s = (struct socket *) w5500_set_socket(socket_num);

}

int w5500_close_socket(struct ethernet_handle *eth_handle) {

}

int w5500_send_packet(struct ethernet_handle *eth_handle, uint8_t *buffer, 
	uint32_t p_size) {

	struct w5500_control w_ctrl = { 0 };
	uint8_t byte;

	w_ctrl.bsb = eth_handle->s->socket_num+1;
	w_ctrl.rwb = W5500_RWB_WRITE;
	w_ctrl.om = W5500_OM_VARIABLE;

	byte = w5500_control_select(&w_ctrl);

	SPI_SS_LOW();

	do_spi(byte);

	for (uint32_t i = 0; i < p_size; ++i) {
		do_spi(buffer[i]);
	}

	SPI_SS_HIGH();

	return 1;
}

/*!
 *	\brief Receive a packet from the wiznet w5500.
 *
 *	The first byte sent to the w5500 requires that it be the address
 *	(uint16_t), and then the control byte. After that, it must be
 *	each byte sequentially. This protocol requires that the EOT byte
 *	value be bitstuffed so that there are no two EOTs in a row.
 *	by doing this, we can work out how many bytes there are in the
 *	packet.
 *
 *	\param eth_handle
 *	The ethernet handle
 *
 *	\param packet
 *	The buffer that is receiving the bytes.
 *
 *	\param p_size
 *	The requested number of bytes. 
 *
 *	\ret
 *	The total number of bytes read
 */
int w5500_receive_packet(struct ethernet_handle *eth_handle, uint8_t *packet,
	uint32_t p_size) {

	struct w5500_control w_ctrl = { 0 };
	uint8_t byte;
	uint8_t check_byte[2] = { 0 };
	uint8_t eot_byte = 0x04;
	uint32_t pkt_byte_count = 0;

	w_ctrl.bsb = eth_handle->s->socket_num+2;
	w_ctrl.rwb = W5500_RWB_READ;
	w_ctrl.om = W5500_OM_VARIABLE;

	byte = w5500_control_select(&w_ctrl);

	SPI_SS_LOW();

	do_spi(byte);

	for (uint32_t i = 0; i < p_size/2; ++i) {
		check_byte[0] = do_spi(eot_byte);
		check_byte[1] = do_spi(eot_byte);

		if (check_byte[0] == eot_byte && check_byte[1] == eot_byte) {
			break;
		}

		packet[pkt_byte_count++] = check_byte[0];
		packet[pkt_byte_count++] = check_byte[1];
	}

	SPI_SS_HIGH();

	return pkt_byte_count;
}

#endif
