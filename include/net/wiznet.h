#ifndef	WIZNET_H
#define	WIZNET_H
#include "net/ethernet.h"

#if USE_ETHERNET == 1

#define	W5500_SOCKET_COUNT	8

struct w5500_socket {
	struct socket s;
	uint8_t unused[0];
};


struct w5500_control {
	uint8_t bsb : 5;
	uint8_t rwb : 1;
	uint8_t om : 2;
};

#define	W5500_COMMON_REG_BSB	0b00000
#define	W5500_SOCKET_0_REG	0b00001
#define	W5500_SOCKET_0_TX	0b00010
#define	W5500_SOCKET_0_RX	0b00011
#define	W5500_SOCKET_1_REG	0b00101
#define	W5500_SOCKET_1_TX	0b00110
#define	W5500_SOCKET_1_RX	0b00111
#define	W5500_SOCKET_2_REG	0b01001
#define	W5500_SOCKET_2_TX	0b01010
#define	W5500_SOCKET_2_RX	0b01011
#define	W5500_SOCKET_3_REG	0b01101
#define	W5500_SOCKET_3_TX	0b01110
#define	W5500_SOCKET_3_RX	0b01111
#define	W5500_SOCKET_4_REG	0b10001
#define	W5500_SOCKET_4_TX	0b10010
#define	W5500_SOCKET_4_RX	0b10011
#define	W5500_SOCKET_5_REG	0b10101
#define	W5500_SOCKET_5_TX	0b10110
#define	W5500_SOCKET_5_RX	0b10111
#define	W5500_SOCKET_6_REG	0b11001
#define	W5500_SOCKET_6_TX	0b11010
#define	W5500_SOCKET_6_RX	0b11011
#define	W5500_SOCKET_7_REG	0b11101
#define	W5500_SOCKET_7_TX	0b11110
#define	W5500_SOCKET_7_RX	0b11111

#define	W5500_RWB_READ		0b0
#define	W5500_RWB_WRITE		0b1

#define	W5500_OM_VARIABLE	0b00

#define	W5500_OM_1_BYTE		0b01
#define	W5500_OM_2_BYTE		0b10
#define	W5500_OM_4_BYTE		0b11

/*!
 *	\{
 *	Given that the socket register is one less than the tx buffer and two
 *	less than the rx buffer in the BSB, it is convenient to use it as a 
 *	socket id.
 */

#define	W5500_SOCKET_ID_0	W5500_SOCKET_0_REG
#define	W5500_SOCKET_ID_1	W5500_SOCKET_1_REG
#define	W5500_SOCKET_ID_2	W5500_SOCKET_2_REG
#define	W5500_SOCKET_ID_3	W5500_SOCKET_3_REG
#define	W5500_SOCKET_ID_4	W5500_SOCKET_4_REG
#define	W5500_SOCKET_ID_5	W5500_SOCKET_5_REG
#define	W5500_SOCKET_ID_6	W5500_SOCKET_6_REG
#define	W5500_SOCKET_ID_7	W5500_SOCKET_7_REG

#define	ENABLE_UDP_MULTICAST		(1 << 7)
#define	DISABLE_UDP_MULTICAST		(0 << 7)
#define	ENABLE_MAC_FILTER		(1 << 7)
#define	DISABLE_MAC_FILTER		(0 << 7)

#define	ENABLE_BROADCAST_BLOCK		(1 << 6)
#define	DISABLE_BROADCAST_BLOCK		(0 << 6)

#define	ENABLE_N_DELAY_ACK		(1 << 5)
#define	DISABLE_N_DELAY_ACK		(0 << 5)

#define	MULTICAST_IGMP_V2		(0 << 5)
#define	MULTICAST_IGMP_V1		(1 << 5)

#define ENABLE_MULTICAST_BLOCK_MCGRAW	(1 << 5)
#define	DISABLE_MULTICAST_BLOCK_MCGRAW	(0 << 5)

#define	ENABLE_UNICAST_BLOCK_UDP	(1 << 4)
#define	DISABLE_UNICAST_BLOCK_UDP	(0 << 4)

#define	ENABLE_IPV6_BLOCK_MCGRAW	(1 << 4)
#define	DISABLE_IPV6_BLOCK_MCGRAW	(0 << 4)

#define	PROTOCOL_CLOSED ((0 << 3) | (0 << 2) | (0 << 1) | (0 << 0))

#define	PROTOCOL_TCP	((0 << 3) | (0 << 2) | (0 << 1) | (1 << 0))

#define	PROTOCOL_UDP	((0 << 3) | (0 << 2) | (1 << 1) |(0 << 0))

#define	PROTOCOL_MCGRAW	((0 << 3) | (1 << 2) | (0 << 1) |(0 << 0))


/*!
 *	\brief Convert the W5500 control struct into a single uint8_t.
 *
 *	The reason for this is that we don't know what kind of endianness the 
 *	bitfields have. For that reason, we'll go ahead and convert it into
 *	something a little more explicit.
 *
 *	\param w
 *	The W5500 control struct
 *
 *	\ret
 *	The control structure as a single unsigned char.
 */
static inline uint8_t w5500_control_select(struct w5500_control *w) {
	return (w->bsb << 3) | (w->rwb << 2) | w->om;
}
	

int w5500_send_packet(struct ethernet_handle *eth_handle, uint8_t *packet, 
	uint32_t p_size);

int w5500_receive_packet(struct ethernet_handle *eth_handle, uint8_t *packet,
	uint32_t p_size);

int w5500_open_socket(struct ethernet_handle *eth_handle);

int w5500_close_socket(struct ethernet_handle *eth_handle);

void construct_w5500_eth_handle(struct ethernet_handle *handle);

void construct_w5500_eth_ctrl(struct ethernet_controller *eth_ctrl);

#endif

#endif
