#include <dpmi.h>
#include <pc.h>
#include <stdio.h>
#include "../common/_kb.h"

#define getkey getkey_ibmpc
#include "../getkey.c"

