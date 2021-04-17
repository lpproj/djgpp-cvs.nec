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
ScreenRetrieve_nec98(void *_virtual_screen)
{
  unsigned char *vscptr = _virtual_screen;
  unsigned scptr = co80;
  unsigned sccnt = ScreenRows_nec98() * ScreenCols_nec98();

  /* todo: support DBCS (kanji) */
  _farsetsel(dossel);
  while ( sccnt-- )
  {
    *vscptr = _farnspeekb(scptr);
    vscptr[1] = _conio_attr_nec98_to_ibmpc(_farnspeekb(scptr + 0x2000));
    scptr += 2;
    vscptr += 2;
  }
}
