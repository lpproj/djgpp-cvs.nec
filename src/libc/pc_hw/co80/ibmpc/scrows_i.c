/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
/* modified by lpproj, 2021 */
#include <go32.h>
#include <dpmi.h>
#include <libc/farptrgs.h>
#include <conio.h>
#include "../sc.h"
#include "../common/_co80.h"

int
ScreenRows_ibmpc(void)
{
  int ymax = _farpeekb(dossel, 0x484);
  /* workaround for early Adapters (MDA/CGA) */
  return (ymax <= 0 || ymax == 255) ? 25 : (ymax + 1);
}

