# PSPDEV Directory Structure
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
这个目录下储存着PSPDev中所有编译好后可供运行的二进制可执行文件。可以看到其中许多都属于GNU的编译套件。binutils

### bin2c/bin2o/bin2s
功能简介：这些软件分别用于将任意二进制文件转换为C源文件、可重定位目标文件、汇编代码文件。

解决痛点：在应用开发时往往需要引用外部资源文件（如图片、音频等），如果程序运行时直接从外部储存器中加载这些文件，那么
+ 编写程序时需要考虑相对路径等问题；
+ 在发行游戏时需要将可执行文件与资源文件一起拷贝到PSP中；
+ 运行时程序需要即时从外部储存器中读取资源文件，速度受限。
具体说明：将二进制资源文件所有字节转化为C中`char`类型数组，通过编译链接将其嵌入最终生成的可执行文件中。程序运行时，数据直接加载到内存中供程序访问。

协同交互：在其他源文件中使用`fmemopen`创建内存流对内存中储存的该数组加以访问。

使用方法：


### GNU Toolchain