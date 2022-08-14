#include "net/ethernet.h"
#include "user.h"

#if	USE_ETHERNET == 1

#define	W5500_SOCKET_MAX	8

volatile struct software_timer *ethernet_st = &tmr_arr[0];

struct net_socket sockets[W5500_SOCKET_MAX] = {
	// sn 0 is used by DHCP client
	{.sn = 0, .in_use = 1},
	{.sn = 1, .in_use = 0},
	{.sn = 2, .in_use = 0},
	{.sn = 3, .in_use = 0},
	{.sn = 4, .in_use = 0},
	{.sn = 5, .in_use = 0},
	{.sn = 6, .in_use = 0},
	{.sn = 7, .in_use = 0}
};

wiz_NetInfo wiz_data = {
	.mac = {
		0xA8, 0x61, 0x0A, 0xAE, 0xAA, 0x2C
	},

	.dhcp = NETINFO_STATIC,
	.ip = {192,168,0,72},
	.sn = {255,255,255,0},
	.gw = {0,0,0,0},
	.dns = {0,0,0,0}
};


#define	DHCP_BUFFER_SIZE	(236+312)
uint8_t dhcp_buffer[DHCP_BUFFER_SIZE] = {0};

// Empty functions right now
void ip_assign() { }

void ip_update() { }

void ip_conflict() { }

void do_ethernet_send() {
	char *buffer = "Hello world!";
	struct net_socket *s;
	uint8_t addr[] = {192,168,2,42};

	s = udp_open(42000);

	if (s) {
		udp_send((uint8_t *) &buffer[0], 12, s, &addr[0]);
	}

	udp_close(s);
}
void ethernet_task() {
	struct net_socket *s;
	while(1) {
		/*switch(DHCP_run()) {
			case DHCP_IP_ASSIGN:
			case DHCP_IP_CHANGED:
				break;
			case DHCP_IP_LEASED:
				if (ethernet_st->state != timer_started) {
					software_timer_start(ethernet_st);
				}
				break;
			case DHCP_FAILED:
				DHCP_stop();
				software_timer_stop(ethernet_st);
				DHCP_init(sockets[0].sn, &dhcp_buffer[0]);
				break;
			default:
				break;
		}*/

		if (ethernet_st->state != timer_started) {
			software_timer_start(ethernet_st);
		}

		task_sleep(0,10000);
	}
}

void ethernet_controller_init() {
	wizchip_init(NULL, NULL);
	//setSHAR(&wiz_data.mac[0]);
	//DHCP_init(sockets[0].sn, &dhcp_buffer[0]);
	//reg_dhcp_cbfunc(ip_assign, ip_update, ip_conflict);
	wizchip_setnetinfo(&wiz_data);
	ctlnetwork(CN_SET_NETINFO, (void *) &wiz_data);
}

struct net_socket *udp_open(uint16_t port) {
	int8_t retVal;
	uint8_t i;
	struct net_socket *s = NULL;

	// Find an available socket
	for (i = 0; i < W5500_SOCKET_MAX; ++i) {
		if (!sockets[i].in_use) {
			s = &sockets[i];
		}
	}

	// Indicate error if one was not found.
	if (!s) {
		return 0;
	}

	// Initialize the socket without flags
	retVal = socket(s->sn, SOCK_UDP, port, 0);

	if (retVal != SOCK_OK) {
		return 0;
	}

	s->port = port;
	s->flag = 0;
	s->protocol = SOCK_UDP;

	return s;
}

void udp_close(struct net_socket *s) {
	close(s->sn);

	s->in_use = 0;
}

int udp_send(uint8_t *buffer, uint16_t len, struct net_socket *s, 
	uint8_t *addr) {

	int32_t written = 0;
	int32_t previously_written = 0;

	/*
	 * Attempt to write the buffer through the socket. Keep trying if we
	 * haven't written everything, unless we get 0 returned.
	 *
	 * TODO: Add software timer support.
	 */
	while (written != len) {
		written = sendto(s->sn, buffer, len, addr, s->port);
		
		if (written < 0) {
			return 0;
		}

		else if (written == 0) {
			return 0;
		}

	}

	return 1;
}

int udp_receive(uint8_t *buffer, uint16_t len, struct net_socket *s,
	uint8_t *addr) {

	return recvfrom(s->sn, buffer, len, addr, &s->port);
}

#endif
