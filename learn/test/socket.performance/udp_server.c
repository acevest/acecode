/*
 *--------------------------------------------------------------------------
 *   File Name:	server.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Jun 24 18:38:17 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include"config.h"

static unsigned long long size = 0;
static unsigned long long npkt = 0;
static struct timeval begin;
static char	buf[LEN];
static int	terminated = 0;
static int sock;

void sig_int(int signo)
{
	print_result(begin, size, npkt);
}
void sig_quit(int signo)
{
	print_result(begin, size, npkt);
	exit(0);
	terminated = chk_quit();
}

int main()
{

	signal(SIGINT,	sig_int);
	signal(SIGQUIT,	sig_quit);

	struct sockaddr_in serv;

	print_tips();

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if(sock == -1)
	{
		perror("socket failed");
		exit(1);
	}

	int flags;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &flags, sizeof(flags));

	serv.sin_family		= AF_INET;
	serv.sin_addr.s_addr	= htonl(INADDR_ANY);
	serv.sin_port		= htons(PORT);
	if(bind(sock, (struct sockaddr*)&serv, sizeof(serv)) == -1)
	{
		perror("bind failed");
		exit(1);
	}


	struct sockaddr_in client;
	socklen_t clientlen = sizeof(client);
	int len = 0;

	gettimeofday(&begin, NULL);

	while(!terminated)
	{
		len = recvfrom(sock, buf, LEN, 0, (struct sockaddr*)&client, &clientlen);
		if(len<0)
		perror("000:");
		if(len<=0) continue;
		size += len;
		npkt++;	
	}


	close(sock);

	print_result(begin, size, npkt);

	return 0;
}

