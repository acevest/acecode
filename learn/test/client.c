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
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <netinet/tcp.h>
#include<arpa/inet.h>
#include<signal.h>
#include<pthread.h>

static int terminated = 0;
static char remote_ip[16] = "202.118.176.37";
static unsigned int data_len = 0;

void sig_int(int signo);
void *thread(void *arg);

int main(int argc, char *argv[])
{

	if(argc != 2)
	{
		printf("useage: %s <client_nums>\n", argv[0]);
		exit(1);
	}

	int client_nums;
	client_nums = atoi(argv[1]);

	signal(SIGINT, sig_int);

	int i;
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

__thread char buf[20480];
__thread char rd[20480];

static int set_socket_fd(int fd) {
	int flags;
	int on = 1;
	if((flags = fcntl(fd, F_GETFL, 0)) == -1) {
		perror("fcntl get");
		return 0;
	}
	flags |= O_NONBLOCK;
	if(fcntl(fd, F_SETFL, flags) == -1) {
		perror("fcntl set");
		return 0;
	}

	if(setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char *)&on, sizeof(on)) == -1) {
		perror("setsockopt");
		return 0;
	}

	return 1;
}
void *thread(void *arg)
{

	int i;

	for(i=0; i<20480; i++) {
		buf[i] = (i % 26) + 'a';
	}

	struct sockaddr_in	serv;
	memset(&serv, 0, sizeof(serv));
	serv.sin_family		= AF_INET;
	serv.sin_port		= htons(90);
	//serv.sin_addr.s_addr	= inet_addr(remote_ip);
	inet_pton(AF_INET, remote_ip, &serv.sin_addr.s_addr);


	int sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
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

	if(!set_socket_fd(sock)) {
		exit(1);
	}

	unsigned long count = 0;
	while(!terminated)
	{
		write(sock, buf, data_len);
		count++;
		int ret = read(sock, rd, 1024);
		rd[ret] = 0;
		printf("%s\n", rd);
		getchar();
	}

	close(sock);

	return 0;
}
