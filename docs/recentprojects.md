# 近年项目
自2020年开始，PSP Homebrew 社区每年召开一次PSP开发者大会(PSP Homebrew Developer Conference)，分享PSP软硬件开发的最新成果，有必要列举一下，以增进对PSP开发现状与前景的了解。

知道哪些东西已经有人做过了，自已又能用哪些东西，十分重要。

## 模拟器 (Emulators)
为了实现渲染和视频等方面的硬件加速，模拟器对PSP的各项处理器如VFPU, Graphics Engine(GE)和Media Engine(ME)的使用量均达到较高水平。研究这些模拟器的实现对于开发者了解如何优化PSP程序性能有很大帮助。

现在还是没看懂有关ME的东西……

+ 2021
    + [DeSmuME](https://www.gamebrew.org/wiki/DeSmuME_PSP): 任天堂DS模拟器
    
    + [nullDC](https://github.com/PSP-Archive/nulldce-psp/): 世嘉Dreamcast模拟器

+ 2023
    + [retroArch](https://github.com/libretro/RetroArch): 跨平台早期游戏终端（如GBA）模拟器，对于使用Kernal Function和多PRX加载极具研究价值。可以在 `PPSSPP`上运行。
    

## 游戏引擎 (Game Engine)
游戏引擎似乎一直是开发者大会上的大热门。每个人都想推广自己的API用来做游戏。

openTRI?
+ 2020
    + [Startdust Engine]()

+ 2021
    + [Gen7 Engine]()
    + [Integrity Engine]()
+ 2022

+ 2023

## 移植(Port)
对其他终端独占游戏的移植或重置亦是开发者大会上的热门。
+ 2020
    + Spelunky PSP: 跨平台开发的启示。Youtube上有一组视频展示。
+ 2021

## 教程(Tutorials)
+ 2021
    + [Platformer Template](https://github.com/stacksta/Advanced_Platformer_Template-PSP/): openTri引擎的使用。