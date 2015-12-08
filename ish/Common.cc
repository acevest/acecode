#include<stdio.h>
#include<stdlib.h>
#include"Common.h"

void fatal(const char *err_msg, int n)
{
	fprintf(stderr,"Error: %s\n",err_msg);
	exit(n);
}
void *my_malloc(size_t size)
{
	void *pt;
	if( (pt=malloc(size)) == NULL )
		fatal("Out of Memory...",1);
	return pt;
}
void *my_realloc(void *p, size_t size)
{
	void *pt;
	if( (pt=realloc(p,size)) == NULL )
		fatal("realloc() failed...",1);
	return pt;
}





#include<string.h>

int my_strlen(const char *s)
{
	return strlen(s);
}
int my_strcmp(const char *s1, const char *s2)
{
	return strcmp(s1, s2);
}
void my_strcpy(char *s1, const char *s2)
{
	strcpy(s1, s2);
}
