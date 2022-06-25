#ifndef	ETHERNET_H
#define	ETHERNET_H
#include <stdint.h>

#if USE_ETHERNET == 1

struct ethernet_handle {
	int (*open_socket)(struct ethernet_handle *handle);
	int (*send_packet)(struct ethernet_handle *handle, uint8_t *buffer, 
		uint16_t n_bytes);
	int (*receive_packet)(struct ethernet_handle * handle, uint8_t *buffer, 
		uint16_t n_bytes);
	int (*close_socket)(struct ethernet_handle *handle);
};

#endif

#endif
