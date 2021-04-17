/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <conio.h>
#include <dpmi.h>
#include <go32.h>
#include <libc/_machine.h>
#include "../common/_co80.h"
#include "../sc.h"

void
ScreenClear_nec98(void)
{
  __dpmi_regs r;
  r.h.ah = 0x16;
  r.h.dh = _conio_attr_ibmpc_to_nec98(ScreenAttrib);
  r.h.dl = ' ';
  r.h.bh = 0;
  __dpmi_int(0x18, &r);
}

