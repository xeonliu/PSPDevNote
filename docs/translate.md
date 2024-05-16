# Language Patch

这篇[Digivice Ver. Portable逆向工程教程](https://github.com/Bunkai9448/digipet_PSP/blob/main/RE_Guide.mdDigivice)写的太好了，涉及从逆向到发布的全过程与工具链，我觉得没必要再多说什么了。

> [digipet_PSP/RE_Guide.md](https://github.com/Bunkai9448/digipet_PSP/blob/main/RE_Guide.mdDigivice) 

# 汉化相关
## 传统汉化方法
> !!! Hint
> + 码表：即编码字节同字符的对应表。
> 
> + 字库：即储存字体字形图像的文件。

从二进制文件中检测潜在的字符串并生成<偏移量,字符数,字符内容>的一张表。通过这张表可以方便地对源文件进行替换和修改。

为了检测潜在的字符串，需要**编码字节与字符的对应表**，即“**码表**”

由于游戏通常采用[SHIFT-JIS](http://www.rikai.com/library/kanjitables/kanji_codes.sjis.shtml)编码，而该编码中汉字字符数量极为有限。

因而人们会**修改字体文件**，即“**字库**”，将原来的SHIFT-JIS字节序列对应的日文字符图像修改为其他的汉字字符图像。

此时字节序列同字符的对应关系已然发生改变。

因而又要重新写一张字符和编码字节的对应表，将翻译后的文本映射到新的字节序列上。

此时再对源二进制文件中的字符序列进行替换修改，便完成了文本的汉化过程。

> 参考资料
> 
> 码表相关
> 
>   + [【GBA、NDS、PSP】汉化基础教程——文字篇（三）by PGCG](https://bbs.chengyi.org/thread-111286-1-1.html)
>   + [NDS汉化小白教程 —— fengarea（A9VG汉化组）](https://xiongonline.github.io/[%E8%BD%AC%E8%BD%BD][NDS]NDS%E6%B1%89%E5%8C%96%E5%B0%8F%E7%99%BD%E6%95%99%E7%A8%8B.html#top) 第三话：字库码表篇•初步
>   + [游戏汉化教学贴-文本的导入导出基础篇](archive/bluekiller.htm)

### 理想情况
能够从二进制文件和资源文件中找到字符串和字库，直接进行修改。
在2010年左右，`WQSG`和`CrystalScript`用于处理码表、检测二进制文件中潜在的字符串，`CrystalTile`用于处理二级制文件中的图片和字库。
> 参考资料
> [CrystalTile](https://www.romhacking.net/utilities/818/)
### 无法获得字符串或字库
由于加密等问题，汉化工作者有时无法从二进制文件中寻找到字符串和字库。此时往往有以下两种方法。
#### 近似汉化
在无法获得字库时，使用SHIFT-JIS中已有的同汉字相近的日文字符作为对应汉字的替代。
> 近似字符表：https://github.com/ultrapre/GBK_SJIS/blob/master/gbksjisTBL/README.md
#### 内存汉化
无法在源文件中获得字符串或字库，但由于游戏运行时未加密的字符串和字库会加载到内存中，因而可以通过插件在游戏运行时对内存相应区域进行替换修改。
> [CG汉化组-幻想传说汉化测试插件](http://bbs1.chinaemu.org/read-htm-tid-80057-uid-71886.html)

## 具体实现
都是2010年前后，上个时代的资料了。现在的人应该用更现代的语言来表述。使用现代的工具链！
### 仅仅对文件修改
按照传统的汉化方法，只需要对资源文件和可执行文件中出现的代表字符串的`字节序列`和`字库`进行修改汉化工作便完成了。这一步的难点就在文件格式的解密上。

具体来讲，对于`PSP`汉化，可以通过`PPSSPP`的调试功能逐步分析文件格式。可以参考[《诡计对逻辑》汉化研究](https://pbteam.cn/posts/txl-hack/)
### 修改可执行文件/添加外部插件
对于一些需要使用内存汉化法或者调用的是系统字库的游戏，则需要进行程序逻辑的修改或者编写新的插件。也就是要进行反汇编、注入、劫持等操作。这更接近于本网站的主题。

https://uofw.github.io/upspd/docs/software/ModuleTutorialv1.pdf

patch prx on runtime？

z_un_088679c0
fcn.000639c0
a1: 0x8CB4
内部调用
...
z_un_088691b0
v0:0x539F
最终返回

8CB4-> 539F

08868dac调用sceFontGetCharInfo和sceFontGetCharGlyph
