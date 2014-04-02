/*
 *--------------------------------------------------------------------------
 *   File Name:	min.pow2.number.c
 * 
 * Description:	给一个数，求大于或等于它的最小的2的幂次数。
 * 		以下给出四种算法。测试表明汇编执行效率最高。
 * 		测试结果如下(单位：us)：
 * 		delta: 597728
 * 		delta: 10032967
 * 		delta: 10880279
 * 		delta: 1012883
 * 		因为我要的是2048以下的随机数，所以我估计第四个和第一个
 * 		应该差不了太多
 *
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 
 *     Version:	1.0
 * Create Date: Mon Jun  1 10:47:53 2009
 * Last Update: Mon Jun  1 10:47:53 2009
 *     Version:	1.1
 * Last Update: Mon Aug  3 13:45:45 2009
 * 
 *--------------------------------------------------------------------------
 */

#include<stdio.h>
#include<sys/time.h>
inline unsigned int funA(unsigned int size)
{
	asm("cmpl $1,%%eax;"\
	"jbe 1f;"\
	"decl %%eax;"\
	"bsrl %%eax,%%ecx;"\
	"incb %%cl;"\
	"movl $1,%%eax;"\
	"shl %%cl,%%eax;"\
	"1:"::"a"(size));
}
//此函数不正确
inline unsigned int funB(unsigned int x)
{
	int res = 1;
	while(x)
	{
		x>>=1;
		res<<=1;
	}
	return res;
}
inline unsigned int funC(unsigned int x)
{
	unsigned int res = 1,tmp=x;
	while(tmp)
	{
		tmp>>=1;
		res<<=1;
	}
	if(x==0 || (x<<1) == res) res>>=1;
	return res;
}

inline unsigned int funD(unsigned int x)
{
	switch(x)
	{
	case 3	...	4:	return 0x4;
	case 5	...	8:	return 0x8;
	case 9	...	16:	return 0x10;
	case 17	...	32:	return 0x20;
	case 33	...	64:	return 0x40;
	case 65	...	128:	return 0x80;
	case 129	...	256:	return 0x100;
	case 257	...	512:	return 0x200;
	case 513	...	1024:	return 0x400;
	case 1025	...	2048:	return 0x800;
	case 2049	...	4096:	return 0x1000;
	case 4097	...	8192:	return 0x2000;
	case 8193	...	16384:	return 0x4000;
	case 16385	...	32768:	return 0x8000;
	case 32769	...	65536:	return 0x10000;
	case 0x10001	...	0x20000: return 0x20000;
	case 0x20001	...	0x40000: return 0x40000;
	case 0x40001	...	0x80000: return 0x80000;
	case 0x80001	...	0x100000:	return 0x100000;
	case 0x100001	...	0x200000:	return 0x200000;
	case 0x200001	...	0x400000:	return 0x400000;
	case 0x400001	...	0x800000:	return 0x800000;
	case 0x800001	...	0x1000000:	return 0x1000000;
	case 0x1000001	...	0x2000000:	return 0x2000000;
	case 0x2000001	...	0x4000000:	return 0x4000000;
	case 0x4000001	...	0x8000000:	return 0x8000000;
	}

	return x;
}

int main()
{

	struct timeval tvBegin, tvEnd;
	unsigned int delta;
	unsigned int i;
#define	TIMES	100000000

	gettimeofday(&tvBegin, NULL);
	for(i=0; i<TIMES; i++)
		funA(i);
	gettimeofday(&tvEnd, NULL);
	delta = (tvEnd.tv_sec - tvBegin.tv_sec) * 1000000
		+ tvEnd.tv_usec - tvBegin.tv_usec;
	printf("delta: %d\n", delta);

	gettimeofday(&tvBegin, NULL);
	for(i=0; i<TIMES; i++)
		funB(i);
	gettimeofday(&tvEnd, NULL);
	delta = (tvEnd.tv_sec - tvBegin.tv_sec) * 1000000
		+ tvEnd.tv_usec - tvBegin.tv_usec;
	printf("delta: %d\n", delta);


	gettimeofday(&tvBegin, NULL);
	for(i=0; i<TIMES; i++)
		funC(i);
	gettimeofday(&tvEnd, NULL);
	delta = (tvEnd.tv_sec - tvBegin.tv_sec) * 1000000
		+ tvEnd.tv_usec - tvBegin.tv_usec;
	printf("delta: %d\n", delta);

	gettimeofday(&tvBegin, NULL);
	for(i=0; i<TIMES; i++)
		funD(i);
	gettimeofday(&tvEnd, NULL);
	delta = (tvEnd.tv_sec - tvBegin.tv_sec) * 1000000
		+ tvEnd.tv_usec - tvBegin.tv_usec;
	printf("delta: %d\n", delta);
	return 0;
}
