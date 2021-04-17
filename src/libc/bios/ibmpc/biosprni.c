#include <bios.h>
#include <dpmi.h>
#include "../common/_bios.h"

#define biosprint(c,b,p) biosprint_ibmpc(c,b,p)
#include "../biosprin.c"

