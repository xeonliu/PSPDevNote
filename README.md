# PSPDevNote
Take notes on PlayStation Portable development.

aka. PlayStation Portable : A Programmer's Perspective

Homepage: https://xeonliu.github.io/PSPDevNote/

[CC-BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/)

- [x] Targets of Build
- [ ] Environment Setup
	- [x] PSPDEV
	- [x] VS Code
- [ ] PSPDEV Directory Structure
- [ ] Build System
	- [ ] How to Build from Source
	- [x] Break Down Makefile Sample
- [ ] File Formats used on PSP
- [ ] Hello World
- [ ] Command-Line Tools (Arguments, Source Code)
- [ ] Link
	- [x] Use Third-Party Libraries（Static Link）
  	- [x] Import External PRX Modules (Dynamic Link)
		- [x] Stub / Resident Libraries
		- [x] PRX File
		- [ ] Write Plugins
- [ ] Device Capability
	- [ ] Screen
	- [ ] Utility
		- [ ] Dialog
		- [ ] On Screen Keyboard. A.k.a OSK
	- [ ] Network
	- [x] Video Decode
	- [ ] I/O
	- [ ] Time
- [ ] Debug
  - [ ] PSPLink
  - [ ] PPSSPP
- [ ] Release
	- [x] EBOOT.PBP
	- [ ] ISO / CSO
- [x] Github Actions CI
- [ ] Patches (Reverse Engineering)
    - [x] MIPS Assembly
    - [x] Memory Address Space
    - [ ] Edit Staticly（ELF File）
    - [ ] Edit Dynamically（插件/CWCheat）
    - [ ] Localization Tutorial

## Roadmap

+ 如欲掌握基本游戏开发技巧，可从Third Party Libraries直接跳至调试步骤。研究SDL项目。使用PSP部分功能可能需要阅读StubLib一节

+ 如欲开发Plugin或者Patch现有游戏，请仔细阅读StubLib一节

+ 如欲对现有游戏进行汉化，请阅读StubLib、Debug及Reverse Engineering和Patch一节。

## Complaints
全是deprecated和temporary fix.必须靠询问来得知各种使用方法best practice
另一方面必须要有能阅读上游代码的能力。

CS:APP显然不足以解释清楚PSP的软硬件，尤其是涉及到中断、硬件寄存器操作等话题时，这得交给OS相关的课程。

## Acknowledgement
+ PSPDEV / PSPSDK(Unofficial)
+ PSP Homebrew Discord
+ rust-psp
+ ppsspp
+ uofw
+ IridescentRose
+ Official PSP™ (PlayStation®Portable) SDK
