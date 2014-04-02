/*
 *--------------------------------------------------------------------------
 *   File Name:	nic.promisc.cc
 * 
 * Description:	将网卡设置为混杂模式
 * 		数据包监听
 * 
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 
 *     Version:	1.0
 * Create Date: Fri May 15 10:27:28 2009
 * Last Update: Fri May 15 10:27:28 2009
 * 
 *--------------------------------------------------------------------------
 */
#include<cstdio>
#include<cstring>
#include<iostream>
#include<unistd.h>
#include<signal.h>
#include<net/ethernet.h>
#include<sys/types.h>
#include<sys/ioctl.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<netinet/tcp.h>
#include<linux/if.h>
#include<linux/sockios.h>
#include<linux/if_ether.h>

#include<linux/if_arp.h>



struct _arphdr {
	__be16		ar_hrd;		/* format of hardware address	*/
	__be16		ar_pro;		/* format of protocol address	*/
	unsigned char	ar_hln;		/* length of hardware address	*/
	unsigned char	ar_pln;		/* length of protocol address	*/
	__be16		ar_op;		/* ARP opcode (command)		*/

	 /*
	  *	 Ethernet looks like this : This bit is variable sized however...
	  */
	unsigned char		ar_sha[ETH_ALEN];	/* sender hardware address	*/
	unsigned char		ar_sip[4];		/* sender IP address		*/
	unsigned char		ar_tha[ETH_ALEN];	/* target hardware address	*/
	unsigned char		ar_tip[4];		/* target IP address		*/

};


using namespace std;

void dump_arp(struct _arphdr *arp);
int setPromisc(const char *interface, int sock);
void ctrl_c_handler(int signo);
inline void displayEtherAddr(char *addr);
void parseTcp(struct iphdr *ip);

char buf[20480];


int main()
{
	int sock;

	if((sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0){
		perror("Failed to create socket");
		return -1;
	}

	setPromisc("eth0", sock);

	while(!false){
		int len;
        struct sockaddr_ll sal;
        socklen_t slen;
		len = recvfrom(sock, buf, 20480, MSG_TRUNC, (struct sockaddr *) &sal, &slen);
#if 0
		cout<<"pkt..."<<endl;
        cout<<"family: "<<sal.sll_family<<"\n";
        cout<<"protocol: "<<sal.sll_protocol<<"\n";
        unsigned int pkttype = sal.sll_pkttype;
        cout<<"pkttype: "<<pkttype<<"\n";
        unsigned int halen = sal.sll_halen;
        cout<<"halen: "<<halen<<"\n";
        for(int i=0; i<8; i++) {
            printf("%x:", sal.sll_addr[i]);
        }
        printf("\n");
#endif
		if(len<0){
			cout<<"data error"<<endl;
			continue;
		}
		else if(len == 0){
			cout<<"data == 0"<<endl;
			continue;
		}

		struct ethhdr *pEthHdr;
		pEthHdr = (struct ethhdr *) buf;

		struct iphdr *ip;
		ip = (struct iphdr *)(buf + ETH_HLEN);

		char *data = (char *)(ip->ihl*4+(unsigned long)ip);

		struct _arphdr *arp = (struct _arphdr *)data;


		switch(ntohs(pEthHdr->h_proto)){
		case 0x0800:
			switch(ip->protocol){
			case IPPROTO_TCP:
				printf("TCP:\n");
				for(int i=0; i<len-(data-buf); i++)
				{
					if(isprint(data[i]));
						cout<<data[i];
				}
				cout<<endl;
				break;
			case IPPROTO_UDP:
				printf("UDP:\n");
				break;
			default:
				printf("ip_protocol:%02x\n", ip->protocol);
				break;
			}
			
			break;
		case 0x0806:
        break;
			switch(ntohs(arp->ar_op))
			{
			case ARPOP_REQUEST:
				printf("arp: ");
				break;
			case ARPOP_REPLY:
				printf("reply: ");
				break;
			default:
				printf("Unknown ARP Packet...\n");
				break;
			}
			displayEtherAddr((char *)pEthHdr->h_source);
			printf(">");
			displayEtherAddr((char *)pEthHdr->h_dest);
			dump_arp(arp);
			break;
		case 0x0835:
			printf("RARP");
			break;
		default:
			printf("Unknown Packet:%04x\n", ntohs(pEthHdr->h_proto));
			break;
		}
	}

	close(sock);
	cout<<"Finished..."<<endl;
	return 0;
}

void dump_arp(struct _arphdr *arp)
{

	char sip[16],tip[16];
	strcpy(sip, inet_ntoa(*((struct in_addr*)arp->ar_sip)));
	strcpy(tip, inet_ntoa(*((struct in_addr*)arp->ar_tip)));
	printf(" %s ask %s\n", sip, tip);
}
int setPromisc(const char *interface, int sock)
{
	struct ifreq ifr;

	if(strlen(interface) >= IFNAMSIZ)
		return -1;
	strcpy(ifr.ifr_name, interface);

	if(ioctl(sock, SIOCGIFFLAGS, &ifr) < 0)
	{
		perror("Could not retrive flags for the interface");
		return -1;
	}

	ifr.ifr_flags |= IFF_PROMISC;

	if(ioctl(sock, SIOCSIFFLAGS, &ifr) < 0)
	{
		perror("Cound not set the PROMISC flag");
		return -1;
	}
	
	printf("Set %s Promisc Success...\n", interface);
	return 0;
}
inline void displayEtherAddr(char *addr)
{
	printf("%02x:%02x:%02x:%02x:%02x:%02x",
	(unsigned char)addr[0],
	(unsigned char)addr[1],
	(unsigned char)addr[2],
	(unsigned char)addr[3],
	(unsigned char)addr[4],
	(unsigned char)addr[5]);
}
void parseTcp(struct iphdr *ip)
{
	int i = 0, j = 0, k = 0;
	static unsigned int pktCount = 0;
	struct tcphdr *tcp;
	unsigned short sport = ntohs(tcp->source);
	unsigned short dport = ntohs(tcp->dest);

	unsigned short tcplen = ntohs(ip->tot_len) - ip->ihl*4 - tcp->doff*4;
	tcp = (struct tcphdr *)(((char *)(ip))+(ip->ihl<<2));
	pktCount++;


    char src[256];
    char dst[256];
    socklen_t len = sizeof(struct in_addr);
    inet_ntop(AF_INET, &ip->saddr, src, len);
    inet_ntop(AF_INET, &ip->daddr, dst, len);
	printf("<%09d> %15s:%6d ---> ", pktCount, src, sport);
	printf("%15s:%6d\r", dst, dport);

	unsigned char *data = (((unsigned char *)tcp) + (tcp->doff)*4);

}
