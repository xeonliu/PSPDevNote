# 汉化相关

都是2010年前后，上个时代的资料了。现在的人应该用更现代的语言来表述。使用现代的工具链！

这篇文章写的太好了，我觉得没必要再多说什么了。
https://github.com/Bunkai9448/digipet_PSP/blob/main/RE_Guide.md

https://xiongonline.github.io/[%E8%BD%AC%E8%BD%BD][NDS]NDS%E6%B1%89%E5%8C%96%E5%B0%8F%E7%99%BD%E6%95%99%E7%A8%8B.html#top

https://www.romhacking.net/utilities/818/

https://bbs.chengyi.org/thread-111286-1-1.html

近似字符表：https://github.com/ultrapre/GBK_SJIS/blob/master/gbksjisTBL/README.md

SHIFTJIS表：http://www.rikai.com/library/kanjitables/kanji_codes.sjis.shtml

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