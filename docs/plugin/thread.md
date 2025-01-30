# 线程（Thread）
## 创建线程
```C
int mythread(SceSize args , void ∗argp)
{ 
    /∗ Do something ∗/ 
}
```
```C
SceUID thid ;
/∗ Create a user thread ∗/
thid = sceKernelCreateThread(”MyThread” , // Name
    mythread,// Entry Point
    20, // Priority
    16384, // Stack Size
    0, // Attribute
    NULL);

/∗ Start thread with arguments ∗/
sceKernelStartThread (thid , args , argp)
```

+ `
SceUID sceKernelCreateThread(const char * 	name, SceKernelThreadEntry entry,int 	initPriority, int stackSize, SceUInt attr,SceKernelThreadOptParam *option)
`

## 线程参数

`PSP_THREAD_ATTR_VFPU`
**Enable VFPU access for the thread.**

`PSP_THREAD_ATTR_USER`
Start the thread in user mode (done automatically if the thread creating it is in user mode).

`PSP_THREAD_ATTR_USBWLAN`
Thread is part of the USB/WLAN API.

`PSP_THREAD_ATTR_VSH`
Thread is part of the VSH API.

`PSP_THREAD_ATTR_SCRATCH_SRAM`
Allow using scratchpad memory for a thread, NOT USABLE ON V1.0.

`PSP_THREAD_ATTR_NO_FILLSTACK`
Disables filling the stack with 0xFF on creation.

`PSP_THREAD_ATTR_CLEAR_STACK`
Clear the stack when the thread is deleted.

# 线程安全性

+ Threads have a privilege level which indicates if they can run in kernel or user mode. This allows protection of kernel memory from user applications.  
+ When creating a new thread, you cannot escalate its privilege level.  
+ Thread primitives **inherit permissions** of the thread which created them.  
+ You cannot enumerate or use thread primitives without the same privilege.  
+ During **syscall transition**, a **separately allocated stack** is used to prevent attacks or data leakage.  
+ All kernel functions which take pointer arguments check them based on the thread's privilege.