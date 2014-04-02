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
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<signal.h>
#include"config.h"
void do_client(int fd);
void sig_child(int signo);
double get_sec(struct timeval begin, struct timeval end);
int main()
{

	signal(SIGCHLD, sig_child);

	int sock;
	struct sockaddr_in serv;

	sock = socket(AF_INET, SOCK_STREAM, 0);
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


	if(listen(sock, SOMAXCONN) == -1)
	{
		perror("listen failed");
		exit(1);
	}


	int new_sock;
	struct sockaddr_in client;
	pid_t pid;
	int len = sizeof(client);
	while(1)
	{
		new_sock = accept(sock, (struct sockaddr *)&client, &len);


		pid = fork();

		if(pid ==0)
		{
			close(sock);
			do_client(new_sock);
			close(new_sock);
			return 0;
		}

		
	}


	close(sock);

	return 0;
}

char buf[LEN];
void do_client(int fd)
{
	int len;
	unsigned long size = 0;
	struct	timeval	begin, end;
	gettimeofday(&begin, NULL);
	while(1)
	{
		//len = recv(fd, buf, LEN, 0);
		len = read(fd, buf, LEN);

		if(len <= 1)
			break;

		printf("len: %d\n", len);

		size += len;
	}
	gettimeofday(&end, NULL);
	double sec = get_sec(begin, end);
	//printf("%dbytes %dMB %fMB/s\n", 
	//	count*LEN, (count*LEN)>>20, ((count*LEN)>>20)/sec);
	printf("%ldMB\t%0.2fMB/s\n", (size)>>20, ((size)>>20)/sec);
}
void sig_child(int signo)
{
	pid_t	pid;
	int	stat;
	while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
	{
		//printf("child %d terminated\n", pid);
	}
	
}

double get_sec(struct timeval begin, struct timeval end)
{
        unsigned long usec = (end.tv_sec - begin.tv_sec)*1000000 + end.tv_usec - begin.tv_usec;

	return (usec/1000000.0);
}
