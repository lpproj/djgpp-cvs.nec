#include <bios.h>
#include <dpmi.h>
#include "../common/_bios.h"

#define biosdisk(c,d,h,t,s,n,b) biosdisk_ibmpc(c,d,h,t,s,n,b)
#define _bios_disk(c,d) _bios_disk_ibmpc(c,d)
#include "../biosdisk.c"

