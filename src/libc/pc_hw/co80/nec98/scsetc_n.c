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

void
ScreenSetCursor_nec98(int _row, int _col)
{
  __dpmi_regs regs;

  regs.h.ah = 0x03;
  regs.h.cl = 0x10;
  regs.h.dh = _row;
  regs.h.dl = _col;
  __dpmi_int(0xdc, &regs);
}
