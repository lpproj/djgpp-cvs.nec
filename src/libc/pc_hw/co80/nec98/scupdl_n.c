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
ScreenUpdateLine_nec98(const void *_virtual_screen_line, int _row)
{
  /* todo: support DBCS (kanji) */
  if (_row >= 0 && _row < ScreenRows_nec98())
  {
    const unsigned char *vscptr = _virtual_screen_line;
    unsigned sccnt = ScreenCols_nec98();
    unsigned scptr = co80 + sccnt * _row * 2;
    _farsetsel(dossel);
    while ( sccnt-- )
    {
      _farnspokew(scptr, *vscptr);
      _farnspokew(scptr + 0x2000, _conio_attr_ibmpc_to_nec98(vscptr[1]));
      scptr += 2;
      vscptr += 2;
    }
  }
}
