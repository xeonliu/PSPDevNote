
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

font_fuck library 还不止一种，有许多变种，但是大体上应该是一致的。

29个
sceFontisElement?


23:25:362 user_main    D[SCEFONT]: HLE\sceFont.cpp:1333 sceFontGetCharInfo(08c4c05c, 27700, 09ff72f0)
23:25:362 user_main    D[SCEFONT]: HLE\sceFont.cpp:1434 sceFontGetCharGlyphImage(8c4c05c, 6c34, 9ff72d0)
23:25:362 user_main    D[SCEFONT]: HLE\sceFont.cpp:1333 sceFontGetCharInfo(08c4c05c, 28304, 09ff72f0)
23:25:362 user_main    D[SCEFONT]: HLE\sceFont.cpp:1434 sceFontGetCharGlyphImage(8c4c05c, 6e90, 9ff72d0)
23:25:362 user_main    D[SCEFONT]: HLE\sceFont.cpp:1333 sceFontGetCharInfo(08c4c05c, 21551, 09ff72f0)
23:25:362 user_main    D[SCEFONT]: HLE\sceFont.cpp:1434 sceFontGetCharGlyphImage(8c4c05c, 542f, 9ff72d0)
23:25:362 user_main    D[SCEFONT]: HLE\sceFont.cpp:1333 sceFontGetCharInfo(08c4c05c, 21160, 09ff72f0)
23:25:362 user_main    D[SCEFONT]: HLE\sceFont.cpp:1434 sceFontGetCharGlyphImage(8c4c05c, 52a8, 9ff72d0)

0x9480

```cpp
undefined2 FUN_08884680(uint param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uVar3;
  
  param_1 = param_1 & 0xffff;
  uVar1 = 0;
  uVar2 = 0x2d;
  if (DAT_08a33310 <= param_1) {
    uVar1 = 0x2e;
    uVar2 = 0x5a;
    if (param_1 <= DAT_08a33310) {
      uVar3 = 0x2d;
      goto LAB_088846d0;
    }
  }
  uVar3 = FUN_08884724(param_1,uVar1,uVar2);
  uVar3 = uVar3 & 0xffff;
LAB_088846d0:
  return *(undefined2 *)
          (&DAT_08a2fb60 +
          //(
		  //(param_1 - *(ushort *)(&DAT_08a3325c + uVar3 * 4)) 
		  //+
		  // Next one at 0x8a3325e
          (uint)*(ushort *)(&DAT_08a3325e + uVar3 * 4)
		  )
		   * 2);
}


uint FUN_08884724(ushort param_1,uint param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  
  param_3 = param_3 & 0xffff;
  param_2 = param_2 & 0xffff;
  uVar3 = param_3 + param_2 >> 1;
  uVar1 = param_3 - 1 & 0xffff;
  if ((param_3 != param_2) &&
     ((uVar2 = uVar3, param_1 < *(ushort *)(&DAT_08a3325c + uVar3 * 4) ||
      (param_2 = uVar3 + 1 & 0xffff, uVar2 = param_3, uVar1 = uVar3,
      *(ushort *)(&DAT_08a3325c + uVar3 * 4) < param_1)))) {
    uVar1 = FUN_08884724(param_1,param_2,uVar2);
  }
  // param1==*(ushort *)(&DAT_08a3325c + uVar3 * 4)
  return uVar1;
}


```

08a3325c -> 0~0x5a

20 00 00 00 a1 00 5f 00 40 81 9e 00 80 81 dd 00 b8 81 0a 01 c8 81 12 01 da 81 19 01 f0 81 28 01 fc 81 30 01 4f 82 31 01 60 82 3b 01 81 82 55 01 9f 82 6f 01 40 83 c2 01 80 83 01 02 9f 83 18 02 bf 83 30 02 40 84 48 02 70 84 69 02 80 84 78 02 9f 84 8a 02 9f 88 aa 02 40 89 08 03 80 89 47 03 40 8a c4 03 80 8a 03 04 40 8b 80 04 80 8b bf 04 40 8c 3c 05 80 8c 7b 05 40 8d f8 05 80 8d 37 06 40 8e b4 06 80 8e f3 06 40 8f 70 07 80 8f af 07 40 90 2c 08 80 90 6b 08 40 91 e8 08 80 91 27 09 40 92 a4 09 80 92 e3 09 40 93 60 0a 80 93 9f 0a 40 94 1c 0b 80 94 5b 0b 40 95 d8 0b 80 95 17 0c 40 96 94 0c 80 96 d3 0c 40 97 50 0d 80 97 8f 0d 40 98 0c 0e 9f 98 3f 0e 40 99 9d 0e 80 99 dc 0e 40 9a 59 0f 80 9a 98 0f 40 9b 15 10 80 9b 54 10 40 9c d1 10 80 9c 10 11 40 9d 8d 11 80 9d cc 11 40 9e 49 12 80 9e 88 12 40 9f 05 13 80 9f 44 13 40 e0 c1 13 80 e0 00 14 40 e1 7d 14 80 e1 bc 14 40 e2 39 15 80 e2 78 15 40 e3 f5 15 80 e3 34 16 40 e4 b1 16 80 e4 f0 16 40 e5 6d 17 80 e5 ac 17 40 e6 29 18 80 e6 68 18 40 e7 e5 18 80 e7 24 19 40 e8 a1 19 80 e8 e0 19 40 e9 5d 1a 80 e9 9c 1a 40 ea 19 1b 80 ea 58 1b

00000020 005f00a1 009e8140 00dd8180 010a81b8 011281c8 011981da 012881f0 013081fc 0131824f 013b8260 01558281 016f829f 01c28340 02018380 0218839f 023083bf 02488440 02698470 02788480 028a849f 02aa889f 03088940 03478980 03c48a40 04038a80 04808b40 04bf8b80 053c8c40 057b8c80 05f88d40 06378d80 06b48e40 06f38e80 07708f40 07af8f80 082c9040 086b9080 08e89140 09279180 09a49240 09e39280 0a609340 0a9f9380 0b1c9440 0b5b9480 0bd89540 0c179580 0c949640 0cd39680 0d509740 0d8f9780 0e0c9840 0e3f989f 0e9d9940 0edc9980 0f599a40 0f989a80 10159b40 10549b80 10d19c40 11109c80 118d9d40 11cc9d80 12499e40 12889e80 13059f40 13449f80 13c1e040 1400e080 147de140 14bce180 1539e240 1578e280 15f5e340 1634e380 16b1e440 16f0e480 176de540 17ace580 1829e640 1868e680 18e5e740 1924e780 19a1e840 19e0e880 1a5de940 1a9ce980 1b19ea40 1b58ea80

第二位，
40-7E
80-FC

仅仅有编码的区域被列入。
ea80-eaa4
最末一位偏移量 1b58 + 25 = 1B7d = 7037

恰好为SHIFT-JIS编码总数
（7070？）有待查询，或许有些许删节。

GB2312有6763个汉字+682个全角字符。


字体替换：将对SceFontOpen的调用变为SceFontOpenUserFile的调用。
不知道Fontfuck Library的适用程度如何。

处于某些原因，PPSSPP无法正确解析PGF文件？可能是其SceFont实现有一些问题？
Jpcsp对于现成的字体没有什么问题。

CLANNED用的是微软雅黑，对字库进行了修改。
Jpcsp使用的是Resource Han Rounded CN，可以说是对于中文用户十分友好了。
MGSPW用的是微软雅黑Bold，没有对字库进行修改。Font='Microsoft YaHei UI' Type='Bold'