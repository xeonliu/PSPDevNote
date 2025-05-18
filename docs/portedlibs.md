# 移植第三方库

`PSPDEV`如今采用`pacman`进行包管理，以`GitHub`仓库作为软件源。

在`pspdev/psp-packages`中，第三方库以
+ `patch` file
+ `BUILD` file
的形式定义了构建的过程。

使用`psp-pacman`安装的程序位于``