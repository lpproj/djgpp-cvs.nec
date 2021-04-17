#include <pc.h>
#include <dpmi.h>
#include <stdlib.h>
#include <libc/_machine.h>
#include "../common/_kb.h"

int
__libc_kb_kbhit_dos(void)
{
  __dpmi_regs r;

  r.h.ah = 0x0b;
  __dpmi_int(0x21, &r);

  return r.h.al != 0;
}

