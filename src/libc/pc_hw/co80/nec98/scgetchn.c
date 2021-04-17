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
ScreenGetChar_nec98_raw(int *_ch, int *_attr, int _x, int _y)
{
  int cols = ScreenCols_nec98();
  int rows = ScreenRows_nec98();
  if (_x >= 0 && _x < cols && _y >= 0 && _y < rows)
  {
    unsigned ofs = co80 + (_y * cols + _x) * 2;
    unsigned sc = _farpeekw(dossel, ofs);
    unsigned sa = _farpeekw(dossel, ofs + 0x2000);
    /* todo: support DBCS (kanji) */
    if (_ch) *_ch = sc & 0xff;
    if (_attr) *_attr = sa;
  }
}

void
ScreenGetChar_nec98(int *_ch, int *_attr, int _x, int _y)
{
  int attr_n;
  ScreenGetChar_nec98_raw(_ch, &attr_n, _x, _y);
  if (_attr) *_attr = _conio_attr_nec98_to_ibmpc((unsigned)attr_n);
}

