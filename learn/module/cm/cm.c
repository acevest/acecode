/*
 *--------------------------------------------------------------------------
 *   File Name:	cm.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Thu Sep  1 09:54:49 2011
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
#include<linux/cdev.h>

int cm_major;
struct cm_dev_t {
	struct cdev cdev;
} cm_dev;

static ssize_t cm_read(struct file *filp, char __user *buf, size_t count, loff_t *pos) {
	if(filp->f_op == NULL) {
		printk("CM_READ: %08x\n", 0);
	} else {
		printk("CM_READ: %08x\n", (unsigned int)(filp->f_op->read));
		printk("CM_DEV: %08x\n", (unsigned int)(filp->f_dentry->d_inode->i_cdev->ops->read));
	}

	return 0;
}

static const struct file_operations cm_fops = {
	.owner = THIS_MODULE,
	.read = cm_read
};

int cm_init(void) {
	int ret;
	dev_t devno;

	ret = alloc_chrdev_region(&devno, 0, 1, "cm");
	cm_major = MAJOR(devno);
	
	if(ret < 0) return ret;

	devno = MKDEV(cm_major, 0);

	cdev_init(&cm_dev.cdev, &cm_fops);
	cm_dev.cdev.owner = THIS_MODULE;
	cm_dev.cdev.ops = &cm_fops;
	
	ret = cdev_add(&cm_dev.cdev, devno, 1);
	if(ret < 0) {
		unregister_chrdev_region(devno, 1);
		return ret;
	}

	printk("CM_INIT: %08x\n", (unsigned int)cm_read);

	return 0;
}

void cm_exit(void) {
	cdev_del(&cm_dev.cdev);
	unregister_chrdev_region(MKDEV(cm_major, 0), 1);
}

module_init(cm_init);
module_exit(cm_exit);
MODULE_LICENSE("GPL v2");
