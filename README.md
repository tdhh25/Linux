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

## GCC常用选项
1. 基础编译选项

|选项|说明|
|:---|:---|
|-o <文件名>|指定输出文件名（默认 a.out）|
|-c|只编译不链接，生成 .o 目标文件|
|-E|仅预处理，输出到标准输出或指定文件（.i）|
|-S|生成汇编代码（.s 文件）|
|-v|显示编译详细过程（查看实际调用的子命令）|

- 命令
```bash
    gcc -c main.c -o main.o    # 生成目标文件
    gcc main.o -o app          # 链接生成可执行文件
```

2. 优化选项

|选项|说明|
|:---|:---|
|-O0|关闭优化（默认，适合调试）|
|-O1/-O|基础优化（平衡速度和体积）|
|-O2|深度优化（推荐发布版本使用）|
|-O3|激进优化（可能增加代码体积）|
|-Os|优化代码体积|
|-march=native|针对当前机器的 CPU 架构优化（如 x86-64）|

命令：
```bash
    gcc -O2 main.c -o app    # 使用 O2 优化级别编译
```

3. 调试选项

|选项|说明|
|:---|:---|
|-g|生成调试信息（GDB 使用）|
|-ggdb|生成更详细的 GDB 专用调试信息|
|-DDEBUG|定义宏 DEBUG（等价代码中的 #define DEBUG）|
|-UNDEBUG|取消宏定义|

命令：
```bash
    gcc -g -DDEBUG main.c -o app    # 支持调试并启用 DEBUG 宏
```

4. 头文件和库路径

|选项|说明|
|:---|:---|
|-I <路径>|指定头文件搜索路径（如 -I/usr/local/include）|
|-L <路径>|指定库文件搜索路径（如 -L/usr/local/lib）|
|-l <库名>|链接指定库（如 -lm 链接数学库 libm.so）|

命令：
```bash
    gcc main.c -I./include -L./lib -lmylib -o app
```

5. 警告选项

|选项|说明|
|:---|:---|
|-Wall|启用所有常见警告（推荐必加）|
|-Wextra|启用额外警告（比 -Wall 更严格）|
|-Werror|将警告视为错误（强制修复警告）|
|-w|关闭所有警告|
|-Wno-<警告名>|禁用特定警告（如 -Wno-unused-variable）|

命令：
```bash
    gcc -Wall -Wextra -Werror main.c -o app    # 严格模式
```

6. 链接选项

|选项|说明|
|:---|:---|
|-static|强制静态链接（所有库静态编译）|
|-shared|生成动态库（.so 或 .dll）|
|-fPIC|生成位置无关代码（动态库必需）|
|-pthread|链接多线程库并启用线程支持|

命令：
```bash
    gcc -shared -fPIC lib.c -o libmylib.so    # 生成动态库
    gcc main.c -static -o app_static          # 静态链接
```

7. 语言标准选项

|选项|说明|
|:---|:---|
|-std=<标准>|指定 C/C++ 标准（如 -std=c11、-std=c++17）|
|-ansi|等同于 -std=c89|

命令：
```bash
    gcc -std=c11 main.c -o app    # 使用 C11 标准编译
```

8. 其他常用选项

|选项|说明|
|:---|:---|
|-MMD|生成依赖关系文件（.d），用于 Makefile 自动化|
|-save-temps|保留所有中间文件（.i, .s, .o）|
|-pipe|使用管道替代临时文件（加快编译速度）|
|-nostdlib|不链接标准库（手动指定入口函数时使用）|

命令：
```bash
    gcc -save-temps main.c -o app    # 保留预处理、汇编等中间文件
```

## 为什么需要Makefile

## Makefile的规则
