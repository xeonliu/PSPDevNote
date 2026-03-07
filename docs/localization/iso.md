# UMD文件系统

UMD镜像使用ISO9660文件系统，同时采用了部分扩展。

## 提取 UMD 镜像

在 CFW 中提取镜像很简单。
- 在 VSH 菜单中，将 USB 设备切换为 UMD
- 连接电脑即可在文件系统中看到对应的 ISO 文件
- 拷贝到电脑即可

## 常用软件

- UMDGen - 修改 UMD 镜像，进行增删查改，生成兼容 PSP 的镜像。
- 重打包脚本 - 添加/修改 UMD 镜像中的文件

在读取UMD得到的的镜像文件中，目录以如下格式组织：

+ SYSDIR
    + BOOT.BIN：通常为空
    + EBOOT.BIN：加密的游戏主程序文件
+ USRDIR
    + 储存游戏运行过程中所需的各类资源文件


## LBA寻址

LBA，即逻辑块地址。PSP的系统IO函数支持使用`...`格式访问 UMD。

- [破解"LBA加密"](https://blog.csdn.net/qqj_1228/article/details/5092558)