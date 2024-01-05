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
```
curl -JLO URL_of_the_file
```

+ Using `wget`
```
wget URL
```

## Extract the file using `tar`
` tar -xvf pspdev-ubuntu-latest.tar.gz`

现在当前目录应该出现一个名为pspdev的文件夹。

------

## 使用VSCode远程连接之

### SSH
配置SSH
### 设置C/C++插件的includePath
VSCode并不知道你要用到的PSPSDK中的头文件在哪里，会标注红波浪线。在json配置文件中修改


## Git Proxy Config

```
git config --global http.proxy "http://..."
git config --global https.proxy "http://"
```

```
git config --global --unset http.proxy
git config --global --unset https.proxy
```
