/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
/* NEC98 and DOSV port: */
/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <conio.h>
#include <libc/stubs.h>
#include <dpmi.h>
#include <go32.h>
#include <libc/farptrgs.h>
#include <sys/segments.h>
#include <dos.h>
#include "../sc.h"
#include "../common/_co80.h"

void
ScreenVisualBell_ibmpc(void)
{
  unsigned sccnt = ScreenRows_ibmpc() * ScreenCols_ibmpc();
  int _nblinks = 2;

  _farsetsel(dossel);
  while (_nblinks--)
  {
    unsigned sp = co80;
    int i = sccnt;
    do {
      _farnspokew(sp, _farnspeekw(sp) ^ 0x7f00);
      sp += 2;
    } while (--i);
    _conio_refreshvirtualscreen_ibmpc(0, 0, sccnt);
    delay(100);
  }
}
