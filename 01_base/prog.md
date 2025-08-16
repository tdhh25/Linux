## 网络编程

## 系统编程
```c
/*
 * 作用：
      将格式化数据写入字符串
 * 参数说明：
   - str	   指向字符数组的指针
   - format	格式化字符串，包含普通字符和格式说明符（如 %d, %s, %.2f 等）
   - ...	   可变参数列表，按顺序匹配 format 中的格式说明符
 * 返回值：
   - 成功：返回写入 str 的字符数量（不包括结尾的 \0）
   - 失败：返回负数
 */
```
__int sprintf(char *str, const char *format, ...)__

```c
/*
 * 作用：
      在堆上分配一块指定大小的内存空间
 * 参数说明：
    - size：分配内存的大小
 * 返回值：
    - 分配失败（如内存不足），返回 NULL
    - 分配成功，返回指针指向该内存的地址
 */
```
__void* malloc(size_t size)__

```c
/*
 * 作用：
      用于释放动态分配的内存
 * 参数说明：
   - ptr 指向先前由内存分配函数分配的内存块的指针
 */
```
__void free(void *ptr);__

```c
/*
 * 作用：
      将指定内存区域的前 num 个字节设置为 value
 * 参数说明：
    - ptr：     目标内存地址
    - value：   填充值
    - num：     填充的字节数
 * 返回值：
    指向目标内存区域（ptr）的指针
 */
```
__void* memset(void* ptr, int value, size_t num)__

```c
/*
 * 作用：
      比较字符串
 * 参数说明：
    - str1：指向第一个要比较的字符串的指针
    - str2：指向第二个要比较的字符串的指针
 * 返回值
    - < 0   str1 在字典序上小于 str2
    - 0：   str1 和 str2 完全相等
    - > 0:  str1 在字典序上大于 str2
 */
```
__int strcmp(const char *str1, const char *str2)__

```c
/*
 * 作用：
      用于打开文件
 * 参数说明：
    - filename：要打开的文件的路径和名称
    - mode：文件打开模式
        - "r"                   只读方式打开文本文件（文件必须存在）
        - "w"	                只写方式打开文本文件（存在则清空，不存在则创建）
        - "a"	                追加方式打开文本文件（写入数据追加到文件末尾）
        - "r+"	                读写方式打开文本文件（文件必须存在）
        - "w+"	                读写方式打开文本文件（存在则清空，不存在则创建）
        - "a+"	                读写方式打开文本文件（写入数据追加到文件末尾）
        - "rb", "wb", "ab"	    二进制文件版本的上述模式
        - "rb+", "wb+", "ab+"   二进制文件版本的读写模式
 * 返回值
    - 成功：返回指向文件的 FILE 指针
    - 失败：返回 NULL，并设置 errno 来指示错误
 */
```
__FILE *fopen(const char *filename, const char *mode)__

```c
/*
 * 作用：
      关闭已打开的文件，释放资源
 * 参数说明：
    - stream：文件指针
 * 返回值
    - 成功返回 0
    - 失败返回 EOF（通常是 -1）
 */
```
__int fclose(FILE* stream);__

```c
/*
 * 作用：
      将内存中的原始二进制数据写入文件流
 * 参数说明：
   - ptr    指向待写入数据的指针
   - size	单个元素的字节大小
   - nmemb	要写入的元素数量
   - stream 文件指针
 * 返回值
   - 成功：实际写入的元素个数
   - 失败：< nmemb 或 0
 */
```
__size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)__

```c
/*
 * 作用：
      用于从 文件流（FILE*） 中读取数据到内存缓冲区
 * 参数说明：
    - ptr       存储读取数据的内存缓冲区
    - size      每个数据项的字节大小
    - count     要读取的数据项数量
    - stream    文件指针
 * 返回值
    - 成功：返回 实际读取的完整数据项数量（≤ count）。
    - 失败/EOF：如果读取失败或到达文件末尾（EOF），返回值可能小于 count，甚至为 0
 */
```
__size_t fread(void *ptr, size_t size, size_t count, FILE *stream)__

```c
/*
 * 作用：
      重定位文件指针到指定位置
 * 参数说明：
    - stream：文件指针
    - offset：偏移
    - whence：基准位置
        - SEEK_SET（文件开头）
        - SEEK_CUR（当前位置）
        - SEEK_END（文件末尾）
 * 返回值
    - 成功：返回 0
    - 失败：返回非零值
 */
```
__int fseek(FILE* stream, long offset, int whence)__

```c
/*
 * 作用：
      获取当前文件指针的位置
 * 参数说明：
    - stream：文件指针
 * 返回值：
    - 成功：当前文件位置
    - 失败：-1L
 */
```
__long ftell(FILE* stream)__

