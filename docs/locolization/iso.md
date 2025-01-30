# UMD文件系统

在读取UMD得到的的镜像文件中，文件目录以如下格式组织：

+ SYSDIR
    + BOOT.BIN：通常为空
    + EBOOT.BIN：加密的游戏主程序文件
+ USRDIR
    + 储存各类资源文件，包括模块（Module）等