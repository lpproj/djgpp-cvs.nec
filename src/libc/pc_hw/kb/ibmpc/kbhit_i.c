#include <dpmi.h>
#include <pc.h>
#include <stdio.h>
#include "../common/_kb.h"

#define kbhit kbhit_ibmpc
#include "../kbhit.c"

