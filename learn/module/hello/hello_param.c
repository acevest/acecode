/*
 *--------------------------------------------------------------------------
 *   File Name:	hello_param.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Mon Jul 19 14:48:59 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#include<linux/init.h>
#include<linux/module.h>

static int	first = 0;
static char	*second = NULL;

/*
 * short	: short
 * ushort	: unsigned short
 * int		: int
 * uint		: unsigned int
 * long		: long
 * ulong	: unsigned long
 * charp	: char *
 * bool		: int
 * invbool	: int
 * intarray	: int *
 */

static int hello_param_init(void)
{
	printk("first: %d\nsecond:%s\n", first, second);

	return 0;
}

static void hello_param_exit(void)
{
	printk("hello_param_exit()...\n");

}


module_param(first,	int, 	0);
module_param(second,	charp,	0);

module_init(hello_param_init);
module_exit(hello_param_exit);

MODULE_LICENSE("GPL v2");

