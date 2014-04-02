/*
 *--------------------------------------------------------------------------
 *   File Name:	cppy.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Oct 28 19:55:12 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_CPPY_H
#define	_CPPY_H

#include<linux/cdev.h>

#define	CPPY_DEVS	3

struct	cppy_dev {
	struct cdev cdev;
};

#endif //_CPPY_H
