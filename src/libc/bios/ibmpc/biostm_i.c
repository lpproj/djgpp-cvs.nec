#include <bios.h>
#include <dpmi.h>
#include "../common/_bios.h"

#define biostime(c,t) biostime_ibmpc(c,t)
#include "../biostime.c"

