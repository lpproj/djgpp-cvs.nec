#include <pc.h>
#include "../common/_kb.h"

int
getkey(void)
{
  return __libc_kb_pf_getkey();
}

