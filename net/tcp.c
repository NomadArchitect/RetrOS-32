#include <net/tcp.h>
#include <net/skb.h>
#include <serial.h>

int tcp_register_connection(struct sock* sock, uint16_t dst_port, uint16_t src_port)
{

	return 0;
}

inline int tcp_is_listening(struct sock* sock)
{
	return sock->tcp_conn.state == TCP_LISTEN;
}

inline int tcp_set_listening(struct sock* sock, int backlog)
{
	
	sock->tcp_conn.backlog = backlog;
	sock->tcp_conn.state = TCP_LISTEN;

	return 1;
}



int tcp_send_ack(struct sock* sock, uint16_t dst_port, uint16_t src_port)
{
	return 0;
}

int tcp_send_syn(struct sock* sock, uint16_t dst_port, uint16_t src_port)
{	

	return 0;
}

int tcp_recv_ack(struct sock* sock, struct sk_buff* skb)
{
	return -1;
}

int tcp_recv_syn(struct sock* sock, struct sk_buff* skb)
{
	/**
	 * A listening socket can only "connect" to one client at a time.
	 * Incomming "connects" while socket is busy needs to be queued.
	 */
	if(sock->tcp_conn.state != TCP_LISTEN)
		return -1;

	/* send syn ack & more*/

	sock->tcp_conn.state = TCP_SYN_RCVD;
	return 1;
}


int tcp_parse(struct sk_buff* skb)
{
		/* Look if there is an active TCP connection, if not look for accept. */

		struct tcp_header* hdr = (struct tcp_header* ) skb->data;
		skb->hdr.tcp = hdr;

		struct sock* sk = net_sock_find_tcp(hdr->source, hdr->dest, skb->hdr.ip->saddr);
		if(sk == NULL){
			dbgprintf("[TCP] No socket found for TCP packet while parsing.\n");
			return -1;
		}

		switch (sk->tcp_conn.state)
		{
		case TCP_LISTEN:
			if(hdr->syn == 1 && hdr->ack == 0){
				return tcp_recv_syn(sk, skb);
			}
			break;
		
		case TCP_SYN_SENT:
			if(hdr->syn == 1 && hdr->ack == 1){
				/* SYN / ACK (Only relvant for "connect" )*/
				return -1;
			}
			break;
		
		case TCP_ESTABLISHED:
			if(hdr->syn == 0 && hdr->ack == 1){
				return tcp_recv_ack(sk, skb);
			}
			break;
		
		default:
			break;
		}
		
		return -1;
}

void tcp_connection_update()
{
	/* This will be a BIG switch statement, executing functions
	* based on state of a tcp connection
	*/

}

