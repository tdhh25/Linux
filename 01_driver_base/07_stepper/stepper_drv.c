#include <linux/module.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/gpio.h>

struct gpios_desc {
	int gpio;
	int irq;
	char* name;
};pinctrl_desc

static int current_pos;
static int stepper_major;
static int stepper_buff[2];
static int stepper_state[4] = {
	1,4,2,8
};
static struct class* stepper_class;
static struct gpios_desc stepper_gpios[4] = {
	{115, 0, "stepper_gpio0"},
	{116, 0, "stepper_gpio1"},
	{117, 0, "stepper_gpio2"},
	{118, 0, "stepper_gpio3"},
};

static void stepper_set_pinctrl(int stepper_state, int stepper_ctrl)
{
	int i = 0, gpio = 0, size = 0;

	size = sizeof(stepper_gpios) / sizeof(stepper_gpios[0]);
	if(stepper_ctrl >= 2)
		return;

	if(stepper_ctrl)
	{
		for(i = 0;i < size;i++)
		{
			gpio = stepper_gpios[i].gpio;
			if(stepper_state & (1 << i))
				gpio_set_value(gpio, 1);
		}
	}
	else
	{
		for(i = 0;i < size;i++)
		{
			gpio = stepper_gpios[i].gpio;
			gpio_set_value(gpio, 0);
		}
	}
}


/*
 * buff[0]: 步进次数
 * buff[1]: 步进速度
 */
static ssize_t stepper_write (struct file *file, const char __user *buff, size_t size, loff_t *offset)
{
	unsigned long ret;

	if(8 != size)
		return -EINVAL;

	ret = copy_from_user(stepper_buff, buff, size);

	if(buff[0] > 0)
	{
		stepper_set_pinctrl(stepper_state[current_pos], 1);
		mdelay(buff[1]);
		current_pos++;
		if(4 == current_pos)
			current_pos = 0;
	}
	else
	{
		stepper_set_pinctrl(stepper_state[current_pos], 1);
		mdelay(buff[1]);
		current_pos--;
		if(-1 == current_pos)
			current_pos = 3;
	}
	stepper_set_pinctrl(0, 0);

	return 8;
}

static struct file_operations stepper_drv = {
	.owner = THIS_MODULE,
	.write = &stepper_write,
};

static int stepper_drv_init(void)
{
	stepper_major = register_chrdev(0, "stepperr", &stepper_drv);
	stepper_class = class_create(THIS_MODULE, "stepper_class");
	device_create(stepper_class, NULL, MKDEV(stepper_major, 0), NULL, "stepper");

	return 0;
}

static void stepper_drv_exit(void)
{
	device_destroy(stepper_class, MKDEV(stepper_major, 0));
	class_destroy(stepper_class);
	unregister_chrdev(stepper_major, "stepper_motor");
}

MODULE_LICENSE("GPL");
module_init(stepper_drv_init);
module_exit(stepper_drv_exit);

