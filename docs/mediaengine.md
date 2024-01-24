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