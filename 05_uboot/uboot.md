
# uboot

cpu，ARM公司设计的ip内核，高速的核心处理单元，放在u-boot/arch/arm/cpu

board, 半导体公司设计的部分，i2c/uart等比较慢的外设，放在u-boot/board

整个代码的入口，u-boot/arch/arm/cpu/start.S

在哪里去找头文件
- u-boot/include
- u-boot/arch/arm/include

启动机制
 
1. iROM (Boot ROM) 阶段
- 芯片上电后，首先执行固化在内部 iROM 中的代码
- iROM 代码执行基本的初始化工作，包括配置系统时钟、看门狗定时器等
- iROM 代码根据预配置的启动顺序（例如 OM 引脚设置），从选定的外部存储器（如 NAND Flash、SD 卡等）中读取前 4KB 数据（即 BL1 阶段代码）

2. BL1 (1st Stage Bootloader) 阶段
- 读取到的 BL1 代码被加载到片内 SRAM（通常称为 Stepping Stone）中执行
- BL1 的主要任务是初始化系统主内存（DDR SDRAM） 以及其他运行完整 Bootloader 所需的关键外设

3. BL2 (2nd Stage Bootloader) 阶段
- 完成内存初始化后，BL1 从外部存储器中将 Bootloader 的剩余主体部分（即 BL2，如 U-Boot）加载到已初始化的 DDR SDRAM 中
- BL1 将程序计数器（PC）跳转至 DDR SDRAM 中的 BL2 入口地址，将控制权移交给 BL2 继续执行

4. 操作系统 (OS) 加载阶段：
- BL2（通常是 U-Boot）从外部存储器中将操作系统内核映像加载到 DDR SDRAM 中的预定地址
- BL2 最后跳转到操作系统内核的入口地址，将控制权完全移交给操作系统，启动过程完成
