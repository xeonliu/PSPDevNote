# MIPS汇编
PSP的CPU采用MIPS架构，32位。ISA与规范略有变化

> 推荐阅读
> 
> + 《CS:APP》 Chapter 3
> + [uOFW Wiki](https://github.com/uofw/uofw/wiki/MIPS)：
> MIPS, Logical Blocks, Functions 三节
> + Module Tutorial

# psp-gcc
`psp-gcc`是为生成PSP可执行文件而修改过的`gcc`，位于`pspdev/bin`文件夹下

不同架构、不同系统上的可执行文件格式不同

使用`psp-gcc -v`可以显示详细信息

```shell
psp@pspserver:~$ psp-gcc -v
Using built-in specs.
COLLECT_GCC=psp-gcc
Target: psp
gcc version 11.2.0 (GCC)
```
# Decompiler
这里我们使用`IDA Pro` / `Ghidra` / `prxtool` 对文件进行反汇编，并对生成的汇编代码进行研究，
或者可以使用`PPSSPP`的调试功能进行断点查看。

## Example

```C
void mult2(int* a,int *b, int *c){
        *c = *a**b;
}
```
TODO：应该使用a0,a1等表示寄存器。
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
