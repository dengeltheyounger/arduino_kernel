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

#define	W5500_COMMON_REG	0b00000
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

#define	W5500_COMMON_MR			0x0000

#define	W5500_COMMON_GAR0		0x0001
#define	W5500_COMMON_GAR1		0x0002
#define	W5500_COMMON_GAR2		0x0003
#define	W5500_COMMON_GAR3		0x0004

#define	W5500_COMMON_SUBR0		0x0005
#define	W5500_COMMON_SUBR1		0x0006
#define	W5500_COMMON_SUBR2		0x0007
#define	W5500_COMMON_SUBR3		0x0008

#define	W5500_COMMON_SHAR0		0x0009
#define	W5500_COMMON_SHAR1		0x000A
#define W5500_COMMON_SHAR2		0x000B
#define	W5500_COMMON_SHAR3		0x000C
#define	W5500_COMMON_SHAR4		0x000D
#define	W5500_COMMON_SHAR5		0x000E

#define	W5500_COMMON_SIPR0		0x000F
#define	W5500_COMMON_SIPR1		0x0010
#define	W5500_COMMON_SIPR2		0x0011
#define	W5500_COMMON_SIPR3		0x0012

#define	W5500_COMMON_INTLEVEL0		0x0013
#define	W5500_COMMON_INTLEVEL1		0x0014

#define	W5500_COMMON_IR			0x0015
#define	W5500_COMMON_IMR		0x0016

#define	W5500_COMMON_SIR		0x0017
#define	W5500_COMMON_SIMR		0x0018
#define	W5500_COMMON_RTR0		0x0019
#define	W5500_COMMON_RTR1		0x001A

#define	W5500_COMMON_RCR		0x001B

#define	W5500_COMMON_PTIMER		0x001C

#define	W5500_COMMON_PMAGIC		0x001D

#define	W5500_COMMON_PHAR0		0x001E
#define	W5500_COMMON_PHAR1		0x001F
#define	W5500_COMMON_PHAR2		0x0020
#define	W5500_COMMON_PHAR3		0x0021
#define	W5500_COMMON_PHAR4		0x0022
#define	W5500_COMMON_PHAR5		0x0023

#define	W5500_COMMON_PSID0		0x0024
#define	W5500_COMMON_PSID1		0x0025

#define	W5500_COMMON_UIPR0		0x0028
#define	W5500_COMMON_UIPR1		0x0029
#define	W5500_COMMON_UIPR2		0x002A
#define	W5500_COMMON_UIPR3		0x002B

#define	W5500_COMMON_UPORTR0		0x002C
#define	W5500_COMMON_UPORTR1		0x002D

#define	W5500_COMMON_CHIP_VERSION	0x0039

#define	W5500_SOCKET_SN_MR		0x0000
#define	W5500_SOCKET_SN_CR		0x0001
#define	W5500_SOCKET_SN_IR		0x0002
#define	W5500_SOCKET_SN_SR		0x0003
#define	W5500_SOCKET_SN_PORT0		0x0004
#define	W5500_SOCKET_SN_PORT1		0x0005
#define	W5500_SOCKET_SN_DHAR0		0x0006
#define	W5000_SOCKET_SN_DHAR1		0x0007
#define	W5500_SOCKET_SN_DHAR2		0x0008
#define	W5500_SOCKET_SN_DHAR3		0x0009
#define	W5500_SOCKET_SN_DHAR4		0x000A
#define	W5500_SOCKET_SN_DHAR5		0x000B
#define	W5500_SOCKET_SN_DIPR0		0x000C
#define	W5500_SOCKET_SN_DIPR1		0x000D
#define	W5500_SOCKET_SN_DIPR2		0x000E
#define	W5500_SOCKET_SN_DIPR3		0x000F
#define	W5500_SOCKET_SN_DPORT0		0x0010
#define	W5500_SOCKET_SN_DPORT1		0x0011
#define	W5500_SOCKET_SN_MSSR0		0x0012
#define	W5500_SOCKET_SN_MSSR1		0x0013
#define	W5500_SOCKET_SN_TOS		0x0015
#define	W5500_SOCKET_SN_RXBUF_SIZE	0x001E
#define	W5500_SOCKET_SN_TXBUF_SIZE	0x001F
#define	W5500_SOCKET_SN_TX_FSR0		0x0020
#define	W5500_SOCKET_SN_TX_FSR1		0x0021
#define	W5500_SOCKET_SN_TX_RD0		0x0022
#define	W5500_SOCKET_SN_TX_RD1		0x0023
#define	W5500_SOCKET_SN_TX_WR0		0x0024
#define	W5500_SOCKET_SN_TX_WR1		0x0025
#define	W5500_SOCKET_SN_RX_RSR0		0x0026
#define	W5500_SOCKET_SN_RX_RSR1		0x0027
#define	W5500_SOCKET_SN_RX_RD0		0x0028
#define	W5500_SOCKET_SN_RX_RD1		0x0029
#define	W5500_SOCKET_SN_RX_WR0		0x002A
#define	W5500_SOCKET_SN_RX_WR1		0x002B
#define	W5500_SOCKET_SN_IMR		0x002C
#define	W5500_SOCKET_SN_FRAG0		0x002D
#define	W5500_SOCKET_SN_FRAG1		0x002E
#define	W5500_SOCKET_SN_KPALVTR		0x002F

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

#define	W5500_RESET				(1 << 7)
#define	W5500_WOL_ENABLE			(1 << 5)
#define	W5500_WOL_DISABLE			(0 << 5)
#define	W5500_PING_BLOCK_MODE_ENABLE		(1 << 4)
#define	W5500_PING_BLOCK_MODE_DISABLE		(0 << 4)
#define	W5500_PPOE_MODE_ENABLE			(1 << 3)
#define	W5500_PPOE_MODE_DISABLE			(0 << 3)
#define	W5500_FARP_ENABLE			(1 << 1)
#define	W5500_FARP_DISABLE			(0 << 1)

#define	W5500_ENABLE_UDP_MULTICAST		(1 << 7)
#define	W5500_DISABLE_UDP_MULTICAST		(0 << 7)
#define	W5500_ENABLE_MAC_FILTER			(1 << 7)
#define	W5500_DISABLE_MAC_FILTER		(0 << 7)

#define	W5500_ENABLE_BROADCAST_BLOCK		(1 << 6)
#define	W5500_DISABLE_BROADCAST_BLOCK		(0 << 6)

#define	W5500_ENABLE_N_DELAY_ACK		(1 << 5)
#define	W5500_DISABLE_N_DELAY_ACK		(0 << 5)

#define	W5500_MULTICAST_IGMP_V2			(0 << 5)
#define	W5500_MULTICAST_IGMP_V1			(1 << 5)

#define W5500_ENABLE_MULTICAST_BLOCK_MCGRAW	(1 << 5)
#define	W5500_DISABLE_MULTICAST_BLOCK_MCGRAW	(0 << 5)

#define	W5500_ENABLE_UNICAST_BLOCK_UDP		(1 << 4)
#define	W5500_DISABLE_UNICAST_BLOCK_UDP		(0 << 4)

#define	W5500_ENABLE_IPV6_BLOCK_MCGRAW		(1 << 4)
#define	W5500_DISABLE_IPV6_BLOCK_MCGRAW		(0 << 4)

#define	W5500_SR7_IMR_ENABLE			(1 << 7)
#define	W5500_SR7_IMR_DISABLE			(0 << 7)
#define	W5500_SR6_IMR_ENABLE			(1 << 6)
#define	W5500_SR6_IMR_DISABLE			(0 << 6)
#define	W5500_SR5_IMR_ENABLE			(1 << 5)
#define	W5500_SR5_IMR_DISABLE			(0 << 5)
#define	W5500_SR4_IMR_ENABLE			(1 << 4)
#define	W5500_SR4_IMR_DISABLE			(0 << 4)
#define	W5500_SR3_IMR_ENABLE			(1 << 3)
#define	W5500_SR3_IMR_DISABLE			(1 << 3)
#define	W5500_SR2_IMR_ENABLE			(1 << 2)
#define	W5500_SR2_IMR_DISABLE			(0 << 2)
#define	W5500_SR1_IMR_ENABLE			(1 << 1)
#define	W5500_SR1_IMR_DISABLE			(0 << 1)
#define	W5500_SR0_IMR_ENABLE			(1 << 0)
#define	W5500_SR0_IMR_DISABLE			(0 << 0)
#define	PROTOCOL_CLOSED ((0 << 3) | (0 << 2) | (0 << 1) | (0 << 0))

#define	PROTOCOL_TCP	((0 << 3) | (0 << 2) | (0 << 1) | (1 << 0))

#define	PROTOCOL_UDP	((0 << 3) | (0 << 2) | (1 << 1) |(0 << 0))

#define	PROTOCOL_MCGRAW	((0 << 3) | (1 << 2) | (0 << 1) |(0 << 0))

#define	SN_CR_OPEN				0x01
#define	SN_CR_LISTEN				0x02
#define	SN_CR_CONNECT				0x04
#define	SN_CR_DISCON				0x08
#define	SN_CR_CLOSE				0x10
#define	SN_CR_SEND				0x20
#define	SN_CR_SEND_MAC				0x21
#define	SN_CR_SEND_KEEP				0x22
#define	SN_CR_RECV				0x40

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

void init_w5500_eth_ctrl(struct ethernet_controller *eth_ctrl);

void deinit_w5500_eth_ctrl(struct ethernet_controller *eth_ctrl);

#endif

#endif
