# Format Specification
在PSP开发中涉及的文件格式
> 推荐阅读：
>> Yet another PSP Documentation [Chapter 26: File Formats](https://gigawiz.github.io/yapspd/html_chapters_split/chap26.html) (2006)

# PRX
+ Encrypted
+ Unencrypted

## File section
Tool: `psp-objdump`

`psp-objdump -x ./ULJS00064_USER_MAIN.BIN `
```
psp@pspserver:~/code/test$ psp-objdump -x ./ULJS00064_USER_MAIN.BIN 

./ULJS00064_USER_MAIN.BIN:     file format elf32-littlemips
./ULJS00064_USER_MAIN.BIN
architecture: mips:allegrex, flags 0x00000000:

start address 0x00000128

Program Header:
    LOAD off    0x00000080 vaddr 0x00000000 paddr 0x001aeeec align 2**6
         filesz 0x001da9e0 memsz 0x001da9e0 flags rwx
    LOAD off    0x001daa80 vaddr 0x001daa00 paddr 0x00000000 align 2**6
         filesz 0x000793fc memsz 0x0020cbb8 flags rw-
private flags = 10a23001: [abi=EABI32] [mips2] [not 32bitmode] [noreorder]

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .init         00000024  00000000  001aeeec  00000080  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .rel.init     00000010  00000000  00000000  00254584  2**2
                  CONTENTS, READONLY
  2 .text         001ae74c  00000040  001aef2c  000000c0  2**6
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  3 .rel.text     000a4ba8  00000000  00000000  00254594  2**2
                  CONTENTS, READONLY
  4 .fini         0000001c  001ae78c  0035d678  001ae80c  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  5 .rel.fini     00000008  00000000  00000000  002f913c  2**2
                  CONTENTS, READONLY
  6 .sceStub.text 00000528  001ae7a8  0035d694  001ae828  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  7 .lib.ent.top  00000004  001aecd0  0035dbbc  001aed50  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  8 .lib.ent      00000010  001aecd4  0035dbc0  001aed54  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  9 .rel.lib.ent  00000008  00000000  00000000  002f9144  2**2
                  CONTENTS, READONLY
 10 .lib.ent.btm  00000004  001aece4  0035dbd0  001aed64  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 11 .lib.stub.top 00000004  001aece8  0035dbd4  001aed68  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 12 .lib.stub     0000017c  001aecec  0035dbd8  001aed6c  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 13 .rel.lib.stub 000001c8  00000000  00000000  002f914c  2**2
                  CONTENTS, READONLY
 14 .lib.stub.btm 00000004  001aee68  0035dd54  001aeee8  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 15 .rodata.sceModuleInfo 00000034  001aee6c  0035dd58  001aeeec  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 16 .rel.rodata.sceModuleInfo 00000028  00000000  00000000  002f9314  2**2
                  CONTENTS, READONLY
 17 .rodata.sceResident 00000190  001aeea0  0035dd8c  001aef20  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 18 .rel.rodata.sceResident 00000028  00000000  00000000  002f933c  2**2
                  CONTENTS, READONLY
 19 .rodata.sceNid 00000294  001af030  0035df1c  001af0b0  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 20 .ctors        00000008  001af2c4  0035e1b0  001af344  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 21 .dtors        00000008  001af2cc  0035e1b8  001af34c  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 22 .jcr          00000004  001af2d4  0035e1c0  001af354  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 23 .eh_frame     0000130c  001af2d8  0035e1c4  001af358  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 24 .rel.eh_frame 00000450  00000000  00000000  002f9364  2**2
                  CONTENTS, READONLY
 25 .gcc_except_table 00000054  001b05e4  0035f4d0  001b0664  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 26 .rodata       0002a3a0  001b0640  0035f52c  001b06c0  2**6
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 27 .rel.rodata   0000c900  00000000  00000000  002f97b4  2**2
                  CONTENTS, READONLY
 28 .data         000793fc  001daa00  00000000  001daa80  2**4
                  CONTENTS, ALLOC, LOAD, DATA
 29 .rel.data     0001fd88  00000000  00000000  003060b4  2**2
                  CONTENTS, READONLY
 30 .sbss         00000000  00253e00  00079400  00253e7c  2**2
                  ALLOC
 31 .bss          001937b8  00253e00  00079400  00253e7c  2**6
                  ALLOC
 32 .comment      00009b06  00000000  00000000  00325e3c  2**0
                  CONTENTS, READONLY
SYMBOL TABLE:
no symbols
```

## SceModuleInfo
```
psp@pspserver:~/code/test$ psp-objdump -s -j .rodata.sceModuleInfo ./ULJS00064_USER_MAIN.BIN 

./ULJS00064_USER_MAIN.BIN:     file format elf32-littlemips

Contents of section .rodata.sceModuleInfo:
 1aee6c 00000101 55534552 5f4d4149 4e000000  ....USER_MAIN...
 1aee7c 00000000 00000000 00000000 00000000  ................
 1aee8c f0130800 d4ec1a00 e4ec1a00 ecec1a00  ................
 1aee9c 68ee1a00                             h...      
```

