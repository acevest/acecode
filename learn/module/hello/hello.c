/*
 *--------------------------------------------------------------------------
 *   File Name:	hello.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Mon Jul 19 14:24:09 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#include<linux/init.h>
#include<linux/module.h>

static int hello_init(void)
{
	printk(KERN_ALERT "Hello Module World\n");
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Goodbye Module World\n");
}


module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL v2");
