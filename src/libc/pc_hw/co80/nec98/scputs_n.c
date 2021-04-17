/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
/* NEC98 and DOSV port: */
/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <conio.h>
#include <dpmi.h>
#include <go32.h>
#include <libc/farptrgs.h>
#include <sys/segments.h>
#include <string.h>
#include "../sc.h"
#include <libc/_machine.h>
#include "../common/_co80.h"

void
ScreenPutString_nec98(const char *_ch, int _attr, int _x, int _y)
{
  int cols = ScreenCols_nec98();
  int rows = ScreenRows_nec98();

  if (_x >= 0 && _x < cols && _y >= 0 && _y < rows)
  {
    unsigned cscrn = cols * rows;
    unsigned cpos = _y * cols + _x;
    unsigned ccnt = strlen(_ch);
    unsigned scptr = co80 + cpos * 2;
    unsigned i;
    unsigned attrn = _conio_attr_ibmpc_to_nec98((unsigned char)(_attr & 0xff));

    if (cpos + ccnt > cscrn)
      ccnt = cscrn - cpos;
    _farsetsel(dossel);
    /* todo: support DBCS (kanji) */
    for( i=0; i<ccnt; i++ )
    {
      _farnspokew(scptr, (unsigned char)(_ch[i]));
      _farnspokew(scptr + 0x2000, attrn);
      scptr += 2;
    }
  }
}
