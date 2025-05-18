# Media Engine (ME): PSP's second CPU

PSP拥有两颗CPU。

列举一下使用ME的项目
+ yabause(2011)
```
0.9.12 -> 0.9.13
 general:
  - Removed Carbon, PSP, Wii and Windows ports
0.9.10 -> 0.9.11
 psp port:
  - Added support for Media Engine CPU
  - Improvements to the PSP port 
```
+ DaedalusX64 / daedalus
+ IridescentRose / MElib

看来看去，越看越累。不写代码在这里瞎研究就是这个坏处。
还有个古早版本的MELib，不知道有没有用。
或许新旧PSPSDK的衔接就在这里：使用PRX文件！

这个东西目前搞不太懂，操作ME需要修改各种奇怪的硬件寄存器（在较高的虚拟地址上），注释过少资料过少，有赖进一步探索，一时半会儿搞不清楚，先观望一下看看能否有老外封装出可用的库。

melib.h
```C
/*
PMP Mod
Copyright (C) 2006 jonny

/*
simple lib to use the psp me

a lot of code is taken from here: http://forums.ps2dev.org/viewtopic.php?t=2652
thanks to crazyc, mrbrown, Brunni, xdeadbeef and anyone else involved
(major optimizations in libavcodec are done with the me)
*/
```