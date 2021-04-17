#include <dpmi.h>
#include <pc.h>
#include <stdio.h>
#include "../common/_kb.h"

#define __get_extended_key_string(c)  __get_extended_key_string_ibmpc(c)
#include "../getxkstr.c"
