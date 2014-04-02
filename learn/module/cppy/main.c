/*
 *--------------------------------------------------------------------------
 *   File Name:	main.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Oct 28 19:41:25 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#include<linux/init.h>
#include<linux/module.h>
#include<linux/types.h>
#include<linux/kdev_t.h>	/* MAJOR */
#include<linux/fs.h>		/* alloc_chrdev_region */
#include<linux/slab.h>		/* kmalloc kfree */
#include<asm/uaccess.h>		/* copy_to_user copy_from_user */
#include"cppy.h"

int cppy_major;
int cppy_minor;
struct cppy_dev *cppy_devs;


int cppy_open(struct inode *inode, struct file *filp);

struct file_operations cppy_fops = {
	.owner	= THIS_MODULE,
	.open	= cppy_open,
};

int cppy_open(struct inode *inode, struct file *filp) {


	return 0;
}

static void cppy_setup_cdev(int index)
{
	int	err;
	int	devno;
	struct cppy_dev *dev;

	devno	= MKDEV(cppy_major, index);
	dev	= cppy_devs + index;

	cdev_init(&dev->cdev, &cppy_fops);
	dev->cdev.owner	= THIS_MODULE;
	dev->cdev.ops	= &cppy_fops;
	err = cdev_add(&dev->cdev, devno, 1);

	if(err)
	{
		printk(KERN_NOTICE "Error %d adding cppy%d", err, index);
	}
}

static int cppy_init(void) {
	int	i;
	int	ret;
	dev_t	dev;

	/* 为本驱动程序动态申请一个主设备号 */
	ret = alloc_chrdev_region(&dev, 0, CPPY_DEVS, "cppy");

	cppy_major = MAJOR(dev);
	if(ret < 0) {
		printk("cppy: can't get major\n");
		return ret;
	}

	cppy_devs = kmalloc(CPPY_DEVS*sizeof(struct cppy_dev), GFP_KERNEL);
	if(cppy_devs == NULL)
	{
		ret = -ENOMEM;
		goto fail_malloc;
	}
	
	for(i=0; i<CPPY_DEVS; i++)
	{
		cppy_setup_cdev(i);
	}


	return 0; /* succeed */
fail_malloc:
	unregister_chrdev_region(dev, CPPY_DEVS);
	return ret;
}

void cppy_exit(void) {
	int	i;

	for(i=0; i<CPPY_DEVS; i++)
	{
		cdev_del(&(cppy_devs[i].cdev));
	}
	kfree(cppy_devs);

	unregister_chrdev_region(MKDEV(cppy_major, 0), CPPY_DEVS);
}

module_init(cppy_init);
module_exit(cppy_exit);
MODULE_LICENSE("GPL v2");
