
## 设备树

### 为什么需要设备树？

### 什么是设备树？
设备树是一种描述硬件的数据结构

### 设备树的组成

设备树 = 节点(node) + 属性(property)

- 节点可以包含子节点
- 属性是成对出现的名称和值

设备树可描述的信息包括：
- cpu的数量和类别
- 内存基地址和大小
- 总线和桥
- 中断控制器和中断使用情况
- GPIO控制器和GPIO使用情况
- 时钟控制器和时钟使用情况

Bootloader会将设备树传递给内核，内核将设备树展开出Linux内核中的platform_device、i2c_client、spi_device等设备，
而这些设备用到的内存、IRQ等资源，也被传递给了内核，内核会将这些资源绑定给展开的相应的设备

### DTS、DTB和DTC

DTS
- ASCII文本格式的设备树描述
- 在ARM Linux中，一个.dts文件对应一个ARM的设备，放置在内核的arch/arm/boot/dts/中
- Soc公用的部分或者多个设备共同的部分被提炼为.dtsi
- .dtsi也可以包含其他的.dtsi

device_tree.dts的（1）描述了.dts文件的模板

device_tree.dts的（2）描述了参考硬件的.dts文件


DTC
- 将.dts编译为.dtb的工具
- DTC的源代码位于内核的scripts/dtc
