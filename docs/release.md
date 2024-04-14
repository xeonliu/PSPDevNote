# UMD Image File

## Dir structure

## EBOOT.BIN / BOOT.BIN
+ EBOOT.BIN: 加密的prx文件

+ BOOT.BIN: 未加密的prx文件

### Decrypte EBOOT.BIN

+ `PRXdecrypter 2.7a`   
    
    (Runs on a PSP or PSVita)  

+ `PPSSPP` 

    (Check on Setting -> Tools -> Developer tools -> Dump decrypted EBOOT.BIN on game boot, and run the game. Then you will get decrypted EBOOT.BIN under (memorystick)/PSP/SYSTEM/DUMP with a name like (game-id).bin.)

生成未加密的PRX文件

### UMD GEN Relink EBOOT.PBP
Maybe we can use an encrypted prx file to load an unencrypted one?

Can we do that on OFW?

## CSO
> ISO Compressor


