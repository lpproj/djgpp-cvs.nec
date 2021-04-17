#include <time.h>
#include <go32.h>
#include <libc/farptrgs.h>
#include <libc/bss.h>
#include "../common/_timer.h"

#define clock clock_ibmpc
#include "../clock.c"

