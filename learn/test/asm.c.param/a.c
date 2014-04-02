#include<stdio.h>
#include<a.h>

extern void asm_fun();

struct pa
{
	unsigned int a;
	unsigned int b;
};
#if PTR1
void c_fun(unsigned int a, unsigned int b)
{
	printf("%d %d\n", a, b);
}
#endif
#if PTR2
void c_fun(struct pa *p)
{
	printf("%d %d\n",p->a, p->b);
}
#endif
#if PTR3
__attribute__ ((regparm(1))) void c_fun(struct pa *p)
{
	printf("%d %d\n",p->a, p->b);
}
#endif
#if PTR4
__attribute__((regparm(3))) void c_fun(int a, int b, int c)
{
	printf("%x %x %x\n", a, b, c);
}
#endif
int main()
{
	asm_fun();

	return 0;
}
