# Patching an existing PSP Game

label: Reverse Engineering?
> Language patch?

说白了，还是patch以下两个方面。

+ 可执行文件(ELF)
 + 数据段
 + 代码段
+ 资源文件
 + 图片等

针对这些需求有不同的patch方法，大致分类如下。

## Patch UMD file (ISO Patch)
### Patch Resource Files
通常来说，游戏文件中文字和图片主要储存在`SYSDIR`的文件中。而这些文件往往采取奇特的形式进行压缩。需要经验丰富者识别其文件结构，方能进行“解包”。对得到的文件进行Patch后重新封装。则主程序加载这些文件时能使用修改后的数据。
### Patch Executable files
往往对资源文件的打包还不够。
EBOOT.BIN -> BOOT.BIN
()
PATCH BOOT.BIN

Relink EBOOT.BIN to BOOT.bin using `UMDGEN`

在Windows下编译简单的`Hello World`程序进行测试。

+ 可以通过`Cutter`对源文件进行修改。
+ 可以通过`Hex Editor`直接定位到字符串。

## Load PRX at Runtime Using CFW
劫持动态链接库，监测运行状态
## load cheat code using CW Cheat (金手指)
本质上是内存修改器。
用于替换内存中数值/机器代码，或向内存中添加数据/机器代码。
在PPSSPP支持此种格式后得到推广。

CSAPP：Attack Lab

https://datacrystal.romhacking.net/wiki/CwCheat