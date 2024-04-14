# Patching an existing PSP Game

label: Reverse Engineering?
> Language patch?

## Pathch ELF files
在Windows下编译简单的`Hello World`程序进行测试。

+ 可以通过`Cutter`对源文件进行修改。
+ 可以通过`Hex Editor`直接定位到字符串。

## Patch UMD file (ISO Patch)
EBOOT.BIN -> BOOT.BIN

PATCH BOOT.BIN

Relink EBOOT.BIN to BOOT.bin using `UMDGEN`

## Load a prx at runtime using CFW

## load cheat code using CW Cheat (金手指)
本质上是内存修改器。
用于替换内存中数值/机器代码，或向内存中添加数据/机器代码。
在PPSSPP支持此种格式后得到推广。

CSAPP：Attack Lab

https://datacrystal.romhacking.net/wiki/CwCheat