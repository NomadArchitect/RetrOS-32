/**
 * @file arp.c
 * @author Joe Bayer (joexbayer)
 * @brief Handles ARP parsing, caching and lookup.
 * @version 0.1
 * @date 2022-06-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <net/arp.h>
#include <terminal.h>

#define MAX_ARP_ENTRIES 25

struct arp_entry arp_entries[MAX_ARP_ENTRIES];

void init_arp()
{
	for (size_t i = 0; i < MAX_ARP_ENTRIES; i++)
	{
		arp_entries[i].sip = 0;
	}

	uint8_t broadcast_mac[6] = {255, 255, 255, 255, 255, 255};
	
	memcpy(&arp_entries[0].smac, &broadcast_mac, 6);
	arp_entries[0].sip = BROADCAST_IP;
}

int arp_add_entry(struct arp_content* arp)
{
	/* Check if ARP entry already exists. */
	for (size_t i = 0; i < MAX_ARP_ENTRIES; i++)
		if(arp_entries[i].sip == arp->sip)
			return 1;

	for (size_t i = 0; i < MAX_ARP_ENTRIES; i++)
	{
		if(arp_entries[i].sip == 0)
		{
			memcpy((uint8_t*)&arp_entries[i].smac, (uint8_t*)&arp->smac, 6);
			arp_entries[i].sip = arp->sip;
			twriteln("Added APR entry.");
			return 1;
		}
	}

	return 0;
}

int arp_find_entry(uint32_t ip, uint8_t* mac)
{
	for (size_t i = 0; i < MAX_ARP_ENTRIES; i++)
		if(arp_entries[i].sip == ip){
			memcpy(mac, arp_entries[i].smac, 6);
			return 1;
		}
	
	return 0;
}

void __arp_ntohs(struct arp_header* a_hdr){

	a_hdr->hwtype = ntohs(a_hdr->hwtype);
	a_hdr->opcode = ntohs(a_hdr->opcode);
	a_hdr->protype = ntohs(a_hdr->protype);
}

void __arp_content_ntohs(struct arp_content* content)
{

	content->sip = ntohl(content->sip);
	content->dip = ntohl(content->dip);
}

void __arp_content_htons(struct arp_content* content)
{

	content->sip = htonl(content->sip);
	content->dip = htonl(content->dip);
}

void __arp_htons(struct arp_header* a_hdr)
{
	a_hdr->hwtype = htons(a_hdr->hwtype);
	a_hdr->opcode = htons(a_hdr->opcode);
	a_hdr->protype = htons(a_hdr->protype);
}

void print_arp()
{
	
}

void arp_print_cache()
{
	twriteln("ARP cache:");
	for (size_t i = 0; i < MAX_ARP_ENTRIES; i++)
		if(arp_entries[i].sip != 0){

			uint32_t ip = ntohl(arp_entries[i].sip);
			uint8_t bytes[4];
			bytes[0] = (ip >> 24) & 0xFF;
			bytes[1] = (ip >> 16) & 0xFF;
			bytes[2] = (ip >> 8) & 0xFF;
			bytes[3] = ip & 0xFF; 
			twritef("(%d.%d.%d.%d) at %x:%x:%x:%x:%x:%x\n",
					bytes[3], bytes[2], bytes[1], bytes[0],
					arp_entries[i].smac[0], arp_entries[i].smac[1], arp_entries[i].smac[2], arp_entries[i].smac[3], arp_entries[i].smac[4], arp_entries[i].smac[5]);
		}
}

void __arp_send(struct arp_content* content, struct arp_header* hdr, struct sk_buff* skb)
{
	skb->proto = ARP;
	twriteln("Creating Ethernet header.");
	int ret = ethernet_add_header(skb, content->dip);
	if(ret <= 0){
		twriteln("Error adding ethernet header");
		return;
	}

	__arp_htons(hdr);
	__arp_content_htons(content);

	memcpy(skb->data, hdr, sizeof(struct arp_header));
	skb->data += sizeof(struct arp_header);
	skb->len += sizeof(struct arp_header);

	memcpy(skb->data, content, sizeof(struct arp_content));
	skb->data += sizeof(struct arp_content);
	skb->len += sizeof(struct arp_content);

	twritef("Creating ARP Response. size: %d \n", skb->len);
	skb->stage = NEW_SKB;
	skb->action = SEND;
}

void arp_respond(struct arp_content* content)
{
	struct sk_buff* skb = get_skb();
    ALLOCATE_SKB(skb);
    skb->stage = IN_PROGRESS;

	struct arp_header a_hdr;
	ARP_FILL_HEADER(a_hdr, ARP_REPLY);

	memcpy(&content->dmac, &content->smac, 6);
	memcpy(&content->smac, &current_netdev.mac, 6);
	content->dip = content->sip;
	content->sip = 167772687;

	__arp_send(content, &a_hdr, skb);
}

void arp_request()
{
	twriteln("Creating ARP packet.");
	struct sk_buff* skb = get_skb();
    ALLOCATE_SKB(skb);
    skb->stage = IN_PROGRESS;


	struct arp_header a_hdr;
	struct arp_content a_content;

	ARP_FILL_HEADER(a_hdr, ARP_REQUEST);

	uint8_t broadcast_mac[6] = {255, 255, 255, 255, 255, 255};

	a_content.dip = BROADCAST_IP;
	memcpy(a_content.smac, current_netdev.mac, 6);
	a_content.sip = ip_to_int("192.168.2.3");
	memcpy(a_content.dmac, broadcast_mac, 6);

	__arp_send(&a_content, &a_hdr, skb);
}

/**
 * @brief Handles ARP packets
 * 
 * @param skb socket buffer to parse
 */
uint8_t arp_parse(struct sk_buff* skb)
{
	struct arp_header* a_hdr = (struct arp_header*) skb->data;
	skb->hdr.arp = a_hdr;
	skb->data = skb->data + sizeof(struct arp_header);

	__arp_ntohs(a_hdr);

	if(a_hdr->opcode != ARP_REQUEST || a_hdr->hwtype != ARP_ETHERNET || a_hdr->protype != ARP_IPV4){	
		return 0;
	}

	struct arp_content* arp_content = (struct arp_content*) skb->data;
	__arp_content_ntohs(arp_content);

	twriteln("Received ARP!");

	int ret = arp_add_entry(arp_content);
	if(!ret)
		return ret;
	
	arp_respond(arp_content);

	return 1;
}