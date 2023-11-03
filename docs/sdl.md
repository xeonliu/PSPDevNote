# Work with SDL2

SDL2（Simple DirectMedia Layer） 是一个低层次跨平台图形开发库，常用于游戏开发。
适配 PSP、PS2 等多种游戏终端

# 链接

注意：没看清这一块会导致无穷无尽的链接报错，请认真阅读
显然，SDL2 的实现中必然调用了许多 pspsdk 中的函数，在链接的语境下就是使用了许多外部的符号。

因此要使用 SDL2 库，在链接时不仅要链接 SDL2，还需要链接其依赖的其他 PSP 相关库。

从 pspdev 提供的 CMake 文件中可以看出一些链接时必须随附的库。

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
```

网络上一些示例项目的 Makefile 也指出了相关的库

```Makefile
LIBS = -lSDLmain -lSDL2 -lGL -lGLU -lglut -lz -lpspvfpu -lpsphprm -lpspsdk -lpspctrl -lpspumd -lpsprtc \
       -lpsppower -lpspgum -lpspgu -lpspaudiolib -lpspaudio -lpsphttp -lpspssl -lpspwlan \
	   -lpspnet_adhocmatching -lpspnet_adhoc -lpspnet_adhocctl -lm -lpspvram
```

具体哪些库是绝对必须的还有待研究。

# SDL 中的 main 函数

下面是一段来自 pspdev 官网的示例代码
假如我们不加-SDLmain，只加-SDL2 直接编译，会报错`undefined refernce to 'main'`
这是十分奇怪的，因为我们我们显然定义了 main 函数。

这就要谈到 SDL 这个库的特性：它能够自动将 main 函数转化成 SDL_main 函数。并预期实现新的 main 函数，在其中调用 SDL_main 并在前后运行添加额外的处理流程。

注意到示例代码里不再有各种线程的注册和模块信息的指定，这正是因为 SDL 重新为我们定义的 main 函数能够帮我们做到这一点。
自建 main 函数这一过程的实现位于 SDL_main 库

下面是摘录自 SDL_main.h 的一段注释

下面是一段 SDL_main.c 的代码

需要 include SDL_main(在 SDL.h 中已经包含)
需要链接 SDL_main
