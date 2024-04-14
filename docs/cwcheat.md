# Patching Using CW Cheat

金手指（CW Cheat）是一种用于表示内存修改的文本格式。

用于替换内存中数值/机器代码，或向内存中添加数据/机器代码。

在PPSSPP支持此种格式后得到推广。

通过在PSP中安装支持此类格式的PRX插件(如`CWCheat PSP`)，可以在程序运行过程中实时加载`CW Cheat`文件并依据其指令修改内存值。对于PPSSPP，则可以直接在PPSSPP中设置并进行加载。

本质上是内存修改器。

## 使用方法
### [`CWCheat PSP`](https://www.gamebrew.org/wiki/CWCheat_PSP)
#### Adding cheat codes
Cheat codes can be added by editing cheat.db and cheatpops.db (for PS1 games) in the seplugins/cwcheats/ folder:
#### Load cheat codes
Activate the cheat menu with the game running, select the cheat that you would like to enable or disable then return to the game.

Select (hold 3 seconds) - Activate plugin

Cross - Select

Circle - Cancel

Triangle - Enable all cheats

### `PPSSPP`

## 基本语法


https://datacrystal.romhacking.net/wiki/CwCheat

```
_S ULJM-05011 -> Game ID.
_G Puzzle Bobble Pocket [JP] -> Game title.
_C0 999999999 Points -> Code name (_C0 to disable; _C1 to enable).
_L 0x20566E30 0x3B9AC9FF -> Code line (often has more than 1 line).
```

> 参考：
> 
> + https://github.com/rezual/nge_2_re/blob/master/ULJS00064.ini
> 
> + https://raw.githubusercontent.com/Saramagrean/CWCheat-Database-Plus-/master/cheat.db