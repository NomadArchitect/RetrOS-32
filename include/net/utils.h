#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

// call with checksum(hdr, hdr->ihl * 4, 0);
uint16_t checksum(void *addr, int count, int start_sum);

uint16_t transport_checksum(uint32_t saddr, uint32_t daddr, uint8_t proto, uint8_t *data, uint16_t len);

uint32_t ntohl(uint32_t data);
uint32_t htonl(uint32_t data);
uint16_t ntohs(uint16_t data);
uint16_t htons(uint16_t data);

uint32_t ip_to_int (const char * ip);

#endif /* UTIL_H */
