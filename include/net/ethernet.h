#ifndef	ETHERNET_H
#define	ETHERNET_H
#include <stdint.h>

#if USE_ETHERNET == 1

#define	MAC_ADDRESS_SIZE	6
#define	IP_ADDRESS_SIZE		4

#define	SOCKET_UNALLOCATED	-1

/*!
 *	\{
 *	The basic idea is that every socket has a protocol, a state, and a 
 *	number. If the socket has not been "allocated" with socket_open, then 
 *	SOCKET_UNALLOCATED is its number. In addition, if there is no protcol 
 *	that has yet been set for that socket, then PROTOCOL_UNDEFINED can be used. 
 *	Prior to calling socket_open, the user must define a protocol. The state 
 *	will be set by the socket_open function. 
 */
enum socket_protocol {
	UDP,
	TCP,
	MCGRAW,
	PROTOCOL_UNDEFINED
};

enum socket_state {
	SOCKET_OPEN,
	SOCKET_CLOSED
};
	
struct socket {
	short socket_num;
	enum socket_protocol protocol;
	enum socket_state state;
};

struct ethernet_handle {
	int (*open_socket)(struct ethernet_handle *handle);
	int (*send_packet)(struct ethernet_handle *handle, uint8_t *buffer, 
		uint32_t n_bytes);
	int (*receive_packet)(struct ethernet_handle * handle, uint8_t *buffer, 
		uint32_t n_bytes);
	int (*close_socket)(struct ethernet_handle *handle);
	struct socket s;
};

struct ethernet_controller {
	uint8_t mac_address[ MAC_ADDRESS_SIZE ];
	uint8_t ip_address[ IP_ADDRESS_SIZE ];
	void (*init_ethernet)(struct ethernet_controller *eth_ctrl);
	void (*deinit_ethernet)(struct ethernet_controller *eth_ctrl);
};

#endif

#endif
