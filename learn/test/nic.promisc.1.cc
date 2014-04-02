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
using namespace std;

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

inline void displayEtherAddr(const char *addr)
{
	printf("%02x:%02x:%02x:%02x:%02x:%02x",
	(unsigned char)addr[0],
	(unsigned char)addr[1],
	(unsigned char)addr[2],
	(unsigned char)addr[3],
	(unsigned char)addr[4],
	(unsigned char)addr[5]);
}

int bTerminate;
char buf[20480];

void ctrl_c_handler(int signo)
{
	cout<<endl<<"CTRL+C Pressed"<<endl;
	cout<<"Programme Exiting...";
	bTerminate = true;
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

	printf("<%09d> %15s:%6d ---> ", pktCount,
			inet_ntoa(*((in_addr*)&(ip->saddr))), sport);
	printf("%15s:%6d\r",
			inet_ntoa(*((in_addr*)&(ip->daddr))), dport);

	unsigned char *data = (((unsigned char *)tcp) + (tcp->doff)*4);
	for(j=0; j<100; j++)
	{
		printf("%c", data[j]);
	}

}


int main()
{
	int sock;

	bTerminate = false;

	signal(SIGINT, ctrl_c_handler);


	if((sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) < 0)
	{
		perror("Failed to create socket");
		return -1;
	}

	setPromisc("eth0", sock);
	//setPromisc("wlan0", sock);


	while(!bTerminate)
	{
		int len;
		len = recvfrom(sock, buf, 20480, 0, NULL, NULL);

		if(len<0)
		{
			cout<<"data error"<<endl;
			continue;
		}	

		struct ether_header *pEthHdr;

		pEthHdr = (struct ether_header *) buf;


		struct iphdr *ip;
		ip = (struct iphdr *)(buf + sizeof(struct ether_header));

		switch(ntohs(pEthHdr->ether_type))
		{
		case 0x0800:
			switch(ip->protocol)
			{
			case IPPROTO_TCP:
/*
				for(int i=0; i<100; i++)
					printf("%x ",(unsigned char)buf[i]);
				printf("\n");
*/
				parseTcp(ip);
				break;
			case IPPROTO_UDP:
				break;
			default:
				break;
			}
			
			break;
		case 0x0806:
#if	0
			switch(ntohs(*((unsigned short*)(buf+20))))
			{
			case 1:
				printf("\rarp:\t");
				break;
			case 2:
				printf("\rreply:\t");
				break;
			default:
				break;
			}
			displayEtherAddr(buf+6);
			printf(" --> ");
			displayEtherAddr(buf);
			printf(" %s",inet_ntoa(*((in_addr*)(buf+38))));
			printf(" %s",inet_ntoa(*((in_addr*)(buf+28))));
#endif
			break;
		case 0x0835:
			printf("RARP");
			break;
		default:
#if 0
			if(ntohs(pEthHdr->ether_type)>0x05DC)
			{
				printf("\nunknown:%x",
				ntohs(pEthHdr->ether_type));
				break;
			}

			for(int i=0; i<len; i++)
				printf(" %x", (unsigned char)buf[i]);

			printf("\n");
#endif
			//printf("[%x] ",ntohs(pEthHdr->ether_type));
			break;
		}


		//printf("\n");
	}


	close(sock);
	cout<<"Finished..."<<endl;

	return 0;
}
