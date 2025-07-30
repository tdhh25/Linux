#include <linux/module.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/device.h>

static int hello_major = 0;
static char hello_buff[100] = {0};
static struct class* hello_class;

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
	hello_major = register_chrdev(0, "hello_drv", &hello_drv);
	hello_class = class_create(THIS_MODULE, "hello_class");
	device_create(hello_class, NULL, MKDEV(hello_major, 0), NULL, "hello");

	return 0;
}

static void hello_drv_exit(void)
{
	device_destroy(hello_class, MKDEV(hello_major, 0));
	class_destroy(hello_class);
	unregister_chrdev(hello_major, "hello_drv");
}

MODULE_LICENSE("GPL");
module_init(hello_drv_init);
module_exit(hello_drv_exit);

