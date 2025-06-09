# List of Formats that are already cracked

历史上，同一公司往往采取相同的格式。其中一些已经被破解。

+ CPK
    + CRIWARE
    + [CriPakTools](https://github.com/esperknight/CriPakTools)

## File System

许多游戏会将所有资源文件打包到一个文件之中，形成一个小小的用单个文件表示的文件系统。

这个文件中包含了资源文件的名称、大小、目录从属等关系。格式各有不同。

往往以文件本身和文件的索引构成。索引常包括名称、偏移量、大小等字段，可以使用`Imhex`等工具辅助逆向。

## Compression Method

在解包过程中往往会遇到压缩后的文件。

+ `zlib`
    + With Header
    + Without Header（Deflate）

> Defalte是结合了`LZ77`与哈夫曼编码的一种压缩算法

+ `LZ77`

## Image Format

+ `GIM`
    + 索尼官方位图格式