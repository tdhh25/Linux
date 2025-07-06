#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <asm/gpio.h>


struct gpios_desc {
	int gpio;
	int irq;
	char* name;
	int key;
};
static int led_major;
static char led_buff[2];
static struct class* led_class;
static struct gpios_desc gpios[2] = {
	{131, 0, "led0", },
};

static ssize_t led_read (struct file *file, char __user *buff, size_t size, loff_t *offset)
{
	unsigned long ret;
	int index;
	
	if(size > 2)
		return -EINVAL;

	ret = copy_from_user(led_buff, buff, 1);

	if(led_buff[0] >= 2)
		return EINVAL;

	index = led_buff[0];
	led_buff[1] = gpio_get_value(gpios[index].gpio);
	ret = copy_to_user(buff, led_buff, 2);

	return 2;

}

static ssize_t led_write (struct file *file, const char __user *buff, size_t size, loff_t *offset)
{
	unsigned long ret;
	int index;

	if(size > 2)
		return -EINVAL;
	
	ret = copy_from_user(led_buff, buff, size);

	if(led_buff[0] >= 2)
		return -EINVAL;

	index = led_buff[0];
	gpio_set_value(gpios[index].gpio, led_buff[1]);

	return 2;
}

static struct file_operations led_drv = {
	.owner = THIS_MODULE,
	.read = &led_read,
	.write = &led_write,
};

static int led_drv_init(void)
{
	int gpio = gpios[0].gpio;

	gpio_request(gpio, gpios[0].name);
	gpio_direction_output(gpio, 1);

	led_major = register_chrdev(0, "led_drv", &led_drv);
	led_class = class_create(THIS_MODULE, "led_class");
	device_create(led_class, NULL, MKDEV(led_major, 0), NULL, "led0");

	return 0;
}

static void led_drv_exit(void)
{
	int gpio = gpios[0].gpio;

	device_destroy(led_class, MKDEV(led_major, 0));
	class_destroy(led_class);
	unregister_chrdev(led_major, "led_drv");
	gpio_free(gpio);
}

MODULE_LICENSE("GPL");
module_init(led_drv_init);
module_exit(led_drv_exit);

