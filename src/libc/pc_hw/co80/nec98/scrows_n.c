/* NEC98 and DOSV port: */
/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <conio.h>
#include <dpmi.h>
#include <go32.h>
#include <libc/farptrgs.h>
#include <sys/segments.h>
#include "../sc.h"
#include <libc/_machine.h>
#include "../common/_co80.h"

int
ScreenRows_nec98(void)
{
#if 0
  if ( __crt0_machine_subtype == MACHINE_SUBTYPE_NEC98_HIRES ) {
    /* todo: make certain that the actual API exists */
    __dpmi_regs r;
    r.x.ax = 0x25ff;
    __dpmi_int(0x18, &r);
    return r.h.ah - 1;
  } else
#endif
  return _farpeekb(dossel, 0x600 + 0x112) + 1;
}
