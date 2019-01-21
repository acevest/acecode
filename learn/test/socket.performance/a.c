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
#include<pthread.h>

static int terminated = 0;
static char remote_ip[16];
static unsigned int data_len = 0;

void sig_int(int signo);
void *thread(void *arg);

int main(int argc, char *argv[])
{
	strcpy(remote_ip, "127.0.0.1");
	struct sockaddr_in	serv;
	memset(&serv, 0, sizeof(serv));
	serv.sin_family		= AF_INET;
	serv.sin_port		= htons(6666);
	serv.sin_addr.s_addr	= inet_addr(remote_ip);


	int sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1)
	{
		perror("socket failed");
		exit(1);
	}

	int flags;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &flags, sizeof(flags));

	struct sockaddr_in cliaddr;
	cliaddr.sin_family		= AF_INET;
	cliaddr.sin_addr.s_addr	= htonl(INADDR_ANY);
	cliaddr.sin_port		= htons(5555);
	if(bind(sock, (struct sockaddr*)&cliaddr, sizeof(cliaddr)) == -1)
	{
		perror("bind failed");
		exit(1);
	}

	if(connect(sock, (struct sockaddr*)&serv, sizeof(serv)) != 0)
	{
		perror("connect");
		exit(1);
	}

	close(sock);

	return 0;
}
