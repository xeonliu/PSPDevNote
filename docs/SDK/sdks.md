# Cooperating with different SDKs

`PSPSDK`是民间爱好者自发通过逆向工程研究得到的SDK。围绕着这套SDK，已经移植出多种库。`PSPSDK`随着PSP破解的发展不断迭代，从以前的`M33`格式到后来的格式。

目前，官方的SDK已经泄露在互联网上，通过在互联网档案馆搜寻不难得到。随着官方SDK的泄露，随之而来的是大量的官方文档，它们对于PSP的运作机理进行了很好的补充。作为初学者阅读这些文档有助于我们更好地使用`PSPSDK`。

事实上，现在`PSPSDK`的功能和配套软件在某些方面已经远远超过了官方SDK。但是`PSPSDK`少收录了部分系统库（系统调用）的函数，亦缺乏许多函数参数的解释。另外，官方SDK还收录了索尼开发的的部分第三方库。这些库能够使我们的程序中UI等的设计更接近当时PSP官方出品的程序。