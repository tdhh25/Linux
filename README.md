# Linux

## GCC编译过程

1. 预处理（Preprocessing）
- 作用：处理源代码中的预处理指令（如 #include、#define、#ifdef 等），生成展开后的代码
 
- 操作：
    - 展开头文件（.h）：将 #include 替换为文件内容
    - 宏展开：将#define 定义的宏展开为实际内容
    - 条件编译：根据 #ifdef、#ifndef 保留或删除代码块
    - 删除注释

- 输出文件：.i 文件

- 命令：
```bash
gcc -E hello.c -o hello.i
```

2. 编译（Compilation）
- 作用：将预处理后的代码转换为汇编代码

- 操作：
    - 语法和语义分析
    - 生成中间代码并进行优化（如使用 -O2 优化选项）
    - 生成目标架构的汇编代码（如 x86 或 ARM）

- 输出文件：.s 文件

- 命令：
```bash
    gcc -S hello.i -o hello.s
    #或者直接从源文件编译
    gcc -S hello.c -o hello.s
```

3. 汇编（Assembly）
- 作用：将汇编代码转换为机器码（二进制目标文件）

- 操作：
    - 生成可重定位的机器指令
    - 生成符号表（记录函数和变量地址）
    - 输出文件：.o/.obj 文件

- 命令：
```bash
    gcc -c hello.s -o hello.o
    # 或直接从源文件生成目标文件
    gcc -c hello.c -o hello.o
```

4. 链接（Linking）
- 作用：合并多个目标文件和库文件，生成可执行文件

- 操作：
    - 静态链接：将静态库（.a 文件）代码复制到可执行文件中
    - 动态链接：记录动态库（.so 文件）的引用，运行时加载
    - 符号解析：解决函数和变量的地址引用

- 输出文件：可执行文件
- 命令：
```bash
gcc hello.o -o hello
# 直接编译并链接多个文件
gcc main.c utils.c -o app
```


