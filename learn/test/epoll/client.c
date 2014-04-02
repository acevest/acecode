/*
 *--------------------------------------------------------------------------
 *   File Name:	client.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Jun 24 18:38:20 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <pthread.h>
#include <netinet/tcp.h>

static int terminated = 0;
static char remote_ip[16];
static unsigned int data_len = 0;

void sig_int(int signo);
void *thread(void *arg);

char buf[204800];

int main(int argc, char *argv[])
{

	if(argc != 4)
	{
		printf("useage: %s <datalen> <ip> <client_nums>\n", argv[0]);
		exit(1);
	}

	int client_nums;
	data_len = atoi(argv[1]);
	strcpy(remote_ip, argv[2]);
	client_nums = atoi(argv[3]);

	int i;
	for(i=0; i<2048; i++) {
		buf[i] = 'a' + i%26;
	}

	printf("datalen: %d remote ip: %s client numbers: %d\n",
		data_len, remote_ip, client_nums);

	if(data_len > 1500 || client_nums <=0)
	{
		printf("parameter error\n");
		exit(1);
	}
	

	signal(SIGINT, sig_int);

	pthread_t *pid;
	pid = (pthread_t *) malloc(sizeof(pthread_t)*client_nums);
	if(pid == NULL)
	{
		perror("failed malloc pid array");
		exit(1);
	}
	for(i=0; i<client_nums; i++)
	{
		if(pthread_create(pid+i, NULL, thread, NULL) != 0)
		{
			perror("faild create thread");
			exit(1);
		}
	}


	for(i=0; i<client_nums; i++)
	{
		pthread_join(pid[i], NULL);
	}

	return 0;
}


void sig_int(int signo)
{
	terminated =1;
}

void *thread(void *arg)
{

	struct sockaddr_in	serv;
	memset(&serv, 0, sizeof(serv));
	serv.sin_family		= AF_INET;
	serv.sin_port		= htons(4321);
	serv.sin_addr.s_addr	= inet_addr(remote_ip);


	int sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1)
	{
		perror("socket failed");
		exit(1);
	}

	int size = data_len;
	setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, &size, sizeof(size));
	
	if(connect(sock, (struct sockaddr*)&serv, sizeof(serv)) != 0)
	{
		perror("connect");
		exit(1);
	}

	unsigned long count = 0;
	while(!terminated)
	{
		send(sock, buf, data_len, 0);
		printf("count: %d\n", count); count++;
	}

	//send(sock, buf, 1, 0);
	close(sock);

	//printf("%dbytes, %dMB\n", (count*data_len), (count*data_len)>>20);
	printf("%dMB\n", (count*data_len)>>20);

	return 0;
}
