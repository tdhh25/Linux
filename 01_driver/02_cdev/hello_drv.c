#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>

static char hello_buff[100] = {0};
static struct class* hello_class;
static dev_t hello_dev;
static struct cdev hello_cdev;

static ssize_t hello_read (struct file *file, char __user *buff, size_t size, loff_t *offset)
{
	unsigned long ret, len = (size > 100) ?  100: size;

	ret = copy_to_user(buff, hello_buff, len);

	return len;
}

static ssize_t hello_write (struct file *file, const char __user *buff, size_t size, loff_t *offset)
{
	unsigned long ret, len = (size > 100) ?	100: size;

	ret = copy_from_user(hello_buff, buff, len);

	return len;
}

static int hello_open (struct inode *inode, struct file *file)
{
	printk("hello_open!");

	return 0;
}

int hello_release (struct inode *inode, struct file *file)
{
	printk("hello_release!");

	return 0;
}


static struct file_operations hello_drv = {
	.owner = THIS_MODULE,
	.read = &hello_read,
	.write = &hello_write,
	.open = &hello_open,
	.release = &hello_release
};

static int hello_drv_init(void)
{
	alloc_chrdev_region(&hello_dev, 0, 1, "hello_drv");
	cdev_init(&hello_cdev, &hello_drv);
	cdev_add(&hello_cdev, hello_dev, 1);
	
	hello_class = class_create(THIS_MODULE, "hello_class");
	device_create(hello_class, NULL, hello_dev, NULL, "hello");

	return 0;
}

static void hello_drv_exit(void)
{
	device_destroy(hello_class, hello_dev);
	class_destroy(hello_class);
	cdev_del(&hello_cdev);
	unregister_chrdev_region(hello_dev, 1);
}

MODULE_LICENSE("GPL");
module_init(hello_drv_init);
module_exit(hello_drv_exit);

