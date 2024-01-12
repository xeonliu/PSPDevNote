# PSPDEV Directory Structure
什么是SDK？PSP开发的工具链是如何构成的？
> 推荐观看：
>
>  【【技术杂谈】C 编译体系】 https://www.bilibili.com/video/BV1J14y1D7Sw
> 
> 2022 PSP Homebrew Developer Conference: PSP Toolchain
```
pspdev
├── bin
├── etc
├── include
├── lib
├── libexec
├── psp
├── share
└── var
```

## `bin`
```
bin
├── PrxEncrypter
├── bin2c
├── bin2o
├── bin2s
├── ebootsign
├── mksfo
├── mksfoex
├── pack-pbp
├── psp-addr2line
├── psp-ar
├── psp-as
├── psp-build-exports
├── psp-c++
├── psp-c++filt
├── psp-cmake
├── psp-config
├── psp-cpp
├── psp-elfedit
├── psp-fixup-imports
├── psp-g++
├── psp-gcc
├── psp-gcc-11.2.0
├── psp-gcc-ar
├── psp-gcc-nm
├── psp-gcc-ranlib
├── psp-gcov
├── psp-gcov-dump
├── psp-gcov-tool
├── psp-gdb
├── psp-gdb-add-index
├── psp-ld
├── psp-ld.bfd
├── psp-lto-dump
├── psp-makepkg
├── psp-nm
├── psp-objcopy
├── psp-objdump
├── psp-pacman
├── psp-pkg-config
├── psp-pkgconf -> psp-pkg-config
├── psp-prxgen
├── psp-ranlib
├── psp-readelf
├── psp-run
├── psp-size
├── psp-strings
├── psp-strip
├── pspsh
├── unpack-pbp
└── usbhostfs_pc
```
这个目录下储存着PSPDev中所有编译好后可供运行的二进制可执行文件。

其中大部分是与GNU相关的编译套件和调试工具：
+ GCC Compiler
+ GNU Binutils
    + ld - the GNU linker.
    + as - the GNU assembler.
    + addr2line - Converts addresses into filenames and line numbers.
    + ar - A utility for creating, modifying and extracting from archives.
    + c++filt - Filter to demangle encoded C++ symbols.
    + elfedit - Allows alteration of ELF format files.
    + nm - Lists symbols from object files.
    + objcopy - Copies and translates object files.
    + objdump - Displays information from object files.
    + ranlib - Generates an index to the contents of an archive.
    + readelf - Displays information from any ELF format object file.
    + size - Lists the section sizes of an object or archive file.
    + strings - Lists printable strings from files.
    + strip - Discards symbols.
+ GDB

其他的大多为满足PSP平台特定需求的工具程序
+ 生成配置文件
    + mksfo
    + mksfoex
+ 加密
    + PrxEncrypter
    + ebootsign
+ 打包 / 解包
    + pack-pbp
    + unpack-pbp
+ 调试
    + usbhostfs_pc
    + pspsh

还有一些杂七杂八的小工具
+ 嵌入资源文件
    + bin2c/bin2o/bin2s

下面选取其中较为重要的进行讲解。

### bin2c/bin2o/bin2s
功能简介：这些软件分别用于将任意二进制文件转换为C源文件、可重定位目标文件、汇编代码文件。

解决痛点：在应用开发时往往需要引用外部资源文件（如图片、音频等），如果程序运行时直接从外部储存器中加载这些文件，那么
+ 编写程序时需要考虑绝对路径等问题；
+ 在发行游戏时需要将可执行文件与资源文件一起拷贝到PSP中；
+ 运行时程序需要即时从外部储存器中读取资源文件，速度受限。

具体说明：将二进制资源文件所有字节转化为C中`char`类型数组，通过编译链接将其嵌入最终生成的可执行文件中。程序运行时，数据直接加载到内存中供程序访问。

协同交互：在其他源文件中使用`fmemopen`创建内存流对内存中储存的该数组加以访问。

使用方法：


### GNU Binutils

14. objdump 二进制文件分析
objdump工具用来显示二进制文件的信息，就是以一种可阅读的格式让你更多地了解二进制文件可能带有的附加信息。

14.1. 常用参数说明
-f 显示文件头信息
-D 反汇编所有section (-d反汇编特定section)
-h 显示目标文件各个section的头部摘要信息
-x 显示所有可用的头信息，包括符号表、重定位入口。-x 等价于 -a -f -h -r -t 同时指定。
-i 显示对于 -b 或者 -m 选项可用的架构和目标格式列表。
-r 显示文件的重定位入口。如果和-d或者-D一起使用，重定位部分以反汇编后的格式显示出来。
-R 显示文件的动态重定位入口，仅仅对于动态目标文件有意义，比如某些共享库。
-S 尽可能反汇编出源代码，尤其当编译的时候指定了-g这种调试参数时，效果比较明显。隐含了-d参数。
-t 显示文件的符号表入口。类似于nm -s提供的信息

[引用](https://linuxtools-rst.readthedocs.io/zh-cn/latest/tool/objdump.html)