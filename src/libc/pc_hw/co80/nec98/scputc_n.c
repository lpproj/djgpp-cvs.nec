/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
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
ScreenPutChar_nec98_raw(int _ch, int _attr, int _x, int _y)
{
  int cols = ScreenCols_nec98();
  int rows = ScreenRows_nec98();
  if (_x >= 0 && _x < cols && _y >= 0 && _y < rows)
  {
    unsigned ofs = co80 + (_y * cols + _x) * 2;
    /* todo: support DBCS (kanji) */
    _farpokew(dossel, ofs, _ch & 0xffff);
    _farpokeb(dossel, ofs + 0x2000, (unsigned char)_attr);
  }
}

void
ScreenPutChar_nec98(int _ch, int _attr, int _x, int _y)
{
  ScreenPutChar_nec98_raw(_ch & 0xff, _conio_attr_ibmpc_to_nec98((unsigned char)(_attr & 0xff)), _x, _y);
}

