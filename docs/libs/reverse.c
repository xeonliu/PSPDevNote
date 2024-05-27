/**
 * @brief This file is a reversed version of TPU's libfont.prx (fontfunk) library
 * Based on the libfont.prx binary, with reference to hz86/mgspw, a locolization plugin for Metal Gear Solid: Peace Walker
 */


// The Error Code definitions.

// https://github.com/uofw/uofw/blob/master/include/common/errors.h#L286
#define SCE_ERROR_KERNEL_LIBRARY_IS_NOT_LINKED 0x8002013A

// https://www.psdevwiki.com/vita/Error_Codes
#define SCE_FONT_ERROR_FILEOPEN 0x80460005
#define SCE_FONT_ERROR_FILECLOSE 0x80460006
#define SCE_FONT_ERROR_FILEREAD 0x80460007
#define SCE_FONT_ERROR_FILESEEK 0x80460008

PSP_MODULE_INFO("fontfuck", 0x0006, 1, 1);

int fuck_thread() {
    printf("Fontfuck Start!\n")
    int status;
    SceUID modid = sceKernelLoadModule("disc0:/PSP_GAME/USRDIR/oldfont.prx", 0, NULL);
    if(modid>0) {
        sceKernelStartModule(modid,0,NULL,&status,0);
    }
    sceKernelExitDeleteThread(0);
    return 0;
}

int module_start(int argc, char** argv)
{
    SceUID thid;
    thid = sceKernelCreateThread("fontfuck",fuck_thread,0x19,0x800,0,NULL);
    if(thid>0){
      sceKernelStartThread(thid, argc, argv);
    }
    return 0;
}

// strlen函数，乐
void sceFontNewLib(int param_1,undefined4 param_2)
{
  int iVar1;
  
  if (*(int *)(param_1 + 0x14) == 0) {
    *(undefined4 *)(param_1 + 0x14) = 0x2d4;
    *(undefined4 *)(param_1 + 0x18) = 0x2a0;
    *(undefined4 *)(param_1 + 0x1c) = 0x21c;
    *(undefined4 *)(param_1 + 0x20) = 0x1e0;
  }
  while ((iVar1 = sceFontNewLib(param_1,param_2)) == SCE_ERROR_KERNEL_LIBRARY_IS_NOT_LINKED) {
    sceKernelDelayThread(200000);
  }
  return;
}

static void *my_open(void *pdata, char *filename, int *error)
{
	SceUID fd = sceIoOpen(filename, PSP_O_RDONLY, 0);
	if(fd < 0) {*error = SCE_FONT_ERROR_FILEOPEN; return 0;}
	*error = 0; return (void *)fd;
}


static int my_close(void *pdata, void *fileid)
{
	return sceIoClose((SceUID)fileid) < 0 ? SCE_FONT_ERROR_FILECLOSE : 0;
}

static int my_read(void *pdata, void *fileid, void *pbuf, int byte, int unit, int *error)
{
	int count = byte * unit;
	int retv = sceIoRead((SceUID)fileid, pbuf, count);
	if(retv < count) {*error = SCE_FONT_ERROR_FILEREAD; return 0;}
	*error = 0; return unit;
}

static int my_seek(void *pdata, void *fileid, int offset)
{
	return sceIoLseek32((SceUID)fileid, offset, PSP_SEEK_SET) < 0 ? SCE_FONT_ERROR_FILESEEK : 0;
}