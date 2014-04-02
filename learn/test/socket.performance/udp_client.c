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
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<signal.h>
#include"config.h"
#include<pthread.h>
#include<time.h>

static int terminated = 0;
static char remote_ip[16];
static unsigned int data_len = 0;
static unsigned int pkts = 0; //每建立一次链接发送data_len长的数据包pkts次
static int client_nums;

static char buf[LEN];
static struct timeval begin;
static unsigned long long np[MAXTHDS];
static unsigned long long sz[4096];
static struct timespec delay;

void sig_int(int signo);
void sig_quit(int signo);
void *thread(void *arg);

int main(int argc, char *argv[])
{

	if(argc != 6)
	{
		printf("useage: %s <ip> <datalen> <pkts_per_socket> <client_nums> <delay>\n", argv[0]);
		exit(1);
	}


	strcpy(remote_ip, argv[1]);
	data_len = atoi(argv[2]);
	pkts	= atoi(argv[3]);
	client_nums = atoi(argv[4]);
	delay.tv_sec	= 0;
	delay.tv_nsec	= atoi(argv[5]);

	printf("remote ip: %s datalen:%d pkts per socket: %d client numbers: %d\n",
		remote_ip, data_len, pkts, client_nums);

	print_tips();
#if 0
	if(data_len <= 42)
	{
		printf("parameter error\n");
		exit(1);
	}
	data_len -= 42;

	if(data_len > 1500 || client_nums <=0)
	{
		printf("parameter error\n");
		exit(1);
	}
#endif	

	signal(SIGINT,	sig_int);
	signal(SIGQUIT,	sig_quit);

	int i;
	pthread_t *pid;
	pid = (pthread_t *) malloc(sizeof(pthread_t)*client_nums);
	if(pid == NULL)
	{
		perror("failed malloc pid array");
		exit(1);
	}

	gettimeofday(&begin, NULL);

	for(i=0; i<client_nums; i++)
	{
		if(pthread_create(pid+i, NULL, thread, (void*)i) != 0)
		{
			perror("faild create thread");
			exit(1);
		}
	}


	for(i=0; i<client_nums; i++)
	{
		pthread_join(pid[i], NULL);
	}


	sig_int(SIGINT);	// 偷下懒

	return 0;
}


void sig_int(int signo)
{
	int i;
	unsigned long long npkt = 0;
	unsigned long long size = 0;

	for(i=0; i<client_nums; i++)
	{
		npkt += np[i];
		size += sz[i];
	}


	print_result(begin, size, npkt);
}
void sig_quit(int signo)
{
	terminated = chk_quit();
}

void *thread(void *arg)
{
	int id = (int)arg;

	struct sockaddr_in	serv;
	memset(&serv, 0, sizeof(serv));
	serv.sin_family		= AF_INET;
	serv.sin_port		= htons(PORT);
	serv.sin_addr.s_addr	= inet_addr(remote_ip);

	np[id] = 0;
	sz[id] = 0;


	while(!terminated)
	{
		int sock;
		sock = socket(AF_INET, SOCK_DGRAM, 0);
		if(sock == -1)
		{
			perror("socket failed");
			exit(1);
		}

		if(connect(sock, (struct sockaddr*)&serv, sizeof(serv)) != 0)
		{
			perror("connect");
			exit(1);
		}

		socklen_t len = sizeof(serv);
		int c = 0;
		int size = 0;
		buf[0] = 1;
		while(c++ < pkts)
		{
			size = sendto(sock, buf, data_len, 0, (struct sockaddr *) &serv, len);
			sz[id] += size;
			np[id]++;
			nanosleep(&delay, NULL);
		}
		close(sock);
	}

	return 0;
}
