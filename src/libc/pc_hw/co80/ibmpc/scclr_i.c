#include <dpmi.h>
#include <conio.h>
#include "../sc.h"
#include <libc/_machine.h>
#include "../common/_co80.h"

void
ScreenClear_ibmpc(void)
{
  __dpmi_regs regs;

  regs.d.eax = 0x0600;
  regs.d.ecx = 0;
  regs.h.bh = ScreenAttrib;
  regs.h.dl = ScreenCols_ibmpc() - 1;
  regs.h.dh = ScreenRows() - 1; /* ScreenRows_ibmpc() - 1; */
  __dpmi_int(0x10, &regs);
}
