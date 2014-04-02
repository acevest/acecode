/*
 *--------------------------------------------------------------------------
 *   File Name:	arp.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Oct 14 12:50:23 2010
 * 
 * Description:	明明是个ARP查询，怎么就把实验室的机器都给骗了呢？
 * 		有待学习.
 * 
 *--------------------------------------------------------------------------
 */

#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netpacket/packet.h>
#include<netinet/if_ether.h>


#define	FRM_SZ	(1024)

int main(int argc, char *argv[]){
	char frame[FRM_SZ];
	unsigned char dst[ETH_ALEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	unsigned char src[ETH_ALEN] = {0x00, 0x21, 0x86, 0x96, 0x62, 0x49};
	unsigned char tst[ETH_ALEN] = {0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb};
	struct in_addr	sip, tip;
	struct ether_header *eth;
	struct ether_arp *arp;
	struct sockaddr_ll sa;
	int fd;
    char *ifn = NULL;

    if(argc != 2) {
        printf("Usage:\n\t%s <interface>\n", argv[0]);
        return 0;
    }

    ifn = argv[1];

#if 1
	inet_pton(AF_INET, "192.168.100.27", &tip);
	inet_pton(AF_INET, "192.168.100.1", &sip);
#else
	inet_pton(AF_INET, "127.0.0.1", &tip);
	inet_pton(AF_INET, "127.0.0.2", &sip);
#endif

	eth = (struct ether_header *)(frame);
	arp = (struct ether_arp *)(frame + ETH_HLEN);

	memset(frame, 0, FRM_SZ);

	memcpy(eth->ether_dhost, dst, ETH_ALEN);
	memcpy(eth->ether_shost, src, ETH_ALEN);
	eth->ether_type	= htons(ETHERTYPE_ARP);

	
	arp->arp_hrd	= htons(ARPHRD_ETHER);
	arp->arp_hln	= ETH_ALEN;
	arp->arp_pln	= 4;
	arp->arp_pro	= htons(ETHERTYPE_IP);
	arp->arp_op	= htons(ARPOP_REQUEST);
	memcpy(arp->arp_sha, src, ETH_ALEN);
	memset(arp->arp_tha, 0, ETH_ALEN);
	memcpy(arp->arp_spa, &sip, sizeof(struct in_addr));
	memcpy(arp->arp_tpa, &tip, sizeof(struct in_addr));

	sa.sll_family	= AF_PACKET;
	sa.sll_ifindex	= if_nametoindex(ifn);
    sa.sll_halen    = ETH_ALEN;
	///memcpy(sa.sll_addr, tst, ETH_ALEN);


	int i;
	for(i=0; i<60; i++)
	{
		printf("%02x ", (unsigned char)frame[i]);
		if((i+1)%8 == 0)
			printf(" ");
		if((i+1)%16 == 0)
			printf("\n");
	}
	printf("\n");
	

	fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if(fd < 0){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	printf("fd:%d\n", fd);

	while(1){
		if(sendto(fd, frame, 60, 0, (struct sockaddr *)&sa,
			sizeof(sa)) < 0){
			printf("errno:%d\n", errno);
			perror("write");
			continue;
		}
		printf("send arp\n");
		sleep(1);
	}

	close(fd);

	return 0;
}
