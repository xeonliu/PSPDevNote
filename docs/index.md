# Welcome to PSPDevNotes

创建这个网站的初衷，一个是想研究古早设备，另一个是想作为学习的契机。通过一个近 20 年前的设备，学习计算机知识。

## Goals

- 熟悉 Linux 开发环境，Bash Shell 的有关知识
- 熟悉 GNU 的一系列工具，了解大型 C/C++项目如何组织
- 练习使用 git 和 GitHub，尝试使用 CI/CD 工具
- 学习计算机系统基础
	- 了解MIPS架构汇编的有关知识和处理器流水线的设计
	- 了解编译和链接的相关知识，了解程序加载的相关概念
    - 了解内存相关概念
	- 了解异常控制流（ECF）、系统调用，内核态与用户态程序
	- 学习线程的概念，体会并发
- 从 GNU Make 到 CMake
- 了解不同平台的差异
- 学习如何将不同工具整合成一套工作流

## TODO：
- [x] 构建的目标
- [ ] 环境配置
	- [x] PSPDEV
	- [ ] VSCode
- [ ] PSPDEV目录结构
- [ ] 编译体系
	- [ ] 从源代码构建PSPSDK
	- [x] Makefile 示例解析
- [ ] PSP 文件格式
- [ ] Hello World
- [ ] 命令行工具详解（参数、源代码）
- [ ] 静态链接
	- [x] 引入第三方库（静态链接）
  	- [x] 导入外部`prx`模块（动态链接）
		- [x] Stub/Resident Libraries
			- [x] 模块导出
			- [x] 模块导入
		- [x] PRX文件
			- [x] Sections
		- [ ] 模块加载
- [ ] 模块
  - [ ] 操作系统架构
  - [ ] 内核模块
  - [ ] 用户模块
- [ ] 设备功能
	- [ ] 显示
	- [ ] 实用程序(Utility)
		- [ ] 弹窗(Dialog)
		- [ ] 屏幕键盘(On Screen Keyboard. A.k.a OSK)
	- [ ] 网络
	- [x] 视频解码
	- [ ] I/O
	- [ ] 时间
- [ ] 虚拟内存
- [ ] 缓存 (Cache)
- [ ] 调试
  - [ ] PSPLink
  - [ ] PPSSPP
- [ ] 发布
	- [x] EBOOT.PBP
	- [ ] ISO / CSO
- [x] Github Actions 自动构建
- [ ] 逆向工程
    - [ ] MIPS汇编
    - [ ] 静态分析工具(Ghidra & Scripts)
- [ ] 补丁
    - [ ] 静态修改（ELF文件）
    - [ ] 动态修改（插件/CWCheat）
    - [ ] 编写CFW插件
    - [x] 汉化教程

## Roadmap

+ 如欲掌握基本游戏开发技巧，可从Third Party Libraries直接跳至调试步骤。研究SDL项目。使用PSP部分功能可能需要阅读StubLib一节

+ 如欲开发Plugin或者Patch现有游戏，请仔细阅读StubLib一节

+ 如欲对现有游戏进行汉化，请阅读StubLib、Debug及Reverse Engineering和Patch一节。

## 抱怨
全是deprecated和temporary fix.必须靠询问来得知各种使用方法best practice

## 致谢
+ PSPDEV / PSPSDK(Unofficial)
+ PSP Homebrew Discord
+ rust-psp
+ ppsspp
+ uofw
+ IridescentRose
+ Official PSP™ (PlayStation®Portable) SDK
