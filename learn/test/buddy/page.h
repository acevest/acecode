/*
 *--------------------------------------------------------------------------
 *   File Name:	page.h
 * 
 * Description:	none
 * 
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 
 *     Version:	1.0
 * Create Date: Sat Feb  7 21:47:42 2009
 * Last Update: Sat Feb  7 21:47:42 2009
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_PAGE_H
#define	_PAGE_H

#include<list.h>

#define	PAGE_SHIFT	(12)
#define	PAGE_SIZE	(1UL << PAGE_SHIFT)
#define	PAGE_MASK	(~((1UL << PAGE_SHIFT)-1))

#define	PAGE_OFFSET	(0xC0000000)
#define	PAGE_UP(page) 		((page + PAGE_SIZE -1) & PAGE_MASK)
#define	PAGE_ALIGN(page)	(page & PAGE_MASK)

#define va2pa(x) (((unsigned long)(x)) - PAGE_OFFSET)
#define pa2va(x) ((void *) (((unsigned long)(x)) + PAGE_OFFSET))

#define	MAX_ORDER	10

typedef struct page
{
	//struct page *prev, *next;
	ListHead list;
	unsigned int mapNR;
} Page, *pPage;

typedef struct free_area
{
	//struct page *prev, *next;
	ListHead freeList;
	unsigned char *map;
	unsigned int mapSize;
	unsigned int count;
} FreeArea, *pFreeArea;


extern FreeArea freeArea[MAX_ORDER];

#endif //_PAGE_H
