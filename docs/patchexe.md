# Patching an Executable File
通过对游戏文件本身进行Patch
## Pathch ELF files
在Windows下编译简单的`Hello World`程序进行测试。

+ 可以通过`Cutter`对源文件进行修改。
+ 可以通过`Hex Editor`直接定位到字符串。

## Patch UMD file (ISO Patch)
EBOOT.BIN -> BOOT.BIN

PATCH BOOT.BIN

Relink EBOOT.BIN to BOOT.bin using `UMDGEN`
