/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
/* NEC98 and DOSV port: */
/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <conio.h>
#include <dpmi.h>
#include <go32.h>
#include <libc/farptrgs.h>
#include <sys/segments.h>
#include <dos.h>
#include "../sc.h"
#include <libc/_machine.h>
#include "../common/_co80.h"

void
ScreenVisualBell_nec98(void)
{
  unsigned sccnt = ScreenRows_ibmpc() * ScreenCols_ibmpc();
  int _nblinks = 2;

  _farsetsel(dossel);
  while (_nblinks--)
  {
    unsigned sp = co80 + 0x2000;
    int i = sccnt;
    do {
      _farnspokew(sp, _farnspeekw(sp) ^ 0x0004);
      sp += 2;
    } while (--i);
    delay(100);
  }
}
