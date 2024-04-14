# Set Up the Environment

在开始编写程序之前，我们需要首先配置好相关的环境。

> 参见：https://pspdev.github.io/

注意：使用Ubuntu 22.04及以上版本

# Install PSPDEV Toolchain

## Dependencies
想使用PSPDev提供的工具链，首先需要安装以下依赖
```bash
sudo apt-get update
sudo apt-get install build-essential cmake pkgconf libreadline8 libusb-0.1 libgpgme11 libarchive-tools fakeroot
```
这其中有`CMake`、`pkgconf`之类的构建工具，也有用于连接PSP进行调试的`libusb`等工具

## Download PSPDev from website

+ Using `curl`
```shell
curl -JLO URL_of_the_file
```

+ Using `wget`
```shell
wget URL
```

## Extract the file using `tar`
` tar -xvf pspdev-ubuntu-latest.tar.gz`

现在当前目录应该出现一个名为pspdev的文件夹。

------

## 使用VSCode远程连接之

### SSH
配置SSH
`sudo apt install openssh-server`
### VSCode连接服务器下载卡住
https://blog.csdn.net/qq_45021180/article/details/131444776
### 设置C/C++插件的includePath
VSCode并不知道你要用到的PSPSDK中的头文件在哪里，无法提供自动补全，会标注红波浪线。在C/C++插件的json配置文件中修改
本质上针对PSP的开发就是跨平台编译。与x86下对arm架构的开发流程有很多相似之处
https://code.visualstudio.com/docs/cpp/configure-intellisense-crosscompilation


https://code.visualstudio.com/docs/cpp/launch-json-reference


## Git Proxy Config

```
git config --global http.proxy "http://..."
git config --global https.proxy "http://"
```

```
git config --global --unset http.proxy
git config --global --unset https.proxy
```
