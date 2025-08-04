
# uboot

cpu，ARM公司设计的ip内核，高速的核心处理单元，放在u-boot/arch/arm/cpu

board, 半导体公司设计的部分，i2c/uart等比较慢的外设，放在u-boot/board

整个代码的入口，u-boot/arch/arm/cpu/start.S

在哪里去找头文件
- u-boot/include
- u-boot/arch/arm/include

### 启动机制
6410启动机制
1. iROM (Boot ROM) 阶段
- 芯片上电后，首先执行固化在内部 iROM 中的代码
- iROM 代码执行基本的初始化工作，包括配置系统时钟、看门狗定时器等
- iROM 代码根据预配置的启动顺序（例如 OM 引脚设置），从选定的外部存储器（如 NAND Flash、SD 卡等）中读取前 4KB 数据（即 BL1 阶段代码）

1. BL1 (1st Stage Bootloader) 阶段
- 读取到的 BL1 代码被加载到片内 SRAM（通常称为 Stepping Stone）去执行，代码里自己会判断是在片内SRAM还是系统主内存（DDR SDRAM），
如果在静态SRAM，就会初始化系统主内存以及其他运行完整 Bootloader 所需的关键外设

1. BL2 (2nd Stage Bootloader) 阶段
- 完成内存初始化后，BL1 从外部存储器中将 整个Bootloader加载到已初始化的 DDR SDRAM 中
- 跳转到u-boot的入口开始运行，判断自己在片内SRAM还是系统主内存
- 如果在系统主内存中，直接跳到4K以后的内容，开始运行BL2

1. 操作系统 (OS) 加载阶段：
- BL2（通常是 U-Boot）从外部存储器中将操作系统内核映像加载到 DDR SDRAM 中的预定地址
- BL2 最后跳转到操作系统内核的入口地址，将控制权完全移交给操作系统，启动过程完成

V210启动机制
1. iROM (Boot ROM) 阶段
- 芯片上电后，首先执行固化在内部 iROM 中的代码
- iROM 代码执行基本的初始化工作，包括配置系统时钟、看门狗定时器等
- iROM 代码根据预配置的启动顺序（例如 OM 引脚设置），从选定的外部存储器（如 NAND Flash、SD 卡等）中读取前 16KB 数据（uboot_spl.bin）

1. BL1 (1st Stage Bootloader) 阶段
- 读取到的 BL1 代码被加载到片内 SRAM（通常称为 Stepping Stone）去执行，绕开片内RAM的BL2，直接配置系统主内存，再把uboot.bin加载到动态DDR内存

1. BL2 (2nd Stage Bootloader) 阶段
- 跳转到uboot主体（uboot.bin）的入口开始运行

1. 操作系统 (OS) 加载阶段：
- BL2 最后跳转到操作系统内核的入口地址，将控制权完全移交给操作系统，启动过程完成

### uboot命令
|命令|用法|描述|示例|示例说明|
|---|---|---|---|---|
| bdinfo | bdinfo | 显示开发板硬件信息 | bdinfo | 显示内存布局、时钟等板级信息 |
| printenv | printenv [变量名] | 打印环境变量 | printenv bootcmd | 显示 bootcmd 环境变量的值 |
| setenv | setenv <变量名> <值> | 设置环境变量 | setenv ipaddr 192.168.1.10 | 设置 ipaddr=192.168.1.10 |
| saveenv | saveenv | 保存环境变量到存储|saveenv | 将变量写入 Flash/EEPROM |
| md | md[.b/.w/.l] <地址> [长度] | 显示内存内容|md.w 0x80000000 10 | 显示 16 个 word (4字节) 数据 |
| nm | nm[.b/.w/.l] <地址> | 交互式修改内存（固定地址）| nm.l 0x80000000 | 修改地址 0x80000000 的 32 位数据 |
| mm | mm[.b/.w/.l] <起始地址> |交互式修改内存（地址自增）| mm.w 0x80000000 | 修改内存，地址自动增加|
| mw | mw[.b/.w/.l] <地址> <值> [长度] | 填充内存区域 | mw.l 0x80000000 0xdeadbeef 10 | 填充 10 个 32 位值 |
| cp | cp[.b/.w/.l] <源地址> <目标地址> <长度> | 内存复制 | cp.b 0x82000000 0x83000000 0x1000 | 复制 4KB (4096 字节) 数据 |
| cmp | cmp[.b/.w/.l] <地址1> <地址2> <长度> | 内存比较 |cmp.l 0x80000000 0x81000000 100 | 比较 100 个 32 位数据 |
