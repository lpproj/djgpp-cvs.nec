#include <pc.h>
#include "../common/_kb.h"

int
getxkey(void)
{
  return __libc_kb_pf_getxkey();
}

