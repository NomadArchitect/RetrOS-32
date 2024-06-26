#ifndef DHCPD_H
#define DHCPD_H

#include <stdint.h>
#include <net/netdev.h>

#define DHCP_OP_DISCOVER 0x01
#define DHCP_OP_OFFER    0x02
#define DHCP_OP_REQUEST  0x01
#define DHCP_OP_ACK      0x02

#define DHCP_SOURCE_PORT 68
#define DHCP_DEST_PORT 67

#define DHCP_MAGIC_COOKIE 0x63538263

#define DHCP_HTYPE_ETH   0x01
#define DHCP_HLEN_ETH    0x06

enum {
    DHCP_FAILED,
    DHCP_SUCCESS,
    DHCP_PENDING,
    DHCP_STOPPED
};
extern char* dhcp_state_names[4];

struct dhcp {
    uint8_t    dhcp_op;
    uint8_t    dhcp_htype;
    uint8_t    dhcp_hlen;
    uint8_t    dhcp_hops;
    uint32_t   dhcp_xid;
    uint16_t   dhcp_secs;
    uint16_t   dhcp_flags;
    uint32_t   dhcp_ciaddr;
    uint32_t   dhcp_yiaddr;
    uint32_t   dhcp_siaddr;
    uint32_t   dhcp_giaddr;
    uint8_t    dhcp_chaddr[6];
    uint8_t    dhcp_reserved[10];
    char       dhcp_servername[64];
    char       dhcp_bootfilename[128];
    uint32_t   dhcp_cookie;
    uint8_t    dhcp_options[128];
} __attribute__((packed));

#define DHCP_DISCOVERY(dhcp) \
    memset((dhcp), 0, sizeof(*(dhcp))); \
    (dhcp)->dhcp_op = DHCP_OP_DISCOVER; \
    (dhcp)->dhcp_htype = DHCP_HTYPE_ETH;  \
    (dhcp)->dhcp_hlen = DHCP_HLEN_ETH; \
    (dhcp)->dhcp_hops = 0; \
    (dhcp)->dhcp_xid = 0x84237428; \
    (dhcp)->dhcp_secs = 0x0000; \
    (dhcp)->dhcp_flags = (uint16_t) 0x8000; \
    (dhcp)->dhcp_ciaddr = dhcp->dhcp_yiaddr = dhcp->dhcp_siaddr = 0; \
    (dhcp)->dhcp_giaddr = 0; \
    memcpy(dhcp->dhcp_chaddr, current_netdev.mac, 6); \
    (dhcp)->dhcp_cookie = (uint32_t) DHCP_MAGIC_COOKIE; \
    memset(&(dhcp)->dhcp_options, 0, 128);


#define DHCP_REQUEST(dhcp, server_ip, client_ip) \
    memset((dhcp), 0, sizeof(*(dhcp))); \
    (dhcp)->dhcp_op = DHCP_OP_REQUEST; \
    (dhcp)->dhcp_htype = DHCP_HTYPE_ETH; \
    (dhcp)->dhcp_hlen = DHCP_HLEN_ETH; \
    (dhcp)->dhcp_hops = 0; \
    (dhcp)->dhcp_xid = 0x84237428; \
    (dhcp)->dhcp_secs = 0x0000; \
    (dhcp)->dhcp_flags = (uint16_t) 0x8000; \
    (dhcp)->dhcp_ciaddr = dhcp->dhcp_giaddr = 0; \
    (dhcp)->dhcp_siaddr = server_ip; \
    (dhcp)->dhcp_yiaddr = client_ip; \
    memcpy((dhcp)->dhcp_chaddr, current_netdev.mac , 6); \
    (dhcp)->dhcp_cookie = (uint32_t) DHCP_MAGIC_COOKIE; \
    memset(&(dhcp)->dhcp_options, 0, 128);

struct dhcp_state 
{
    uint8_t state;
    uint32_t ip;
    uint8_t tries;
    uint32_t gateway;
    uint32_t dns;
};

int dhcp_get_state();
int dhcp_get_ip();
int dhcp_get_gw();
int dhcp_get_dns();

#endif /* DHCPD_H */
