# 播放视频的可能性？
## FFmpeg
在Github上存在着利用了少量PSP汇编代码优化的的FFmpeg实现（ffmpeg-psp），目前尚不清楚其优化程度，而API亦过于老旧。

## Build FFmpeg from source
不论是FFmpeg-psp还是如今每日构建的ffmpeg，想要取出其特定功能我们还得手动构建

+ 协助控制编译的./configure 文件（修改让他支持我的psp参数：也就是什么都不做，因为不支持平台-specific的code）
+ 支持什么，参数怎么改？
    + install的位置
    + cross-compile
+ 我们需要的库 `libav?`

+ 没有硬解行不行？
目前版本号显示可以做到

## PSP 内置的 `libMpeg` 有多大能力?
+ 加了硬解行不行？
能解码何种视频流？
Github: `pmfplayer`/`pmfplayer-lib`


## 用SDL渲染视频流？

## 视频流与音频流的同步？？
+ ffmpeg
+ pmfplayer?