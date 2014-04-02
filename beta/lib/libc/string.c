/*
 *--------------------------------------------------------------------------
 *   File Name:	string.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Sat Oct  2 23:24:58 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include<string.h>

char *strcpy(char *dest, const char *src)
{
	char *p = dest;
	while((*dest++ = *src++));
	return p;
}

size_t strlen(const char *str)
{
	int i=0;
	while(*str++) i++;
	return i;
}

int	strcmp(const char *a, const char *b)
{
	int delta;
	while (*a || *b)
	{
		delta = *a++ - *b++;
		if(delta != 0)
			return delta;
	}
	return 0;
}

int	strncmp(const char *a, const char *b, size_t count)
{
	unsigned char c1, c2;
	int delta;
	while(count)
	{
		c1 = *a++;
		c2 = *b++;

		delta = c1-c2;
		if(delta != 0)
			return delta;

		if(c1 == 0)
			break;
		
		count--;
	}

	return 0;
}

char	*strcat(char *dest, const char *src)
{
	char *tmp = dest;
	while(*dest) dest++;
	while((*dest++ = *src++) != '\0');
	return tmp;
}

void *memcpy(void *dest, const void *src, size_t size)
{
	char *d = (char *) dest;
	char *s = (char *) src;
	while(size-->0) {*d = *s;d++;s++;}
	return dest;
}

void	memset(char *dest, char ch, size_t size)
{
	while(size--) *dest++ = ch;
}
