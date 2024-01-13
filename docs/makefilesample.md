# Makefile Example

编写好代码之后，还需要编译汇编链接才能生成 PSP 可执行的文件。PSPDev 提供了一套完整的 GNU 工具链供编译使用。

## 推荐阅读

> 【【技术杂谈】C 编译体系】 https://www.bilibili.com/video/BV1J14y1D7Sw

> 【其他】make 到底干了些什么 http://bbs.chinaemu.org/read-htm-tid-86754-uid-12451.html

## EBOOT.PBP 的构建流程

1.  编译生成.o 可重定位目标文件（自己负责）。指定变量`OBJS`
2.  链接静态链接库（.a 文件，在 pspdev/psp/sdk/lib 中）生成 ELF 可执行目标文件。指定变量`LIBS`
    `Makefile linenums="1" hl_lines="2"
$(TARGET).elf: $(OBJS) $(EXPORT_OBJ)
	$(LINK.c) $^ $(LIBS) -o $@
	$(FIXUP) $@
`
    注：LINK.C 是 GNU MAKE 中默认的变量，会展开
    注：参考 CSAPP 7.6.2 与静态库链接
3.  使用`psp-fixup-imports`修复 ELF 文件的导入表。
    ```Makefile linenums="1" hl_lines="3"
    $(TARGET).elf: $(OBJS) $(EXPORT_OBJ)
    	$(LINK.c) $^ $(LIBS) -o $@
    	$(FIXUP) $@
    ```
4.  生成 PSP 上的可执行文件。PSP 支持 ELF 和 PRX 两种可执行文件格式。 - （选择 1）使用 psp-strip 删除 ELF 文件中的符号表信息
    `Makefile
      $(STRIP) $(TARGET).elf -o $(TARGET)_strip.elf
      ` - （选择 2）用 psp-prxgen 生成 PRX 文件（期间会删除符号表信息）。指定变量`BUILD_PRX`
    `Makefile
      %.prx: %.elf
      	psp-prxgen $< $@
      ` - 对于 PRX 文件，可以使用`PrxEncrypter`进行加密使其能在未经修改的 PSP 上运行。指定变量`ENCRYPT`
    `makefile
      ifeq ($(ENCRYPT), 1)
      	- $(ENC) $(TARGET).prx $(TARGET).prx
      `
    !!! Hint
    PRX 文件的生成依赖于特定的 ELF 文件。如果最终目标是生成 PRX 文件，则在第二步链接生成 ELF 文件时除了指定静态链接库还需要添加一些附加的指令。
    `Makefile
LDFLAGS  := $(addprefix -L,$(LIBDIR)) -specs=$(PSPSDK)/lib/prxspecs -Wl,-q,-T$(PSPSDK)/lib/linkfile.prx $(LDFLAGS)
`
5.  使用 mksfo/mksfoex 生成 SFO 信息文件。指定相关变量`SFOFLAGS` `PSP_EBOOT_TITLE`

    ```makefile
    $(PSP_EBOOT_SFO):
    $(MKSFO) $(SFOFLAGS) '$(PSP_EBOOT_TITLE)' $@
    ```

    !!! Hint
    有关 SFO 文件格式，参考文件格式一页。

        有关mksfo使用及源码解析，参考工具一页。

6.  使用 pack-pbp 将 SFO 文件、ELF/PRX 文件和其他资源文件打包生成 EBOOT.PBP。指定相关变量`PSP_EBOOT_SFO`、`PSP_EBOOT_ICON`、`PSP_EBOOT_ICON1`、`PSP_EBOOT_UNKPNG`、`PSP_EBOOT_PIC1`、`PSP_EBOOT_SND0`、`PSP_EBOOT_PSAR`

    ```Makefile
    $(PACK_PBP) $(PSP_EBOOT) $(PSP_EBOOT_SFO) $(PSP_EBOOT_ICON)  \
    	$(PSP_EBOOT_ICON1) $(PSP_EBOOT_UNKPNG) $(PSP_EBOOT_PIC1)  \
    	$(PSP_EBOOT_SND0)  $(TARGET)_strip.elf $(PSP_EBOOT_PSAR)

    ```

    !!! Hint
    有关 PBP 文件格式，参考文件格式一页。

        有关pack-pbp使用及源码解析，参考工具一页。

## HelloWorld 示例中的 Makefile

## PSPDEV 提供的基础 Makefile

不要忘记了，写笔记的目的不仅仅是为了使用 PSPSDK 开发，更是为了学习相关知识。所以在解析 Makefile 的过程中会穿插知识点和参考。
位于`pspdev/psp/sdk/lib`基础的 Makefile 文件`build.mak`，通常会在自己的 Makefile 包含。

```makefile title="pspdev/psp/sdk/lib/build.mak"
# Note: The PSPSDK make variable must be defined before this file is included.
ifeq ($(PSPSDK),)
$(error $$(PSPSDK) is undefined.  Use "PSPSDK := $$(shell psp-config --pspsdk-path)" in your Makefile)
endif
```

使用前要求变量 PSPSDK 已经被定义。

```makefile
CC       = psp-gcc
CXX      = psp-g++
AS       = psp-gcc
LD       = psp-gcc
AR       = psp-gcc-ar
RANLIB   = psp-gcc-ranlib
STRIP    = psp-strip
MKSFO    = mksfoex
PACK_PBP = pack-pbp
FIXUP    = psp-fixup-imports
ENC		 = PrxEncrypter
```

通过变量定义了需要用到的可执行程序的缩写，这些程序位于前述的`pspdev/bin`中
其中`psp-strip`用于删除 ELF 符号表以优化文件大小，`mksfoex`用于生成`SFO`文件，`PrxEncrypter`用于加密`PRX`文件

```makefile
# Add PSPSDK includes and libraries.
INCDIR   := $(INCDIR) . $(PSPDEV)/psp/include $(PSPSDK)/include
LIBDIR   := $(LIBDIR) . $(PSPDEV)/psp/lib $(PSPSDK)/lib

CFLAGS   := $(addprefix -I,$(INCDIR)) -G0 $(CFLAGS)
CXXFLAGS := $(CFLAGS) $(CXXFLAGS)
ASFLAGS  := $(CFLAGS) $(ASFLAGS)

SFOFLAGS := -d MEMSIZE=$(EXPAND_MEMORY) $(SFOFLAGS)

CFLAGS += -D_PSP_FW_VERSION=$(PSP_FW_VERSION)
CXXFLAGS += -D_PSP_FW_VERSION=$(PSP_FW_VERSION)
LDFLAGS  := $(addprefix -L,$(LIBDIR)) -specs=$(PSPSDK)/lib/prxspecs -Wl,-q,-T$(PSPSDK)/lib/linkfile.prx $(LDFLAGS)
# Reduce binary size
LDFLAGS +=  -Wl,-zmax-page-size=128

ifeq ($(USE_KERNEL_LIBS),1)
LIBS := -nostdlib $(LIBS) -lpspdebug -lpspdisplay_driver -lpspctrl_driver -lpspmodinfo -lpspsdk -lpspkernel
else
LIBS := $(LIBS) -lpspdebug -lpspdisplay -lpspge -lpspctrl \
		-lpspnet -lpspnet_apctl
endif

$(PSP_EBOOT_SFO):
	$(MKSFO) $(SFOFLAGS) '$(PSP_EBOOT_TITLE)' $@

ifeq ($(BUILD_PRX),1)
$(PSP_EBOOT): $(TARGET).prx $(PSP_EBOOT_SFO)
ifeq ($(ENCRYPT), 1)
	- $(ENC) $(TARGET).prx $(TARGET).prx
endif
	$(PACK_PBP) $(PSP_EBOOT) $(PSP_EBOOT_SFO) $(PSP_EBOOT_ICON)  \
		$(PSP_EBOOT_ICON1) $(PSP_EBOOT_UNKPNG) $(PSP_EBOOT_PIC1)  \
		$(PSP_EBOOT_SND0)  $(TARGET).prx $(PSP_EBOOT_PSAR)
else
$(PSP_EBOOT): $(TARGET).elf $(PSP_EBOOT_SFO)
	$(STRIP) $(TARGET).elf -o $(TARGET)_strip.elf
	$(PACK_PBP) $(PSP_EBOOT) $(PSP_EBOOT_SFO) $(PSP_EBOOT_ICON)  \
		$(PSP_EBOOT_ICON1) $(PSP_EBOOT_UNKPNG) $(PSP_EBOOT_PIC1)  \
		$(PSP_EBOOT_SND0)  $(TARGET)_strip.elf $(PSP_EBOOT_PSAR)
	-rm -f $(TARGET)_strip.elf
endif

%.prx: %.elf
	psp-prxgen $< $@

%.c: %.exp
	psp-build-exports -b $< > $@
```

LINK.c
The basic cc command line to link object files, such as COMPILE.c, but without the -c option and with a reference to the LDFLAGS macro:

```
LINK.c=$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
```

https://docs.oracle.com/cd/E19504-01/802-5880/6i9k05dhg/index.html#make-40951

Running "make -p" without a Makefile will show you Make's default
variables and rules. Like those for linking; among others:

LINK.o = $(CC) $(LDFLAGS) $(TARGET_ARCH)
LINK.cc = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)
LINK.C = $(LINK.cc)
LINK.cpp = $(LINK.cc)
https://lists.gnu.org/archive/html/help-make/2012-01/msg00058.html

make -p | grep LINK.c

A Makefile will automate the build process. Below is the basic actions it does. If on Linux, translation of the -I and -L switches will be needed, as this points to a typical windows install directory. To get this path correct 100% of the time, a tool called psp-config is available. Try using psp-config -p and append it with /include for -I and /lib for -L.

```bash
psp-gcc -O0 -g3 -Wall -I. -IC:/pspsdk/psp/sdk/include -L. -LC:/pspsdk/psp/sdk/lib -D_PSP_FW_VERSION=150 -c *.c -lpspdebug -lpspdisplay -lpspge -lpspctrl -lpspsdk -lc -lpspnet -lpspnet_inet -lpspnet_apctl -lpspnet_resolver -lpsputility -lpspuser -lpspkernel

psp-gcc -O0 -g3 -Wall -I. -IC:/pspsdk/psp/sdk/include -L. -LC:/pspsdk/psp/sdk/lib -D_PSP_FW_VERSION=150 -o raw_eboot.elf *.o -lpspdebug -lpspdisplay -lpspge -lpspctrl -lpspsdk -lc -lpspnet -lpspnet_inet -lpspnet_apctl -lpspnet_resolver -lpsputility -lpspuser -lpspkernel

psp-fixup-imports raw_eboot.elf
mksfo 'XMB_TITLE' PARAM.SFO
psp-strip raw_eboot.elf -o strip_eboot.elf
pack-pbp EBOOT.PBP PARAM.SFO NULL NULL NULL NULL NULL strip_eboot.elf NULL
```

Compile all the files into objects
Link all objects and libraries into an .elf file
Create a .SFO file for XMB use
Strip the .elf file to shrink size and reduce redundancy
Create an EBOOT.PBP file, which houses additional XMB information (see pack-pbp --help)

https://en.wikibooks.org/wiki/PSP_Development/Hello_World_Application

## Libraries Available

```
cmake
crt0.o
crt0_prx.o
ldscripts
libAngelscript.a
libGL.a
libGLU.a
libSDL.a
libSDL2.a
libSDL2_gfx.a
libSDL2_image.a
libSDL2_mixer.a
libSDL2_ttf.a
libSDL2main.a
libSDL_gfx.a
libSDL_image.a
libSDL_mixer.a
libSDL_ttf.a
libSDLmain.a
libargtable2.a
libatomic.a
libatomic.la
libbulletml.a
libbz2.a
libc.a
libcglue.a
libcjson.a
libcjson_utils.a
libconfuse.a
libconfuse.la
libcurl.a
libdumb.a
libenet.a
libexpat.a
libfreetype.a
libg.a
libglut.a
libintrafont.a
libjpeg.a
libjsoncpp.a
liblua.a
libm.a
libmad.a
libmbedcrypto.a
libmbedtls.a
libmbedx509.a
libmikmod.a
libminizip.a
libogg.a
libopenal.a
libpixman-1.a
libpixman-1.la
libpng
libpng.a
libpng16.a
libpocketpy.a
libpolarssl.a
libpspkernel.a
libpspkubridge.a
libpspmodinfo.a
libpspnet_inet.a
libpspnet_resolver.a
libpsprtc.a
libpspsdk.a
libpspuser.a
libpsputility.a
libpspvram.a
libpspvramalloc.a
libpthread.a
libpthreadglue.a
libsmpeg.a
libsqlite3.a
libsqstdlib.a
libsqstdlib_static.a
libsquirrel.a
libsquirrel_static.a
libstdc++.a
libstdc++.a-gdb.py
libstdc++.la
libsupc++.a
libsupc++.la
libtri.a
libturbojpeg.a
libun7zip.a
libvorbis.a
libvorbisenc.a
libvorbisfile.a
libxmp-lite.a
libxmp.a
libyaml.a
libz.a
libzip.a
libzzip-0.a
libzzipfseeko-0.a
libzzipmmapped-0.a
libzzipwrap-0.a
objects-Release
pkgconfig
```
```
if(PSP)
40 link_libraries(
41 SDL2::SDL2main
42 SDL2::SDL2test
43 SDL2::SDL2-static
44 GL
45 pspvram
46 pspvfpu
47 pspdisplay
48 pspgu
49 pspge
50 pspaudio
51 pspctrl
52 psphprm
53 psppower
54 )

#include <pspkernel.h>
#include <pspdebug.h>
#include <SDL2/SDL.h>

/_ Define the module info section _/
PSP_MODULE_INFO("SDL2", 0, 1, 1);

/_ Define the main thread's attribute value (optional) _/
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int main(int argc, char \*argv[])

# 链接 SDL2
```
## 编写跨平台代码
在编写跨平台程序时，我们希望部分代码根据目标平台的不同选择是否忽略。

在代码上体现为不同平台代码使用不同的`#ifdef`/`#ifndef`包裹

例如：`SDL2`

### GCC 预定义的宏

你是 Linux 系统，那么 GNUC 会给你宏 `linux`,`**linux`,`**linux**`三个宏中的一个。

如果你是安卓系统，那么就会给 ANDROID,`**ANDROID**`宏中的一个。 

[所以跨平台就是根据这些 GNUC 给出的宏来判断的。](https://visualgmq.gitee.io/2019/07/28/%E5%90%84%E7%A7%8D%E5%BA%93%E6%98%AF%E5%A6%82%E4%BD%95%E5%81%9A%E5%88%B0%E8%B7%A8%E5%B9%B3%E5%8F%B0%E7%9A%84/)

### 查看psp-gcc预定义的宏
```C
psp@pspserver:~/pspdev/psp/share$ psp-gcc -E -dM - < /dev/null
// ......
#define __PSP__ 1
#define __DQ_FBIT__ 63
#define _MIPS_ARCH_ALLEGREX 1
// ......
#define R3000 1
// ......
#define _MIPS_ISA _MIPS_ISA_MIPS2
// ......
#define _PSP 1
// ......
#define __INT_MAX__ 0x7fffffff
#define mips 1
// ......
#define __mips__ 1
// ......
#define PSP 1
```