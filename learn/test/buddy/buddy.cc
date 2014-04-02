/*
 *--------------------------------------------------------------------------
 *   File Name:	buddy.cc
 * 
 * Create Date: Wed Jan 20 21:32:39 2010
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 		Information Security Research Center Of
 * 		Harbin Engineering University
 * 
 * Description:	none
 * 
 * 
 *--------------------------------------------------------------------------
 */

#include"buddy.h"
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

FreeArea freeArea[MAX_ORDER];

void init()
{
	for(int i=0; i<MAX_ORDER; i++)
	{
		int mapSize = (MM_SIZE>>(i+1+3));
		freeArea[i].mapSize = mapSize;
		freeArea[i].map = (unsigned char *) malloc(mapSize);
		if(freeArea[i].map == NULL)
		{
			cout<<"Can't allocate memory"<<endl;
		}

		memset(freeArea[i].map, 0, freeArea[i].mapSize);

		printf("%d\t%d\t0x%08x\n", i, freeArea[i].mapSize,
					freeArea[i].map);
	}
}

void destroy()
{
	for(int i=0; i<MAX_ORDER; i++)
	{
		if(freeArea[i].map != NULL)
			free(freeArea[i].map);
	}
}

int main()
{

	init();

	destroy();

	return 0;
}
