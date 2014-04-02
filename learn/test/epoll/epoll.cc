/*
 *--------------------------------------------------------------------------
 *   File Name:	epoll.cc
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Fri May 13 16:18:07 2011
 * 
 * Description:	为实验室写的用来测epoll的性能,我也不知道好不好
 * 
 *--------------------------------------------------------------------------
 */
#include <cstdio>
#include <cerrno>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <fcntl.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define	MAXEVENTS	1024
struct epoll_event events[MAXEVENTS];
#define	MAXLINE		4096
char	line[MAXLINE];

using namespace std;


void setnonblocking(int sock_fd) {

	int flags = fcntl( sock_fd , F_GETFL, 0);

	flags |= O_NONBLOCK;

	if (fcntl(sock_fd, F_SETFL, flags) == -1) {
		perror("fcntl");
		exit(EXIT_FAILURE);
	}

}

int main() {
	
	int listenfd;
	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd == -1) {
		perror("socket");
		exit(EXIT_FAILURE);
	}

	int flags;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &flags, sizeof(flags));

	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(4321);
	if(bind(listenfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1) {
		perror("bind");
		exit(EXIT_FAILURE);
	}

	if(listen(listenfd, SOMAXCONN) == -1) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	int epollfd = epoll_create(256);// 参数无用了
	if(epollfd == -1) {
		perror("epoll create");
		exit(EXIT_FAILURE);
	}
	struct epoll_event ev;
	ev.data.fd = listenfd;
	ev.events = EPOLLIN | EPOLLET;
	if(epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &ev) == -1) {
		perror("epoll ctl");
		exit(EXIT_FAILURE);
	}

	while(true) {

		cout<<__LINE__<<endl;
		int nfds = epoll_wait(epollfd, events, SOMAXCONN, 500);
		cout<<__LINE__<<" "<<nfds<<endl;
		for(int i=0; i<nfds; i++) {
			if(events[i].data.fd == listenfd) {
				socklen_t len;
				int connfd = accept(listenfd, (struct sockaddr*)&clientaddr, &len);
				if(connfd == -1) {
					perror("accept");
					exit(EXIT_FAILURE);
				}
				char dst[256];
				inet_ntop(AF_INET, &clientaddr, dst, sizeof(clientaddr));
				cout<<"connect from: "<<dst<<endl;

				setnonblocking(connfd);

				ev.data.fd = connfd;
				ev.events  = EPOLLIN |EPOLLET;
				epoll_ctl(epollfd, EPOLL_CTL_ADD, connfd, &ev);			
			} else if(events[i].events & EPOLLIN) {
				int sockfd;
				if((sockfd = events[i].data.fd) < 0) {
		cout<<__LINE__<<endl;
					cout<<"epoll fd < 0"<<endl;
					continue;
				}
				int n;
		cout<<__LINE__<<endl;
				if((n=read(sockfd, line, MAXLINE-1)) < 0) {
					if(errno == ECONNRESET) {
						close(sockfd);
						events[i].data.fd = -1;
					} else {
						cout<<"read line error"<<endl;
					}
				} else if(n == 0) {
					close(sockfd);
					events[i].data.fd = -1;
				}
		cout<<__LINE__<<endl;
				assert(n <= MAXLINE);
				line[n] = 0;
				static int k = 0;
				cout<<"line:"<<k++<<endl;

				
			} else if(events[i].events & EPOLLOUT) {
				cout<<"unwrite part"<<endl;
			}
		}

	}


	return 0; 
}
