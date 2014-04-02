/*
 *--------------------------------------------------------------------------
 *   File Name:	sysc.time.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sat Jun 26 10:16:49 2010
 * 
 *--------------------------------------------------------------------------
 */
#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


//#define	TIMES	(2000000000)
#define	TIMES	(20000000)
//#define	TIMES	(20000)

int func()
{
	int i,b, c;
	i = b;
	b = c;
	c = i;
	i = b;
	b = c;
	c = i;
	i = b;
	b = c;
	c = i;
	return 0;
}


int sysc()
{
	asm("int $0x80"::"a"(20));

}

unsigned long delta = 0;

void disp_result(struct timeval begin, struct timeval end)
{
	unsigned long usec = (end.tv_sec - begin.tv_sec)*1000000 + end.tv_usec - begin.tv_usec;

	printf("usec: %d\n", usec - delta);
}

int main()
{

	struct timeval	tv_begin, tv_end;
	int i;

	gettimeofday(&tv_begin, NULL);
	for(i=0; i<TIMES; i++)
	{
	}
	gettimeofday(&tv_end, NULL);
	delta = (tv_end.tv_sec - tv_begin.tv_sec)*1000000 + tv_end.tv_usec - tv_begin.tv_usec;
	printf("delta: %d\n", delta);


#if 1
	printf("syscall:");
	gettimeofday(&tv_begin, NULL);
	for(i=0; i<TIMES; i++)
	{
		getpid();
	}
	gettimeofday(&tv_end, NULL);
	disp_result(tv_begin, tv_end);

	printf("sysc:");
	gettimeofday(&tv_begin, NULL);
	for(i=0; i<TIMES; i++)
	{
		sysc();
	}
	gettimeofday(&tv_end, NULL);
	disp_result(tv_begin, tv_end);

	printf("function:");
	gettimeofday(&tv_begin, NULL);
	for(i=0; i<TIMES; i++)
	{
		func();
	}
	gettimeofday(&tv_end, NULL);
	disp_result(tv_begin, tv_end);

#endif

	int fd;
	fd = open("/dev/zero", O_RDWR);
	if(fd < 0)
	{
		perror("open failed");
		exit(1);
	}

#define	LEN	256
	char buf[LEN];
	printf("read:");
	gettimeofday(&tv_begin, NULL);
	for(i=0; i<TIMES; i++)
	{
		read(fd, buf, 1);
	}
	gettimeofday(&tv_end, NULL);
	disp_result(tv_begin, tv_end);

	printf("write:");
	gettimeofday(&tv_begin, NULL);
	for(i=0; i<TIMES; i++)
	{
		write(fd, buf, 1);
	}
	gettimeofday(&tv_end, NULL);
	disp_result(tv_begin, tv_end);

#if 0
	printf("syscall gettimeofday:");
	struct timeval tv;
	gettimeofday(&tv_begin, NULL);
	for(i=0; i<TIMES; i++)
	{
		gettimeofday(&tv, NULL);
	}
	gettimeofday(&tv_end, NULL);
	disp_result(tv_begin, tv_end);
#endif

	return 0;
}
