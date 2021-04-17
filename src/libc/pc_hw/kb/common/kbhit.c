#include <pc.h>
#include "../common/_kb.h"

int
kbhit(void)
{
  return __libc_kb_pf_kbhit();
}

