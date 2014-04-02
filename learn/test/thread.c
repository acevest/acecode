/*
 *--------------------------------------------------------------------------
 *   File Name:	thread.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Fri Dec 11 13:07:31 2009
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */


#include<stdio.h>
#include<pthread.h>


__thread n1,n2;

int n3;


#if 1
void testhread(int id)
{
	int a;


	n1 += (id == 1)? 1: -1;
	n2 += (id == 1)? 1: -1;
}

void * thread(void *arg)
{
	int id = (int)arg;

	while(1)
	{
		testhread(id);
		printf("Thread ID: %d\tn:%d %d\n", id, n1,n2);
		sleep(1);
	}

	return NULL;
}


int main()
{

	pthread_t t1, t2;


	pthread_create(&t1, NULL, thread, (void*)1);
	pthread_create(&t2, NULL, thread, (void*)2);

	while(1);

	return 0;
}
#endif
