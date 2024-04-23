# Debug Tutorial
调试是开发过程中十分重要的环节。

通常来讲我们两种情况下会在想调试程序：
+ 开发过程
+ 逆向过程

针对这两种不同的需求，我们推荐如下两种Debug方法。
+ 实机Debug
+ 模拟器Debug

实际上主要是因为PPSSPP的限制，不能直接加载ELF文件，而且PSPDEV生成PRX时又自动strip了符号表，导致加载的程序完全没有符号信息。
对于逆向工程来讲，因为发行的游戏本来就已经移除了符号表，没有函数名什么的提示倒也无妨。但使用`PPSSPP`Debug自己写的程序时，不能显示对应的源文件和行号，甚至连函数名都不知道，就十分痛苦了。

> 刚才得知，PPSSPP可以导出和导入符号表，还可以与Ghida交互，进行静态分析
> 参见https://github.com/Bunkai9448/digipet_PSP/blob/main/RE_Guide.md#Text-File

实机Debug就使用pspsh与psp-gdb，逆向的时候使用PPSSPP就十分方便了。
## Debug Using `pspsh` & `psp-gdb`
使用实机Debug有很多好处

## Debug Using `PPSSPP`
> [《诡计对逻辑》汉化研究](https://pbteam.cn/posts/txl-hack/)
> https://datacrystal.romhacking.net/wiki/Blaze_Union/Tutorials
> https://github.com/Bunkai9448/digipet_PSP/blob/main/RE_Guide.md

PPSSPP自带的调试工具算很强大了。简要介绍一下它的功能。
+ 查看寄存器
+ 查看内存
+ 给系统调用打断点

具体用法可以参考链接。

几种内存地址的变换
+ psp的内存地址空间
+ Dump出的内存
+ ELF中的vmaddr
+ ELF的二进制文件

## Makefile Example (From RetroArch)
+ After `include`
```Makefile
debug:
    /snap/bin/ppsspp-emu.ppsspp-sdl EBOOT.BIN
```

> If you are using Ubuntu and install PPSSPP from snap.
> + Program Location: /snap/bin/ppsspp-emu.ppsspp-sdl
> + `PSP` Folder Location: ~/snap/ppsspp-emu/common/.config/ppsspp