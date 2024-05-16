
# PGF file
PPSSPP有PGF文件的解析实现。
# libFont
PPSSPP有一个libFont的实现。

charCode is UCS2.
UCS2，可认为是UTF-16用二个字节来表示基本平面

UTF-16 编码表
Unicode 中的一个编码区段，编码从 U+0000 至 U+FFFF，也称基本多文种平面（Basic Multilingual Plane，BMP），或第零平面（Plane 0）。

Unicode 编码规定以下字符范围为控制字符，\U0000 - \U001F, \U007F, \U0080 - \U009F。

# PGF

26.9  PGF

The PSP font format (.PGF files) is a bitmap based font format. Each letter (as well as its shadow) is a single, 4bpp bitmap, saved in the font file in a RLE compressed form. The bitmaps are encoded using either vertical or horizontal rows, depending on a certain 2-bit field in character metrics. Every [character, shadow] bitmap pair is preceded by a character metrics record. For Latin fonts the length of this record appears to be 12 bytes (with an optional 7-byte extension), for other families it's different. It's not known at this time what is the determinant of the record length. The metrics record contains the following fields:
14-bit offset of the shadow header record
7-bit width
7-bit height
7-bit signed horizontal adjustment
7-bit ascender
2-bit transposition (1 - horizontal rows, 2 - vertical rows)
1-bit modified record field (adds a 7-byte extension to the 12-byte header for ltn0.pgf)
46 bits of unknown data
5-bit horizontal advance
To find the character metrics one has to read the main pointer table. The table is constructed of N-bit pointers, where N is found in the file header at offset 0x1C. The number of pointers (and characters) can be found in the file header at offset 0x14. It is not known yet how to locate the main pointer table. The RLE compression works on 4-bit nibbles (the low nibble of a byte is considered to precede the high nibble in the stream). There are two sequences defined for this RLE:
a nibble N<8: take next nibble and replicate N+1 times into the output stream
a nibble N>7: take next 16-N nibbles and copy directly into the output stream

上面的文章好像是针对拉丁字符的，中文字符感觉要参考一下国内的程序，或者PPSSPP。