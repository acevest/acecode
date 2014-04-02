/*
 *--------------------------------------------------------------------------
 *   File Name:	string.h
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sat Oct  2 23:31:30 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#ifndef	_STRING_H
#define	_STRING_H

#include<sys/types.h>

char	*strcpy(char *dest, const char *src);
size_t	strlen(const char *str);
int	strcmp(const char *a, const char *b);
int	strncmp(const char *a, const char *b, size_t count);
char	*strcat(char *dest, const char *src);


void	*memcpy(void *dest, const void *src, size_t size);
void	memset(char *dest, char ch, size_t size);


#endif //_STRING_H
