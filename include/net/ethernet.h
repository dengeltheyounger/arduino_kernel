#ifndef	ETHERNET_H
#define	ETHERNET_H
#include <stdint.h>
#include <stddef.h>
#include "ioLibrary_Driver/socket.h"
#include "ioLibrary_Driver/wizchip_conf.h"
#include "ioLibrary_Driver/w5500/w5500.h"

#if	USE_ETHERNET == 1

struct net_socket
{
	uint8_t sn;
	uint8_t protocol;
	uint16_t port;
	uint8_t flag;
	int in_use;
};

struct net_socket *udp_open(uint16_t port);

void ethernet_controller_init();

void udp_close(struct net_socket *s);

int udp_send(uint8_t *buffer, uint16_t len, struct net_socket *s, 
	uint8_t *addr);

int udp_receive(uint8_t *buffer, uint16_t len, struct net_socket *s,
	uint8_t addr);

#endif
#endif
