#include <linux/module.h>
#include <linux/fb.h>
#include <linux/dma-mapping.h>
#include <linux/platform_device.h>

static struct fb_info* my_fbinfo;
static struct fb_ops myfb_ops = {
	.owner		= THIS_MODULE,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
};
static struct gpio_desc* bl_gpio;

static int my_lcdprobe(struct platform_device *pdev)
{
	dma_addr_t phy_addr = 0;
	struct clk * pix_clk = NULL;
	struct clk * axi_clk = NULL;

	/* 设置背光 */
	bl_gpio = gpiod_get(&pdev->dev, "backlight", 0);
	gpiod_direction_output(bl_gpio, 1);
	gpiod_set_value(bl_gpio, 1);

	/* 配置时钟 */
	pix_clk = devm_clk_get(&pdev->dev, "pix");
	axi_clk = devm_clk_get(&pdev->dev, "axi");
	clk_set_rate(pix_clk, 50000000);
	clk_prepare_enable(pix_clk);
	clk_prepare_enable(axi_clk);

	/* 分配fb_info */
	my_fbinfo = framebuffer_alloc(0, NULL);
	
	/* 设置fb_info */
	/* a. 分辨率，颜色 */
	my_fbinfo->var.xres = 1024;
	my_fbinfo->var.yres = 600;
	my_fbinfo->var.bits_per_pixel = 16;
	my_fbinfo->var.red.length = 5;
	my_fbinfo->var.red.offset = 11;
	my_fbinfo->var.green.length = 6;
	my_fbinfo->var.green.offset = 5;
	my_fbinfo->var.blue.length = 5;
	my_fbinfo->var.blue.offset = 0;

	/* b. 长度，虚拟地址，物理地址等*/
	my_fbinfo->fix.smem_len = my_fbinfo->var.xres * my_fbinfo->var.yres * my_fbinfo->var.bits_per_pixel / 8;
	if(24 == my_fbinfo->var.bits_per_pixel)
			my_fbinfo->fix.smem_len = my_fbinfo->var.xres * my_fbinfo->var.yres * 4;
	my_fbinfo->screen_base = dma_alloc_wc(NULL, my_fbinfo->fix.smem_len, &phy_addr, GFP_KERNEL);
	my_fbinfo->fix.smem_start = phy_addr;
	my_fbinfo->fix.type = FB_TYPE_PACKED_PIXELS;
	my_fbinfo->fix.visual = FB_VISUAL_TRUECOLOR;

	/* fbops */
	my_fbinfo->fbops = &myfb_ops;

	/* 注册fb_info */
	register_framebuffer(my_fbinfo);

	/* 硬件操作 */

}

static int my_lcdremove(struct platform_device *pdev)
{
	unregister_framebuffer(my_fbinfo);
	framebuffer_release(my_fbinfo);

}

static struct of_device_id my_lcdmatch[] = {
	{compatible = "100ask,lcd",},
	{}
};


static struct platform_driver my_lcddriver = {
	.probe = my_lcdprobe,
	.remove = my_lcdremove,
	.driver = {
		.name = "lcd_driver",
		.of_match_table = my_lcdmatch,
	},
};

static int lcd_drv_init(void)
{
	platform_driver_register(&my_lcddriver);
} 

static void lcd_drv_exit(void)
{
	platform_driver_unregister(&my_lcddriver);
}

MODULE_LICENSE("GPL");
module_init(lcd_drv_init);
module_exit(lcd_drv_exit);

