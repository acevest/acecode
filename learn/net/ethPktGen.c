/*
 *--------------------------------------------------------------------------
 *   File Name:	ethPktGen.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Wed Dec 22 22:28:30 2010
 * 
 * Description: 在中心作实验常常要生成大量的指定大小的数据包.所以就写个.
 * 
 *--------------------------------------------------------------------------
 */

#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/time.h>
#include<arpa/inet.h>
#include<netpacket/packet.h>
#include<netinet/if_ether.h>
#include<netinet/ip.h>


#define	FRM_SZ	(2048)
unsigned char dst[ETH_ALEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
unsigned char src[ETH_ALEN] = {0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa};
char dev[256];

void setDstMacAddr(char *str) {
    int i;
	unsigned long d[ETH_ALEN];
	sscanf(str, "%x:%x:%x:%x:%x:%x",
		d+0, d+1, d+2, d+3, d+4, d+5);
    for(i=0; i<ETH_ALEN; i++) {
        dst[i] = (unsigned char) (0xFF & d[i]);
    }
}

void Usage(char *name) {
	printf("Usage:\n\t%s <mac addr> <device> <npkts> <packet size>\n", name);
}


int main(int argc, char *argv[]){
	char frame[FRM_SZ];
	struct in_addr	sip, dip;
	struct ether_header *eth;
	struct iphdr *ip;
	struct sockaddr_ll sa;
	long long npkts, size;
	int fd;
	struct timeval tvBegin, tvEnd;
	double sec, speed;

	if(argc != 5)
	{
		Usage(argv[0]);
		exit(0);
	}

	setDstMacAddr(argv[1]);
	strcpy(dev, argv[2]);
	npkts = atoi(argv[3]);
	size = atoi(argv[4]);

	if(size<46 || size>1500)
	{
		printf("size is error...\n");
		exit(0);
	}



	eth = (struct ether_header *)(frame);
	ip  = (struct iphdr *)(frame + ETH_HLEN);

	memset(frame, 0, FRM_SZ);

	// 构造ether头
	memcpy(eth->ether_dhost, dst, ETH_ALEN);
	memcpy(eth->ether_shost, src, ETH_ALEN);
	eth->ether_type	= htons(ETHERTYPE_IP);

	// 构造ip头
	ip->ihl = 5;
	ip->version = 4;
	ip->tot_len = htons(size);
	ip->ttl	    = 128;
	
	sa.sll_family	= AF_PACKET;
	sa.sll_ifindex	= if_nametoindex(dev);
    sa.sll_halen    = ETH_ALEN;


	int i;
#if 0
	for(i=0; i<60; i++)
	{
		printf("%02x ", (unsigned char)frame[i]);
		if((i+1)%8 == 0)
			printf(" ");
		if((i+1)%16 == 0)
			printf("\n");
	}
	printf("\n");
#endif
	

	fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if(fd < 0){
		perror("socket");
		exit(EXIT_FAILURE);
	}

	printf("Sending on %s...%d\n", dev, npkts);
	gettimeofday(&tvBegin, NULL);
	i=0;
	while(i++<npkts) {
		if(sendto(fd, frame, ETH_HLEN+size, 0, 
			(struct sockaddr *)&sa, sizeof(sa)) < 0){

			printf("errno:%d\n", errno);
			perror("write");
			continue;
		}
	}
	gettimeofday(&tvEnd, NULL);
	close(fd);

	sec = tvEnd.tv_sec - tvBegin.tv_sec + (tvEnd.tv_usec - tvBegin.tv_usec)/1000000.0;

	speed = size*npkts*8*1.0/(1024*1024*sec);

	printf("time:%.2fs mbps:%.2f(%0.2fMB/s)\n", sec, speed, speed/8);

	return 0;
}
