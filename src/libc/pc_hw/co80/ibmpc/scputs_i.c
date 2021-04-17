/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
/* NEC98 and DOSV port: */
/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <go32.h>
#include <dpmi.h>
#include <libc/farptrgs.h>
#include <conio.h>
#include <string.h>
#include "../sc.h"
#include "../common/_co80.h"

void
ScreenPutString_ibmpc(const char *_ch, int _attr, int _x, int _y)
{
  int cols = ScreenCols();
  int rows = ScreenRows();

  if (_x >= 0 && _x < cols && _y >= 0 && _y < rows)
  {
    unsigned cscrn = cols * rows;
    unsigned cpos = _y * cols + _x;
    unsigned ccnt = strlen(_ch);
    unsigned scptr = co80 + cpos * 2;
    unsigned i;

    if (cpos + ccnt > cscrn)
      ccnt = cscrn - cpos;
    _farsetsel(dossel);
    for( i=0; i<ccnt; i++ )
    {
      _farnspokew(scptr, _attr | (unsigned char)(_ch[i]));
      scptr += 2;
    }
    if (ccnt > 0)
      _conio_refreshvirtualscreen_ibmpc(_y, _x, ccnt);
  }
}
