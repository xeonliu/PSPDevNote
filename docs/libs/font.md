
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

<<<<<<< HEAD
UCS-2 用 0x0000 - 0xFFFF 代表所有UTF-8的字符。 假设一个字符为16x16, 一个byte（8Bit）可以代表8个点, 32个byte就可以代表一个字, 2Mib刚好表示整个UCS-2字库。

PSP在使用的时候, 跟据UCS2编码可以直接算出偏移量, 并取出32个byte, 进行位运算, 打印出一个字符.
=======
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

`liquidzigong`?
`TPU`?

怪物猎人？
梦幻之星携带版2等？
`oldfont.prx`?

```
Name:    fontfuck
Attrib:  0000
Version: 1.1
GP:      00008EF0

Exports:
Export 0, Name syslib, Functions 1, Variables 1, flags 80000000
Export 1, Name sceLibFont, Functions 15, Variables 0, flags 00010000

Imports:
Import 0, Name sceLibFttt, Functions 27, Variables 0, flags 00090011
Import 1, Name IoFileMgrForUser, Functions 5, Variables 0, flags 40010000
Import 2, Name ModuleMgrForUser, Functions 2, Variables 0, flags 40010000
Import 3, Name StdioForUser, Functions 1, Variables 0, flags 40010000
Import 4, Name ThreadManForUser, Functions 4, Variables 0, flags 40010000
```

https://gist.github.com/TellowKrinkle/3414f704ba39d4dea5773df5a6f53f3c

new Module("sceLibFttt",
			new SCE(0x67f17ed7, "sceFontNewLib", 'x', "xx"),
			new SCE(0x574b6fbc, "sceFontDoneLib", 'i', "x"),
			new SCE(0x48293280, "sceFontSetResolution", 'i', "xff"),
			new SCE(0x27f6e642, "sceFontGetNumFontList", 'i', "xx"),
			new SCE(0xbc75d85b, "sceFontGetFontList", 'i', "xxi"),
			new SCE(0x099ef33c, "sceFontFindOptimumFont", 'i', "xxx"),
			new SCE(0x681e61a7, "sceFontFindFont", 'i', "xxx"),
			new SCE(0x2f67356a, "sceFontCalcMemorySize", 'i', ""),
			new SCE(0x5333322d, "sceFontGetFontInfoByIndexNumber", 'i', "xxx"),
			new SCE(0xa834319d, "sceFontOpen", 'x', "xxxx"),
			new SCE(0x57fcb733, "sceFontOpenUserFile", 'x', "xsxx"),
			new SCE(0xbb8e7fe6, "sceFontOpenUserMemory", 'x', "xxxx"),
			new SCE(0x3aea8cb6, "sceFontClose", 'i', "x"),
			new SCE(0x0da7535e, "sceFontGetFontInfo", 'i', "xx"),
			new SCE(0xdcc80c2f, "sceFontGetCharInfo", 'i', "xxx"),
			new SCE(0xaa3de7b5, "sceFontGetShadowInfo", 'i', "xxx"),
			new SCE(0x5c3e4a9e, "sceFontGetCharImageRect", 'i', "xxx"),
			new SCE(0x48b06520, "sceFontGetShadowImageRect", 'i', "xxx"),
			new SCE(0x980f4895, "sceFontGetCharGlyphImage", 'i', "xxx"),
			new SCE(0xca1e6945, "sceFontGetCharGlyphImage_Clip", 'i', "xxxiiii"),
			new SCE(0x74b21701, "sceFontPixelToPointH", 'f', "ifx"),
			new SCE(0xf8f0752e, "sceFontPixelToPointV", 'f', "ifx"),
			new SCE(0x472694cd, "sceFontPointToPixelH", 'f', "ifx"),
			new SCE(0x3c4b7e82, "sceFontPointToPixelV", 'f', "ifx"),
			new SCE(0xee232411, "sceFontSetAltCharacterCode", 'i', "xx"),
			new SCE(0x568be516, "sceFontGetShadowGlyphImage", 'i', "xxx"),
			new SCE(0x5dcf6858, "sceFontGetShadowGlyphImage_Clip", 'i', "xxxiiii"),
			new SCE(0x02d7f94b, "sceFontFlush", 'i', "x")
		),

Module("sceLibFont",
			new SCE(0x67f17ed7, "sceFontNewLib", 'x', "xx"),
			new SCE(0x574b6fbc, "sceFontDoneLib", 'i', "x"),
			new SCE(0x48293280, "sceFontSetResolution", 'i', "xff"),
			new SCE(0x27f6e642, "sceFontGetNumFontList", 'i', "xx"),
			new SCE(0xbc75d85b, "sceFontGetFontList", 'i', "xxi"),
			new SCE(0x099ef33c, "sceFontFindOptimumFont", 'i', "xxx"),
			new SCE(0x681e61a7, "sceFontFindFont", 'i', "xxx"),
			new SCE(0x2f67356a, "sceFontCalcMemorySize", 'i', ""),
			new SCE(0x5333322d, "sceFontGetFontInfoByIndexNumber", 'i', "xxx"),
			new SCE(0xa834319d, "sceFontOpen", 'x', "xxxx"),
			new SCE(0x57fcb733, "sceFontOpenUserFile", 'x', "xsxx"),
			new SCE(0xbb8e7fe6, "sceFontOpenUserMemory", 'x', "xxxx"),
			new SCE(0x3aea8cb6, "sceFontClose", 'i', "x"),
			new SCE(0x0da7535e, "sceFontGetFontInfo", 'i', "xx"),
			new SCE(0xdcc80c2f, "sceFontGetCharInfo", 'i', "xxx"),
			new SCE(0xaa3de7b5, "sceFontGetShadowInfo", 'i', "xxx"),
			new SCE(0x5c3e4a9e, "sceFontGetCharImageRect", 'i', "xxx"),
			new SCE(0x48b06520, "sceFontGetShadowImageRect", 'i', "xxx"),
			new SCE(0x980f4895, "sceFontGetCharGlyphImage", 'i', "xxx"),
			new SCE(0xca1e6945, "sceFontGetCharGlyphImage_Clip", 'i', "xxxiiii"),
			new SCE(0x74b21701, "sceFontPixelToPointH", 'f', "ifx"),
			new SCE(0xf8f0752e, "sceFontPixelToPointV", 'f', "ifx"),
			new SCE(0x472694cd, "sceFontPointToPixelH", 'f', "ifx"),
			new SCE(0x3c4b7e82, "sceFontPointToPixelV", 'f', "ifx"),
			new SCE(0xee232411, "sceFontSetAltCharacterCode", 'i', "xx"),
			new SCE(0x568be516, "sceFontGetShadowGlyphImage", 'i', "xxx"),
			new SCE(0x5dcf6858, "sceFontGetShadowGlyphImage_Clip", 'i', "xxxiiii"),
			new SCE(0x02d7f94b, "sceFontFlush", 'i', "x")
)
>>>>>>> 04bea76e94d934b878c995d594ce433b4f3be225
