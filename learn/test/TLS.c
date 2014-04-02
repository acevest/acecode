/*
 *--------------------------------------------------------------------------
 *   File Name:	TLS.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Wed Aug 18 08:53:37 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#include <stdio.h>
#include <signal.h>
#include <pthread.h>


int terminated = 0;

__thread int pid;

void fun(int id)
{
	printf("%d---%d\n", id, pid);
}


void *thread(void *arg)
{

	int	id;
	id	= *((int*)arg); 
	pid	= *((int*)arg); 
	while(!terminated)
	{
		fun(id);
		sleep(1);
	}

	return NULL;
}


void sig_int(int signo)
{
	terminated = 1;
}

#define	N 3
int main()
{
	int i;
	int arg[N];
	pthread_t id[N];

	signal(SIGINT, sig_int);

	for(i=0; i<N; i++)
		arg[i] = i;

	for(i=0; i<N; i++)
		pthread_create(id+i, NULL, thread, arg+i);

	for(i=0; i<N; i++)
		pthread_join(id[i], NULL);

	return 0;
}
