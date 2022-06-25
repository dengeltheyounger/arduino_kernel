#include "net/wiznet.h"

#if USE_ETHERNET == 1

struct w5500_socket[W5500_SOCKET_COUNT] = { 0 };

uint8_t w5500_socket_in_use = 0;

void construct_w5500_eth_handle(struct ethernet_handle **handle) {
	

void w5500_open_socket(struct ethernet_handle *eth_handle);

#endif
