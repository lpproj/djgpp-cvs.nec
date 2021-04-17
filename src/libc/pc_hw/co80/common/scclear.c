/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
/* modified by lpproj, 2021 */
#include <dpmi.h>
#include <go32.h>
#include <conio.h>
#include "../sc.h"
#include "../common/_co80.h"

void	
ScreenClear(void)
{
  __libc_co80_pf_ScreenClear();
}
