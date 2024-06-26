
# 从已有的PRX模块生成Stub Library

主要步骤：

1. 得到PRX文件的导出表
2. 用导出表生成Stub Library

## PSPSDK的库从哪里来？

> 2021 PSPHDC: uofw
>
> 2022 PSPHDC: Toolchain

事实上，我们目前为止链接的所有PSPSDK中内置库中的内核库几乎都是`Stub Libraries`。

在`pspsdk/src/kernel`中，我们只有`.h`头文件和`.S`存根文件（实际上是充满宏的汇编文件）。


历史上，人们设法从索尼提供的官方固件升级包中提取出许多系统级`prx`模块，接着进行如下操作：


1. 使用`prxtool`从`prx`模块提取得到导出表（`Export Table`,`.exp`文件）
`prxtool sample.prx -p`生成exports.exp
    >  **导出表(Export Table)**
    >
    > `prx`文件的导出表可以类比Windows PE文件（如DLL文件）中的导出表。
    >
    >导出表包含了一个模块显式向其他模块公开供其使用的符号列表。
    >
    >导出表的关键组成部分包括：
    >
    >+ 导出的符号： 可以被其他模块访问和使用的函数、变量或资源的名称和地址。
    >
    >+ 序数号码(`NID`)： 为每个导出的符号分配一个序数号码。序数号码提供了另一种引用导出符号的方式，特别是当名称没有被公开时。
    >
    >+ 地址或指针： 指示模块内导出函数或数据的位置的指针或地址。
    ```
    # Copyright (C) 2011, 2012 The uOFW team
    # See the file COPYING for copying permission.

    # Automatically exports file generated with prxtool
    PSP_BEGIN_EXPORTS

    PSP_EXPORT_START(syslib, 0x0000, 0x8000)
    PSP_EXPORT_FUNC_HASH(module_start)
    PSP_EXPORT_FUNC_HASH(module_reboot_phase)
    PSP_EXPORT_FUNC_HASH(module_reboot_before)
    PSP_EXPORT_VAR_HASH(module_info)
    PSP_EXPORT_VAR_HASH(module_sdk_version)
    PSP_EXPORT_END

    PSP_EXPORT_START(sceGe_driver, 0x0011, 0x0001)
    PSP_EXPORT_FUNC_NID(sceGePutBreakpoint, 0x05238809)
    ......
    PSP_EXPORT_END

    PSP_EXPORT_START(sceGe_user, 0x0011, 0x4001)
    PSP_EXPORT_FUNC_NID(sceGeListSync, 0x03444EB4)
    ......
    PSP_EXPORT_END

    PSP_END_EXPORTS
    ```
2. 利用导出表信息生成存根文件/导入表(`.S`文件)

    工具：`psp-build-exports`/`prxtool`
    
    命令：`psp-build-exports -k supervisor_exp.exp`
    
    格式：两种，`-k`和？

    例子：`pspsdk/src/ge/sceGe_user.S`(from GitHub)
    ```C
        .set noreorder

    #include "pspimport.s"

    #ifdef F_sceGe_user_0000
        IMPORT_START	"sceGe_user",0x40010000
    #endif
    #ifdef F_sceGe_user_0001
        //Module Name, NID, Function Name(Used only during linking)
        IMPORT_FUNC	"sceGe_user",0x1F6752AD,sceGeEdramGetSize
    #endif
    ......
    ```

    注释：[pspimport.s](https://github.com/pspdev/pspsdk/blob/master/src/base/pspimport.s)

3. 存根文件编译形成可重定位目标文件`.o`并进一步打包成存根库`.a`
    
    例子：`sceGe_user_0000.o` `sceGe_user_0001.o`... 
    -> `libpspge.a`

    ```makefile
    GE_OBJS = sceGe_user_0000.o sceGe_user_0001.o

    $(GE_OBJS): ge.S 
    psp-gcc $(CFLAGS) -DF_$* $< -c -o $@
    ```
    在运行时存根库在功能上被其所指的`prx`模块代替。


将自己的代码与存根库链接后，我们理论上已经可以借此调用其中的函数了，但导出的函数若不知其含义，显然无从使用；且导出的函数名均以`sceMgr_driver_949CAC22`这样`库名+NID`的形式命名，不利于开发使用。

2. 对这些模块进行逆向工程，得到其机器语言实现，通过对汇编代码的研究理解其使用方法，以此整理出描述函数接口的头文件并修正导出的函数名。

NID的计算方式为函数名作SHA256取高32位。可以通过暴力破解尝试反推函数名。

通过这种方法，得到包含头文件和存根库的整个PSPSDK开发环境。

目前PSPSDK中有一些库的头文件中函数名仍带有奇怪的字符串，这实际上就是直接从导出表中得到的函数的`NID`，由于彼时尚不理解其具体实现，没有办法为其取名。


.macro IMPORT_START module, flags_ver

	.set push
	.section .rodata.sceResident, "a"
	.word   0
__stub_modulestr_\module:
	.asciz  "\module"
	.align  2

	.section .lib.stub, "a", @progbits
	.global __stub_module_\module
__stub_module_\module:
	.word   __stub_modulestr_\module // Module Name String Addr
	.word   \flags_ver  // Flags
	.word   0x5
	.word   __executable_start  // 在psp-fixup-imports中重定位
	.word   __executable_start  // 在psp-fixup-imports中重定位

	.set pop
.endm


# Cooperating with different SDKs

`PSPSDK`是民间爱好者自发通过逆向工程研究得到的SDK。围绕着这套SDK，已经移植出多种库。`PSPSDK`随着PSP破解的发展不断迭代，从以前的`M33`格式到后来的格式。

目前，官方的SDK已经泄露在互联网上，通过在互联网档案馆搜寻不难得到。随着官方SDK的泄露，随之而来的是大量的官方文档，它们对于PSP的运作机理进行了很好的补充。作为初学者阅读这些文档有助于我们更好地使用`PSPSDK`。

事实上，现在`PSPSDK`的功能和配套软件在某些方面已经远远超过了官方SDK。但是`PSPSDK`少收录了部分系统库（系统调用）的函数，亦缺乏许多函数参数的解释。另外，官方SDK还收录了索尼开发的的部分第三方库。这些库能够使我们的程序中UI等的设计更接近当时PSP官方出品的程序。
