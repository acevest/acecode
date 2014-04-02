/*
 *--------------------------------------------------------------------------
 *   File Name:	pkt.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Wed Jun 23 20:15:04 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include<stdio.h>
#include<stdlib.h>
#include<libnet.h>

char buf[100000];
int main(int argc, char *argv[])
{
	//char *dst_ip_str = "192.168.100.128";
	//char *dst_ip_str = "125.211.213.130";
	//char *dst_ip_str = "218.7.43.28";
	char *dst_ip_str = "74.125.71.105";
	char *src_ip_str = "192.168.100.64";
	unsigned char src_hw_addr[6] = {0x00, 0x21, 0x86, 0x96, 0x62, 0x49};
	//unsigned char dst_hw_addr[6] = {0x00, 0x1a, 0x92, 0xe8, 0x7a, 0x12};
	unsigned char dst_hw_addr[6] = {0x00, 0x0f, 0xe2, 0x19, 0x78, 0xa9};
	//unsigned char dst_hw_addr[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};


	unsigned long dst_ip, src_ip;

	char err_msg[LIBNET_ERRBUF_SIZE];

	libnet_ptag_t ip_tag = 0;
	libnet_ptag_t eth_tag= 0;



	libnet_t *l;

	unsigned int playload_size = 0;
	int send_size = 0;


	if(argc != 2)
	{
		printf("%s <packet_size>\n", argv[0]);
		exit(1);
	}


	playload_size = atoi(argv[1]);


	l = libnet_init(
		LIBNET_LINK,
		"eth0",
		err_msg);


	dst_ip = libnet_name2addr4(l, dst_ip_str, LIBNET_RESOLVE);
	src_ip = libnet_name2addr4(l, src_ip_str, LIBNET_RESOLVE);


	ip_tag = libnet_build_ipv4(
		LIBNET_IPV4_H + playload_size,
		0,
		0x3111,
		0xbFFF,
		64,
		IPPROTO_TCP,
		0,
		src_ip,
		dst_ip,
		buf,
		playload_size,
		l,
		ip_tag);

	eth_tag = libnet_build_ethernet(
		dst_hw_addr,
		src_hw_addr,
		ETHERTYPE_IP,
		NULL,
		0,
		l,
		eth_tag);

	send_size = libnet_write(l);
	printf("send packet size : %d bytes\n", send_size);

	if(send_size<0)
		printf("err: %s\n", err_msg);
	
	libnet_destroy(l);

	
	return 0;
}
