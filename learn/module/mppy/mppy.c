/*
 *--------------------------------------------------------------------------
 *   File Name:	mppy.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Tue Nov 30 15:25:20 2010
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */

#include<linux/init.h>
#include<linux/types.h>
#include<linux/module.h>
#include<linux/miscdevice.h>
#include<linux/fs.h>

#define	MPPY_ERR(args...) printk(KERN_ERR "mppy: " args)

static int mppy_open(struct inode *inode, struct file *file)
{

	return 0;
}

static ssize_t mppy_read(struct file *file, char __user *buf, size_t count,
			loff_t *pos)
{
	return 0;
}


static struct file_operations mppy_fops = {
	.owner	= THIS_MODULE,
	.open	= mppy_open,
	.read	= mppy_read,
	.llseek	= no_llseek,
};

/* miscdev 类驱动默认了主设备号，所以这类驱动只需要指定从设备号 */
static struct miscdevice mppy_dev = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= "mppy",
	.fops	= &mppy_fops,
};


static int mppy_init(void)
{
	int	err;
	err = misc_register(&mppy_dev);
	if(err)
	{
		MPPY_ERR("Failed to register misc device\n");
		return err;
	}

	return err;
}
static void mppy_exit(void)
{
	misc_deregister(&mppy_dev);
}

module_init(mppy_init);
module_exit(mppy_exit);
MODULE_LICENSE("GPL v2");
