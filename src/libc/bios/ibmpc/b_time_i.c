#include <bios.h>
#include <dpmi.h>
#include "../common/_bios.h"

#define _bios_timeofday _bios_timeofday_ibmpc
#include "../b_time.c"

