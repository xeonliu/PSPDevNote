# Makefile Example

编写好代码之后，还需要编译汇编链接才能生成 PSP 可执行的文件。PSPDev 提供了一套完整的 GNU 工具链供编译使用。

## 推荐阅读

> 【【技术杂谈】C 编译体系】 https://www.bilibili.com/video/BV1J14y1D7Sw/?share_source=copy_web&vd_source=21fc443ef57d30a122c546adda50cd40

> 【其他】make到底干了些什么 http://bbs.chinaemu.org/read-htm-tid-86754-uid-12451.html

## EBOOT.PBP的构建流程
1. 编译生成.o可重定位目标程序（自己负责）。指定变量`OBJS`
2. 链接静态链接库（.a文件，在pspdev/psp/sdk/lib中）生成ELF文件。指定变量`LIBS`
	```Makefile linenums="1" hl_lines="2"
	$(TARGET).elf: $(OBJS) $(EXPORT_OBJ)
		$(LINK.c) $^ $(LIBS) -o $@
		$(FIXUP) $@
	```
3. 使用`psp-fixup-imports`修复ELF文件的导入表。
	```Makefile linenums="1" hl_lines="3"
	$(TARGET).elf: $(OBJS) $(EXPORT_OBJ)
		$(LINK.c) $^ $(LIBS) -o $@
		$(FIXUP) $@
	```
4.  生成PSP上的可执行文件。PSP支持ELF和PRX两种可执行文件格式。
	+ （选择1）使用psp-strip生成优化的ELF文件
		```Makefile
		$(STRIP) $(TARGET).elf -o $(TARGET)_strip.elf
		```
	+ （选择2）用psp-prxgen生成PRX文件。指定变量`BUILD_PRX` 
		```Makefile
		%.prx: %.elf
			psp-prxgen $< $@
		```
		+ 对于PRX文件，可以使用`PrxEncrypter`进行加密使其能在未经修改的PSP上运行。指定变量`ENCRYPT`
		```makefile
		ifeq ($(ENCRYPT), 1)
			- $(ENC) $(TARGET).prx $(TARGET).prx
		```
		!!! Hint
			PRX文件的生成依赖于特定的ELF文件。如果最终目标是生成PRX文件，则在第二步链接生成ELF文件时除了指定静态链接库还需要添加一些附加的指令。
			```Makefile
			LDFLAGS  := $(addprefix -L,$(LIBDIR)) -specs=$(PSPSDK)/lib/prxspecs -Wl,-q,-T$(PSPSDK)/lib/linkfile.prx $(LDFLAGS)
			```
5. 使用mksfo/mksfoex生成SFO信息文件。指定相关变量`SFOFLAGS` `PSP_EBOOT_TITLE`
	```makefile
	$(PSP_EBOOT_SFO): 
	$(MKSFO) $(SFOFLAGS) '$(PSP_EBOOT_TITLE)' $@
	```

	!!! Hint
		有关SFO文件格式，参考文件格式一页。	

		有关mksfo使用及源码解析，参考工具一页。

6. 使用pack-pbp将SFO文件、ELF/PRX文件和其他资源文件打包生成EBOOT.PBP。指定相关变量`PSP_EBOOT_SFO`、`PSP_EBOOT_ICON`、`PSP_EBOOT_ICON1`、`PSP_EBOOT_UNKPNG`、`PSP_EBOOT_PIC1`、`PSP_EBOOT_SND0`、`PSP_EBOOT_PSAR`
	```Makefile
	$(PACK_PBP) $(PSP_EBOOT) $(PSP_EBOOT_SFO) $(PSP_EBOOT_ICON)  \
		$(PSP_EBOOT_ICON1) $(PSP_EBOOT_UNKPNG) $(PSP_EBOOT_PIC1)  \
		$(PSP_EBOOT_SND0)  $(TARGET)_strip.elf $(PSP_EBOOT_PSAR)
	
	```
	
	!!! Hint
		有关PBP文件格式，参考文件格式一页。

		有关pack-pbp使用及源码解析，参考工具一页。

## HelloWorld示例中的Makefile


## PSPDEV提供的基础Makefile
位于`pspdev/psp/sdk/lib`基础的Makefile文件`build.mak`，通常会在自己的Makefile包含。
```makefile title="pspdev/psp/sdk/lib/build.mak"
# Note: The PSPSDK make variable must be defined before this file is included.
ifeq ($(PSPSDK),)
$(error $$(PSPSDK) is undefined.  Use "PSPSDK := $$(shell psp-config --pspsdk-path)" in your Makefile)
endif
```
使用前要求变量PSPSDK已经被定义。

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
其中`psp-strip`用于优化ELF文件大小，`mksfoex`用于生成`SFO`文件，`PrxEncrypter`用于加密`PRX`文件

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

LINK.o   = $(CC) $(LDFLAGS) $(TARGET_ARCH)
LINK.cc  = $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)
LINK.C   = $(LINK.cc)
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