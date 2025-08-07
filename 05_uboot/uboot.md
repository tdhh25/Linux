
## uboot

### lds

GNU LD手册：  
&emsp;https://sourceware.org/binutils/docs/ld/

### 脚本整体结构
```ld
/* 全局设置 */
OUTPUT_FORMAT(...)    // 定义输出文件格式
elf32-littlearm：ARM 32位小端
elf32-bigarm：ARM 32位大端
elf64-littleaarch64：ARM 64位小端
elf32-i386：x86 32位
elf64-x86-64：x86_64 64位
elf32-powerpc：PowerPC 32位
elf64-powerpc：PowerPC 64位
elf32-riscv：RISC-V 32位
elf64-risc：RISC-V 64位

OUTPUT_ARCH(...)      // 定义目标架构
ARM 32位：arm
ARM 64位 (AArch64)：aarch64
RISC-V 32位：riscv
RISC-V 64位：riscv:rv64
MIPS 32位小端：mipsel
MIPS 32位大端：mips
PowerPC 32位：powerpc:common
x86 32位：i386
x86_64 位：i386:x86-64
LoongArch 64位：loongarch

ENTRY(...)            // 定义程序入口点

/* 可选：内存区域定义 */
MEMORY {
    ROM (rx) : ORIGIN = 0x00000000, LENGTH = 256K
    RAM (rwx): ORIGIN = 0x80000000, LENGTH = 64M
}

/* 核心：段布局定义 */
SECTIONS
{
    /* 段1定义 */
    .text : { ... } > ROM
    
    /* 段2定义 */
    .data : { ... } > RAM AT> ROM
    
    /* 特殊段 */
    /DISCARD/ : { ... }
}
```
### 核心组件
1. 全局设置指令

|指令|作用|示例|
|---|---|---|
|OUTPUT_FORMAT|指定文件输出格式|OUTPUT_FORMAT("elf32-littlearm")|
|OUTPUT_ARCH|指定处理器架构|OUTPUT_ARCH(arm)|
|ENTRY|指定程序入口|ENTRY(_start)|

2. 内存区域定义  

    语法:<br> 
    &emsp;MEMORY {<br>
    &emsp;&emsp;<名称>(<属性>): ORIGIN = <起始地址>，LENGTH = <长度>  
    &emsp;}

    - 属性： r：可读 w：可写 x：可执行

    示例：
```shell
MEMORY {
    FLASH(rx): ORIGIN = 0x08000000，LENGTH = 512K
    SRAM(rwx): ORIGIN = 0x20000000，LENGTH = 128K
}
```

3. 段布局定义（SECTIONS核心内容）
    - 语法:<br>
    &emsp;<段名> [<地址>] : [AT(<加载地址>)]<br>
    &emsp;{<br>
    &emsp;&emsp;<内容><br>
    &emsp;} [> <内存区域>]<br>

    - 位置控制

    |语法|作用|示例|
    |---|---|---|
    |. = <值>;|设置当前位置|. = 0x87800000|
    |. += <值>;|当前位置偏移|. += 0x1000|
    |ALIGN(<对齐>)|地址对齐|. = ALIGN(4)|

    - 输入段选择器

        基础语法：
        &emsp;输入文件模式(段名)
        - 输入文件模式，可以是通配符 *（所有文件）、文件名（如 start.o）或带路径的文件名
        - 段名，目标文件中的段名称（如 .text、.data、.vectors 等）

    |模式|作用|示例|
    |---|---|---|
    |*(.text)|所有文件的.text段|合并所有.text|
    |start.o(.vectors)|特定文件的段|仅处理start.o的.vectors|
    |*(.text .rodata)|多段合并|同时包含.text和.rodata|
    |KEEP(*(.init))|防止优化移除|关键启动代码|

    - 符号定义  
    语法：  
    &emsp;<符号名> = <表达式>;  
    用途：  
    &emsp;- 标记段边界，__bss_start = .;  
    &emsp;- 计算长度，__data_len = __data_end - __data_start;

   - 特殊段处理
```ld
    /DISCARD/ : {
    *(.comment)     // 丢弃注释段
    *(.note.*)      // 丢弃所有note段
}
```

cpu，ARM公司设计的ip内核，高速的核心处理单元，放在u-boot/arch/arm/cpu

board, 半导体公司设计的部分，i2c/uart等比较慢的外设，放在u-boot/board

### 目录结构

链接脚本，放在u-boot/arch/arm/cpu/u-boot.lds

配置文件，configs目录

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
