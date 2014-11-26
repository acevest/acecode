#ifndef	_COMMON_H
#define	_COMMON_H

void fatal(const char *err_msg, int n);
void *my_malloc(size_t size);
void *my_realloc(void *p, size_t size);


int my_strlen(const char *s);
int my_strcmp(const char *s1, const char *s2);
void my_strcpy(char *s1, const char *s2);

#endif	/*_COMMON_H*/
