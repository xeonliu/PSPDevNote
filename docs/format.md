# Format Specification
在PSP开发中涉及的文件格式
> 推荐阅读：
>> Yet another PSP Documentation [Chapter 26: File Formats](https://gigawiz.github.io/yapspd/html_chapters_split/chap26.html) (2006)

# ELF
经典的可执行文件格式。经过`psp-prxgen`可以变换为PRX。
# PRX
特殊的可执行文件
+ Encrypted 在OFW上运行，理论上需要索尼授权加密
+ Unencrypted 在CFW上运行

PRX 文件需要重点讲一下。它里面涉及到太多使用StubLibrary和导入导出相关的规则

# SFO

# PBP