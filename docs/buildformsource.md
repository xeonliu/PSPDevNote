# Build PSPDEV from source

在前面我们已经看到，pspdev 在 GitHub 上已经提供了面对多个平台编译好的 Release 版本的下载。利用我们所学的对编译体系的认识，尝试看看如何用一系列工具从源代码编译生成所需的文件。

在 PSPDEV 的 Github Repository 中，我们可以看到许多 Shell 脚本。让我们具体看看他们以何种顺序执行，都做了些什么来得到 Release。

> 参考阅读
>
> MIT Missing Semester: Shell Scripts

!!! Hint
	编译源代码是个耗时耗力的过程，如果想直接开发，还是去下载Release版本！
## 文件目录结构
```
pspdev
├── Dockerfile
├── LICENSE
├── README.md
├── build-all.sh
├── build-extra.sh
├── depends
│   ├── check-dependencies.sh
│   ├── check-pspdev.sh
│   └── check-sh-is-not-dash.sh
├── prepare-arch.sh
├── prepare-debian-ubuntu.sh
├── prepare-fedora.sh
├── prepare-gentoo.sh
├── prepare-mac-os.sh
└── scripts
    ├── 001-psptoolchain.sh
    ├── 002-pspsdk.sh
    ├── 003-psp-packages.sh
    ├── 004-psplinkusb-extra.sh
    └── 005-ebootsigner-extra.sh
```

## `pspdev`根目录中的脚本

如果只想自己 build 的话，git clone 到本地后只需要进行一些配置并执行下面两个脚本。第二个脚本会自动执行子目录中的脚本。

### `pspdev/prepare-*.sh`

- 这些脚本用于安装编译和运行时所需的各种依赖

```bash title="prepare-debian-ubuntu.sh" linenums="1"
  #!/bin/bash

  # Install build dependencies
  sudo apt-get install $@ \
  git gzip libarchive-dev libcurl4 libcurl4-openssl-dev libelf-dev libgpgme-dev libncurses5-dev libreadline-dev libssl-dev \
  libtool-bin libusb-dev m4 make patch pkg-config python3 python3-venv subversion tar tcl texinfo unzip wget xz-utils \
  sudo fakeroot libarchive-tools curl libgmp3-dev libmpfr-dev libmpc-dev python3-pip autoconf automake bison bzip2 cmake doxygen flex g++ gcc
```

### `pspdev/build-all.sh`

- 自动执行`pspdev/depends`下的脚本检查依赖安装情况
    - `check-pspdev.sh`：是否已经手动创建 PSPDEV 目录并指定环境变量
    - `check-dependencies.sh`：是否已经安装所需依赖
    - `check-sh-is-not-dash.sh`：是否使用 bash 作为默认终端
- 自动执行`pspdev/scripts`下的脚本下载多个项目的源码并进行编译

## 子目录`depends`下的脚本

### `check-pspdev.sh`

  - 执行前需要手动设置 PSPDEV 环境变量并改变 PATH 环境变量
  - 检查如下配置
```shell linenums="1" hl_lines="4 7 10 13"
  #!/bin/sh
  # check-pspdev.sh by Naomi Peori (naomi@peori.ca)

  ## Check if $PSPDEV is set.
  if test ! $PSPDEV; then { echo "ERROR: Set \$PSPDEV before continuing."; exit 1; } fi

  ## Check for the $PSPDEV directory.
  ls -ld $PSPDEV > /dev/null 2>&1 || mkdir -p $PSPDEV > /dev/null 2>&1 || { echo "ERROR: Create $PSPDEV before continuing."; exit 1; }

  ## Check for write permission.
  touch $PSPDEV/test.tmp > /dev/null 2>&1 || { echo "ERROR: Grant write permissions for $PSPDEV before continuing."; exit 1; }

  ## Check for $PSPDEV/bin in the path.
  echo $PATH | grep $PSPDEV/bin > /dev/null 2>&1 || { echo "ERROR: Add $PSPDEV/bin to your path before continuing."; exit 1; }

```

- 什么是环境变量？
    - 参考 MIT Missing Semester 第一集
- 如何设置环境变量？

    - `export <NAME>='<value>'`
    - 通过在`~/.bashrc`中添加这一行使得每次启动 shell 时生效
    - 输入`source ~/.bashrc`以重新加载
!!! 官方说明
	Add this to your login script (example: ~/.bash_profile) Note: Ensure that you have full access to the PSPDEV path. You can change the PSPDEV path with the following requirements: only use absolute paths, don't use spaces, only use Latin characters.
	```shell linenums="1"
	export PSPDEV=/usr/local/pspdev
	export PATH=$PATH:$PSPDEV/bin
	```

### `check-dependencies.sh`

- 负责检查如下依赖
```shell linenums="1"
     check_program   which
     check_program   git
     check_program   patch
     check_program   autoconf
     check_program   automake
     check_program   make
     check_program   cmake
     check_program   gcc
     check_program   g++
     check_program   bison
     check_program   flex
     check_program   python3
     check_program   pip3
     check_program   gpgme-tool

     # macOS uses it's own fork of libtool
     if [ "$(uname)" != "Darwin" ]; then
     check_program libtoolize
     else
     check_program glibtoolize
     fi

     check_library   libarchive
     check_library   openssl
     check_library   ncurses
```

## 子目录`scripts`下的脚本

```

```

## 使用 Github Action 自动构建