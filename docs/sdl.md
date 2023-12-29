# Work with SDL2

SDL2（Simple DirectMedia Layer） 是一个低层次跨平台图形开发库，常用于游戏开发。
适配 PSP、PS2 等多种游戏终端。

它为图形界面开发者提供了一套统一的API，而在底层针对不同平台有不同的具体代码实现。
# 链接

> 注意：没看清这一块会导致无穷无尽的链接报错，请认真阅读

显然，SDL2给PSP开发者提供的API内部都基于 `pspsdk` 中的函数实现，在链接的语境下就是引用了许多外部的符号。。SDL2想要调用这些不属于它自身的函数，就必须链接`pspsdk`中编译好的含有相应函数实现部分的可重定位文件。

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

SDL 使用了一种技巧，通过宏定义将用户的 main 函数重命名为 SDL_main，然后提供自己的 main 函数。这样，当你在你的代码中写 main 函数时，预处理器实际上会将其重命名为 SDL_main

下面是一段来自 pspdev 官网的示例代码
```

```

假如我们不加-SDLmain，只加-SDL2 直接编译，会报错`undefined refernce to 'main'`
这是十分奇怪的，因为我们我们显然定义了 main 函数。

这就要谈到 SDL 这个库的特性：在预处理时，SDL会通过宏定义将用户的 main 函数重命名为 SDL_main。这样，当你在你的代码中写 main 函数时，预处理器实际上会将其重命名为 SDL_main。此后 SDL 会重新实现新的 main 函数，在其中调用 SDL_main 并在前后运行添加额外的处理流程。

注意到示例代码里不再有各种线程的注册和模块信息的指定，这正是因为 SDL 重新为我们定义的 main 函数能够帮我们做到这一点。
而自建 main 函数这一过程的实现位于 SDL_main 库

下面是摘录自 SDL_main.h 的一段注释

```c
#elif defined(__PSP__)
/* On PSP SDL provides a main function that sets the module info,
   activates the GPU and starts the thread required to be able to exit
   the software.

   If you provide this yourself, you may define SDL_MAIN_HANDLED
 */
#define SDL_MAIN_AVAILABLE
```
```c
#if defined(SDL_MAIN_NEEDED) || defined(SDL_MAIN_AVAILABLE) || defined(SDL_MAIN_USE_CALLBACKS)
#define main    SDL_main
#endif
```
下面是一段 SDL_main.c 的代码
> 2023年12月24日注：
> SDL2已经被遗弃，现通行的是SDL3。
> SDL_main.c已不复存在，取而代之的是一些更加模块化的设计。

> The SDLmain library has been removed, it's been entirely replaced by SDL_main.h.

由于`SDL_main.h`已经在`SDL.h`中被包含，故示例代码中仅`#include <SDL.h>`。

需要 include SDL_main(在 SDL.h 中已经包含)
需要链接 SDL_main

# Working with SDL3
出人意料的是，在Github上SDL仓库的main分支已经被SDL3替代。不过这样更好，让我们有机会得以尝试没有资料下的探索，并以此检验自己的理解情况。

## 下载仓库
```bash
git clone https://github.com/libsdl-org/SDL
cd SDL
```

>Building
>To build SDL library for the PSP, make sure you have the latest PSPDev status and run:
```bash
cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=$PSPDEV/psp/share/pspdev.cmake
cmake --build build
cmake --install build
```

## 步骤

```bash
cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=$PSPDEV/psp/share/pspdev.cmake
```
用pspdev.cmake提供的参数使用pspdev工具链构建

>会安装到哪里？
`psp@pspserver:~/SDL/build$ cat cmake_install.cmake`
```
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/psp/pspdev/psp")
endif()
```

```
psp@pspserver:~/pspdev/psp/include$ ll
total 2048
drwxr-xr-x 33 psp psp   4096 Dec 24 14:28 ./
drwxr-xr-x  9 psp psp   4096 Dec  2 09:25 ../
drwxr-xr-x  2 psp psp   4096 Dec  2 09:25 SDL/
drwxr-xr-x  2 psp psp   4096 Dec  2 09:25 SDL2/
drwxrwxr-x  2 psp psp   4096 Dec 24 14:28 SDL3/
```

```
psp@pspserver:~/pspdev/psp/lib$ ll
total 47884
drwxr-xr-x  7 psp psp    4096 Dec 24 14:28 ./
drwxr-xr-x  9 psp psp    4096 Dec  2 09:25 ../
-rw-r--r--  1 psp psp  373754 Dec  2 08:58 libSDL.a
-rw-r--r--  1 psp psp 2142412 Dec  2 08:58 libSDL2.a
-rw-r--r--  1 psp psp   76952 Dec  2 08:59 libSDL2_gfx.a
-rw-r--r--  1 psp psp  228316 Dec  2 08:59 libSDL2_image.a
-rw-r--r--  1 psp psp  287696 Dec  2 08:59 libSDL2_mixer.a
-rw-r--r--  1 psp psp   77684 Dec  2 08:59 libSDL2_ttf.a
-rw-r--r--  1 psp psp    2896 Dec  2 08:58 libSDL2main.a
-rw-r--r--  1 psp psp 1695386 Dec 24 14:25 libSDL3.a
-rw-r--r--  1 psp psp  136880 Dec 24 14:25 libSDL3_test.a
-rw-r--r--  1 psp psp   99226 Dec  2 08:59 libSDL_gfx.a
-rw-r--r--  1 psp psp   69128 Dec  2 08:59 libSDL_image.a
-rw-r--r--  1 psp psp  234946 Dec  2 08:59 libSDL_mixer.a
-rw-r--r--  1 psp psp   33122 Dec  2 08:59 libSDL_ttf.a
-rw-r--r--  1 psp psp    2820 Dec  2 08:58 libSDLmain.a
```

大量的宏被重命名，函数原型也被修改……
还好新名字也用宏告诉你了

在SDL3中，前面提到的令人费解的SDL2部分基本得到解决。
PSP的参数需要自己指定而可以不使用SDL_main提供的默认值
main函数不会使用宏进行强行替换，只是部分重要API的实现会采用依赖平台的函数。

给个自己测试出来的样例
```Makefile
TARGET = main
OBJS= main.o

LIBDIR  =
LIBS = -lSDL3 -lGL -lGLU -lglut -lz \
         -lpspvfpu -lpsphprm -lpspsdk -lpspctrl -lpspumd -lpsprtc -lpsppower -lpspgum -lpspgu -lpspaudiolib -lpspaudio -lpsphttp -lpspssl -lpspwlan \
         -lpspnet_adhocmatching -lpspnet_adhoc -lpspnet_adhocctl -lm -lpspvram

EXTRA_TARGETS   = EBOOT.PBP
PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
```

```C
#include <pspkernel.h>
#include <SDL3/SDL.h>
/* Define the module info section */
PSP_MODULE_INFO("HelloSDL", 0, 1, 1);
/* Define the main thread's attribute value (optional) */
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD);

    SDL_Window * window = SDL_CreateWindow(
        "window",
        480,
        272,
        0
    );

    SDL_Renderer * renderer = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED);

    SDL_FRect square = {216, 96, 34, 64}; 

    int running = 1;
    SDL_Event event;
    while (running) { 
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    running = 0;
                    break;
                case SDL_EVENT_GAMEPAD_ADDED:
                    SDL_OpenGamepad(event.gdevice.which);
                    break;
                case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
                    if(event.gbutton.button == SDL_GAMEPAD_BUTTON_START)
                        running = 0;
                    break;
            }
        }

        // Clear the screen
        SDL_RenderClear(renderer);

        // Draw a red square
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &square);

        // Draw everything on a white background
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderPresent(renderer);
    }

    return 0;
}
```


[SDL3关于main函数的讨论](https://wiki.libsdl.org/SDL3/README/main-functions)

# working with c++
-lc++std