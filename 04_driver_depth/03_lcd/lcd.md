# lcd驱动

## 驱动程序框架

驱动程序 = 程序框架 + 硬件驱动

lcd也绕不开创建字符设备，只不过在内核的fbmem.c帮我们实现了

- register_framebuffer
    1. do_register_framebuffer
        1. device_create，创建设备节点（/dev/fbx）
- fbmem_init()
    1. register_chrdev()，a. 主设备号29，b. 字符设备操作：绑定操作集 fb_fops（包含 read/write/mmap/ioctl 等方法）     
    2. class_create()，在 sysfs 中创建 graphics 类
- fbmem_exit()
    - class_destroy
    - unregister_chrdev
-  fb_fops
    1. fb_open
        1. iminor()，从inode获取次设备号
        2. get_fb_info()， 通过次设备号查找fb_info
        3. info->fbops->fb_open()，调用驱动的自定义open（如果存在）
    2. fb_read
        1. file_fb_info()，从file获取fb_info
        2. return info->fbops->fb_read()，优先调用用户定义的fb_read
        3. fb_memcpy_fromfb()，从framebuffer拷贝数据到内核缓存区
        4. copy_to_user()，复制到用户空间
    3. fb_write
        1. return info->fbops->fb_write()，优先调用用户定义的fb_write
        2. copy_from_user，从用户空间复制
        3. fb_memcpy_tofb，写入显存



