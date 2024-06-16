# 程序加载
> http://uofw.github.io/upspd/docs/software/naked_psp.pdf
这部分可以看uofw里面手机的一份PSPSDK的PPT
restart and open
`sceKernelLoadModule`
`sceKernelStartModule`

manage prx

# Load&Execution Library.
Load&Execute A PRX/BOOT.BIN... from another Executable File

You can pass some arguments to the main function of the program you are about to execute.

```C
int sceKernelLoadExec (const char *file, struct SceKernelLoadExecParam *param);
```
The PSP will reboot and execute the file you have selected. The screen will gone blank for a while. But you seem to have some choice to keep the screen on during the reboot process, according to what the official document says.

# 地址空间

sceModuleInfo
内核如何管理Moudule


TN-HEN 6.20

Total Noob Homebrew Enabler OF 6.20(Can not load ISO on XMB)

Prometheus ISO Loader (liquidzigong)
-> Load ISO on XMB.

You can find videos & screenshots.

https://gbatemp.net/threads/liquidzigong-has-quit-the-psp-scene.267699/

https://baike.baidu.com/item/liquidzigong/6154040

http://news.17173.com/content/12172020/102020086.shtml

https://gamergen.com/actualites/liquidzigong-prometheus-quitte-scene-psp-fake-48302-1/amp

http://zerofuga0613.blog65.fc2.com/blog-entry-76.html

SCE_MODULE_ATTR_CANT_STOP = 0x0001
The module cannot stop (valid only when there is no stop entry). 
SCE_MODULE_ATTR_EXCLUSIVE_LOAD = 0x0002
The module cannot be loaded if a module having the same name has already been loaded. 
*SCE_MODULE_ATTR_EXCLUSIVE_START = 0x0004
The module cannot be started if a module having the same name has already been started. 
