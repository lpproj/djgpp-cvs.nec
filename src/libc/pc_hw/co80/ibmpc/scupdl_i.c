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
#include <string.h>
#include "../sc.h"
#include "../common/_co80.h"

void
ScreenUpdateLine_ibmpc(const void *_virtual_screen_line, int _row)
{
  unsigned ccnt = ScreenCols_ibmpc();

  if (_row >= 0 && _row < ScreenRows_ibmpc() && ccnt > 0)
  {
    unsigned ccnt2 = ccnt * 2;
    movedata(_my_ds(), (int)_virtual_screen_line, dossel, co80 + ccnt2 * _row , ccnt2);
    _conio_refreshvirtualscreen_ibmpc(_row, 0, ccnt);
  }
}
