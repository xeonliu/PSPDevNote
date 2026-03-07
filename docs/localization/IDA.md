# IDA Pro

使用 IDA Pro 逆向分析

- prxtool 用于生成`.idc`脚本，定义函数名
- 使用头文件生成函数定义

需要从[`psplibdoc`](https://github.com/pspdev/psplibdoc/)获取生成IDC所需的XML文件。

注意应先应用`IDC`脚本，后调整基地址。