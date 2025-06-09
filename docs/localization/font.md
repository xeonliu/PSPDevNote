# Customize Font
通常PSP游戏默认使用系统自带的`jpn0.pgf`（位于`flash0`）渲染日文字体。而该字体缺少大量汉字。

PSP的libfont支持UCS2定义的65536个字符，因而可以生成覆盖足量字符的字体。

使用`TPU`编写的`pgftool`可以做到这一点。

推荐将`ttf2pgf`与`mixpgf`一起使用，保证字符外沿不会过宽。

`PPSSPP`当前版本对字体限制较为迷惑，需要按要求修改。