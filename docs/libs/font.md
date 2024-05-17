
# PGF file
PPSSPP有PGF文件的解析实现。
## Manipulating PGF Files.
> A Commandline tool for manipulating PGF File
> >[PGFTool](https://github.com/tpunix/pgftool)
>
> A Windows Tool for manipulating PGF file
> >[PSP-Pixels](https://github.com/niuhuan/psp-pixels)
>
> An old and more general Locolization Tool in Chinese. 
> > [Firefly](https://github.com/IanusInferus/firefly/)
# libFont
PPSSPP有一个libFont的实现。

charCode is UCS2.
UCS2，可认为是UTF-16用二个字节来表示基本平面

UTF-16 编码表
Unicode 中的一个编码区段，编码从 U+0000 至 U+FFFF，也称基本多文种平面（Basic Multilingual Plane，BMP），或第零平面（Plane 0）。

Unicode 编码规定以下字符范围为控制字符，\U0000 - \U001F, \U007F, \U0080 - \U009F。

UCS-2 用 0x0000 - 0xFFFF 代表所有UTF-8的字符。 假设一个字符为16x16, 一个byte（8Bit）可以代表8个点, 32个byte就可以代表一个字, 2Mib刚好表示整个UCS-2字库。

PSP在使用的时候, 跟据UCS2编码可以直接算出偏移量, 并取出32个byte, 进行位运算, 打印出一个字符.
