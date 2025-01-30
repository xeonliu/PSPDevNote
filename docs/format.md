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
SFO（System File Object）用于储存需要在PSP XMB（XrossMediaBar）中显示的文件。

SFO同样存在于PS3、PS Vita和PS4上。

+ SFO中包含的值可以简化为内容的输入/输出：
    + 启动修改器（大多数为int32数据），在内容被执行时发送给内容，以激活特定功能或设置（例如游戏的音频和视频模式）。
    + 关于内容及其限制的信息文本（大多数为UTF-8数据），例如游戏的标题和版本。
# PBP