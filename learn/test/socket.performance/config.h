/*
 *--------------------------------------------------------------------------
 *   File Name:	config.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Fri Jun 25 15:40:12 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_CONFIG_H
#define	_CONFIG_H

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define	PORT	(5454)
#define	LEN	(20480)
#define	MAXTHDS	(4096)


static inline void print_result(struct timeval begin, unsigned long long size, unsigned long long npkt)
{
	struct timeval end;
	unsigned long usec;
	double sec;

	gettimeofday(&end, NULL);

	usec	= (end.tv_sec - begin.tv_sec)*1000000 + end.tv_usec - begin.tv_usec;
 	sec	= usec/1000000.0;

	printf("usec: %d sec:%0.2f\n", usec, sec);
	printf("%llubytes %lluMB\n", size, size>>20);
	printf("%llu packets...\n", npkt);
}

static inline int chk_quit()
{
	return 1;


	return 0;
}

static inline void print_tips()
{
	printf("Press Ctrl+C to print result...\n");
	printf("Press Ctrl+\\ to print exit...\n"); 
}

#endif //_CONFIG_H
