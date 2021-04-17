/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <bios.h>
#include <dpmi.h>
#include "../common/_bios.h"

int biosmemory_nec98(void)
{
  __dpmi_regs r;
  r.h.cl = 0x81;
  r.x.ax = 0x0000;
  __dpmi_int(0xdc, &r);
  return (int)(r.h.al) * 128;
}

