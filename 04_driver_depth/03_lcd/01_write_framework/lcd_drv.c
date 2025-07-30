#include <linux/module.h>
#include <linux/fb.h>
#include <linux/dma-mapping.h>

static struct fb_info* my_fbinfo;
static struct fb_ops myfb_ops = {
	.owner		= THIS_MODULE,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
};

static int lcd_drv_init(void)
{
	dma_addr_t phy_addr;

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

static void lcd_drv_exit(void)
{
	unregister_framebuffer(my_fbinfo);
	framebuffer_release(my_fbinfo);
}

MODULE_LICENSE("GPL");
module_init(lcd_drv_init);
module_exit(lcd_drv_exit);

