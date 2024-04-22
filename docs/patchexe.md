# Patching an Executable File
通过对游戏文件本身进行Patch
## Pathch ELF files
在Windows下编译简单的`Hello World`程序进行测试。

+ 可以通过`Cutter`对源文件进行修改。
+ 可以通过`Hex Editor`直接定位到字符串。

参考CSAPP 链接和虚拟地址章节。
ELF文件的修改不是那么直接，因为存在虚拟地址的映射。
ELF Header 中定义了文件到虚拟地址的映射。
使用objdump得到的是虚拟地址。
`objdump -x`查看header和各个段

使用`Rizin`修改数据段

## Patch UMD file (ISO Patch)
EBOOT.BIN -> BOOT.BIN

PATCH BOOT.BIN

Relink EBOOT.BIN to BOOT.bin using `UMDGEN`
