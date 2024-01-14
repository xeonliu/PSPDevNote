# 我们要构建的是什么？
我们的目标是编写能在PSP上运行的软件（常被称为`PSP Module`），从应用上可分为自制游戏（`Homebrew`）和插件(`Plugin`)。

> 参考阅读
>
> PSP Modules, Exports, Imports and Patches https://uofw.github.io/upspd/docs/

在此之前，我们先了解一下PSP。

## PSP的正规使用方法
众所周知，PSP是索尼2004年推出的一款游戏机。其游戏通过UMD光盘发行。在运行官方固件的PSP上，PSP通过读取插入的UMD光盘运行游戏。PSP支持读取记忆棒，主要用于储存游戏存档数据等。

## 自定义固件（CFW）
PSP推出以后，各路大神争相破解PSP固件，利用各种漏洞推出了众多自定义固件。在自定义固件下，PSP可以运行储存在记忆棒中的UMD光盘镜像或者爱好者自己编写的`PSP Module`文件。

经过20年迭代，一般认为目前功能最完善的CFW为6.60PRO。互联网上有许多安装教程，不再赘述。

> 新近的`ARK-4` CFW也是一个不错的选择

本文所有示例程序均在6.60PRO固件下的PSP1000型号中测试通过。

## 模拟器（Emulator）
随着其他设备性能的提升，市面上也开始出现越来越多的PSP模拟器。其中最著名的当属PPSSPP。如果你没有实体的PSP，也可以通过模拟器来享受前人制作的精良游戏或测试自己开发的`PSP Module`。

## 文件格式

前文已经提到，我们的目标是编写`PSP Module`。我们有必要提及运行CFW的PSP可以运行的`PSP Module`程序的文件格式。

+ ELF
+ PRX

> A program that is loaded in memory is called a program module or simply a module. The PSP™ kernel is responsible for managing the modules in memory.
>
> The PSP™ kernel loader can handle two types of object files. One is a relocatable object file format unique to the PSP™ kernel called a PRX file, and the other is a normal ELF executable object file.

对于自制游戏来说，为了能让其在主界面（`XMB`）的游戏菜单中显示，需要将其封装为EBOOT.PBP

示例：我们假设你已经拥有一台配备CFW的PSP

> A typical Plugin
> ![Leda Plugin](https://www.gamebrew.org/images/2/23/Ledapsp2.png)

> A typical Homebrew
> ![Dinorun](https://www.gamebrew.org/images/7/70/Dinorunpsp.png)





