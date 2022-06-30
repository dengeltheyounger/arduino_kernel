#ifndef	ETHERNET_H
#define	ETHERNET_H
#include <stdint.h>

#if USE_ETHERNET == 1

#define	MAC_ADDRESS_SIZE	6

enum socket_protocol {
	UDP,
	TCP,
	MCGRAW
}

enum socket_state {
	SOCKET_OPEN,
	SOCKET_CLOSED
}
	

struct socket {
	uint8_t socket_num;
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
	struct socket *s;
};

struct ethernet_controller {
	uint8_t mac_address[ MAC_ADDRESS_SIZE ];
	uint32_t ip_address;
	void (*init_ethernet)(struct ethernet_controller *eth_ctrl);
	void (*deinit_ethernet)(struct ethernet_controller *eth_ctrl);
};

#endif

#endif
