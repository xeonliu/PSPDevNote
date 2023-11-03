# CPU架构
PSP采用MIPS架构，32位CPU，ISA与规范略有变化

> 推荐阅读
>
> MIPS ISA 手册
>
> CS:APP Chapter 3

# A Programmer's Perspective
与CS:APP宗旨类似，我们主要观察gcc编译后汇编文件的内容。

# psp-gcc
psp-gcc是为生成PSP可执行文件而修改过的gcc，在pspdev/bin文件夹下
gcc可以为不同的目标系统生成可执行文件，不同架构、不同系统上的可执行文件格式不同。
使用`psp-gcc -v`可以显示详细信息
```shell
psp@pspserver:~$ psp-gcc -v
Using built-in specs.
COLLECT_GCC=psp-gcc
Target: psp
gcc version 11.2.0 (GCC)
```
注意到其`target`为PSP
对比x86-64架构下Ubuntu的gcc，其target为`x86_64-linux-gnu`
```shell
psp@pspserver:~$ gcc -v
Using built-in specs.
COLLECT_GCC=gcc
Target: x86_64-linux-gnu
gcc version 11.4.0 (Ubuntu 11.4.0-1ubuntu1~22.04)
```

对于Windows下MSYS2的gcc
```shell
$ gcc -v
Using built-in specs.
COLLECT_GCC=C:\msys64\mingw64\bin\gcc.exe
Target: x86_64-w64-mingw32
gcc version 12.2.0 (Rev4, Built by MSYS2 project)
```

## Example

```C
void mult2(int* a,int *b, int *c){
        *c = *a**b;
}
```

```asm
<!-- a in $4 , b in $5, c in $6 -->
mult2:
        .frame  $sp,0,$31               # vars= 0, regs= 0/0, args= 0, gp= 0
        .mask   0x00000000,0
        .fmask  0x00000000,0
        .set    noreorder
        .set    nomacro
        lw      $3,0($4)
        lw      $2,0($5)
        mult    $3,$2
        mflo    $2
        sw      $2,0($6)
        jr      $31
        nop
```

SW $source register's address, offset($destination register's address)
The SW instruction stores data to a specified address on the data memory with a possible offset, from a
source register.

LW $destination register's address, offset($source register's address).

MIPS Multiply Unit
The multiply unit of MIPS contains two 32-bit registers called hi and lo. These are not general purpose registers. When two 32-bit operands are multiplied, hi and lo hold the 64 bits of the result. Bits 32 through 63 are in hi and bits 0 through 31 are in lo.

High and Low Registers
Here are the instructions that do this. The operands are contained in general-purpose registers.

mult    s,t        # hilo <— $s * $t   (two's comp operands)
multu   s,t        # hilo <— $s * $t   (unsigned operands)