/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <go32.h>
#include <dpmi.h>
#include <libc/farptrgs.h>
#include <conio.h>
/* NEC98 and DOSV port: */
/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include "../sc.h"
#include "../common/_co80.h"

void
ScreenPutChar_ibmpc(int _ch, int _attr, int _x, int _y)
{
  int cols = ScreenCols();
  int rows = ScreenRows();
  if (_x >= 0 && _x < cols && _y >= 0 && _y < rows)
  {
    unsigned ofs = co80 + (_y * cols + _x) * 2;
    _farpokew(dossel, ofs, ((_attr & 0xff) << 8) | (_ch & 0xff));
    /* todo: support DBCS (kanji) on DOS/V */
    _conio_refreshvirtualscreen_ibmpc(_y, _x, 1);
  }
}
