# PSPDevNote
Take notes on PlayStation Portable development.

aka. PlayStation Portable : A Programmer's Perspective

Homepage: https://xeonliu.github.io/PSPDevNote/

[CC-BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/)

- [x] 构建的目标
- [ ] 环境配置
	- [x] PSPDEV
	- [x] VSCode
- [ ] PSPDEV目录结构
- [ ] 编译体系
	- [ ] 如何 Build from source
	- [x] Makefile 示例解析
- [ ] PSP 文件格式
- [ ] Hello World
- [ ] 命令行工具详解（参数、源代码）
- [ ] 链接
	- [x] 引入第三方库（静态链接）
  	- [x] 导入外部`prx`模块（动态链接）
		- [x] Stub/Resident Libraries
		- [x] PRX文件
		- [ ] 系统调用
		- [ ] 编写插件
- [ ] 设备功能
	- [ ] 显示
	- [ ] 实用程序(Utility)
		- [ ] 弹窗(Dialog)
		- [ ] 屏幕键盘(On Screen Keyboard. A.k.a OSK)
	- [ ] 网络
	- [x] 视频解码
	- [ ] I/O
	- [ ] 时间
- [ ] 调试
  - [ ] PSPLink
  - [ ] PPSSPP
- [ ] 发布
	- [x] EBOOT.PBP
	- [ ] ISO / CSO
- [x] Github Actions 自动构建
- [ ] 补丁（逆向工程）
    - [ ] MIPS汇编
    - [ ] 内存地址空间
    - [ ] 静态修改（ELF文件）
    - [ ] 动态修改（插件/CWCheat）
    - [ ] 汉化教程

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
