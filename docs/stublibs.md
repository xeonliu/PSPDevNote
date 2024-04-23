# Stub Libraries
> 推荐阅读
>
> `uofw` Github wiki https://github.com/uofw/uofw/wiki
>
> PSP Modules, Exports, Imports and Patches https://uofw.github.io/upspd/docs/
>
> `uofw` Document
>
> `pspsdk/src/samples/prx/`


当我们之前链接第三方库时，都是直接与是真正包含代码的库链接。

现在我们希望在程序运行时动态地载入其他模块，依然可以使用静态链接，不过链接的是只包含函数接口和其空实现的存根库(`Stub/Resident Library`)。通过PSPSDK提供给我们的加载模块的函数，我们可以实现模块运行时的加载。

> Multiple programs can be loaded at the same time in PSP™ memory.
>
> Use other modules in your own module Dynamically.

## 编写可被其他模块动态加载的PRX模块
> A PRX-format module can be used as a resident library. A resident library provides some of its functions to another module.

编写导出表，将导出表嵌入PRX模块。

1. 撰写PRX程序的C代码
不写main函数，写module_start()和module_stop()函数
注意：请于module_start()函数中加一行`printf()`函数调用，否则在由ELF文件生成PRX文件时会出现缺少.lib.stub段的问题(WHY?)。
2. 编写导出表，指定哪些函数可被其他模块引用
导出格式。
必须导出：
自定义导出：
据说不推荐导出变量。
3. 对导出表使用`psp-build-exports -b`生成C代码 
    ### build.mak
    ```makefile
    %.c: %.exp
        psp-build-exports -b $< > $@
    ```
4. 编译1、3中的C代码得到可重定位目标文件，链接后生成PRX文件
    ### build.mak
    ```makefile
    # 将3中C代码对应的目标文件设为构建目标
    ifdef PRX_EXPORTS
    EXPORT_OBJ=$(patsubst %.exp,%.o,$(PRX_EXPORTS))
    EXTRA_CLEAN += $(EXPORT_OBJ)
    ```
    ```makefile
    # 编译链接
    $(TARGET).elf: $(OBJS) $(EXPORT_OBJ)
	$(LINK.c) $^ $(LIBS) -o $@
	$(FIXUP) $@
    ```
    注意，链接时需要指定`LDFLAGS = -nostartfiles`以避免出现`main`函数符号未定义的问题。
    **至此，导出表已嵌入PRX文件，接下来的步骤是为将要使用该PRX文件的模块准备的**
5. 对导出表使用`psp-build-exports -k`生成存根.S文件（module stubs / import table）
6. （可选）编译.S文件至.o文件并通过ar即得到存根库

## 在程序中动态加载PRX模块
+ 写代码时：包含存根库的头文件
+ 链接时：编译存根.S文件并与之链接 / 链接存根库
`OBJS`中指定.S->.o的文件名



https://uofw.github.io/upspd/docs/SilverSpring_Blog/my.malloc.us/silverspring/category/nids/index.html