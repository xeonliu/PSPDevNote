# Load&Execution Library.
Load&Execute A PRX/BOOT.BIN... from another Executable File

You can pass some arguments to the main function of the program you are about to execute.

```C
int sceKernelLoadExec (const char *file, struct SceKernelLoadExecParam *param);
```
The PSP will reboot and execute the file you have selected. The screen will gone blank for a while. But you seem to have some choice to keep the screen on during the reboot process, according to what the official document says.