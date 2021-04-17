/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
/* NEC98 and DOSV port: */
/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <stdarg.h>
#include <stdio.h>
#include <sys/mono.h>
#include <libc/farptrgs.h>
#include <go32.h>

#include <pc.h>
#include <libc/_machine.h>
#include "../common/_mono.h"

int ScreenRows_nec98(void);
int ScreenCols_nec98(void);

static int cols_nec98 = 80;
static int rows_nec98 = 24;
static int bytes_nec98 = 80 * 24 * 2;

void _mono_clear_nec98(void)
{
  int i;

  cols_nec98 = ScreenCols_nec98();
  rows_nec98 = ScreenRows_nec98();
  bytes_nec98 = cols_nec98 * rows_nec98 * 2;
  for (i = 0; i < bytes_nec98; i += 2) {
    _farpokew(_dos_ds, ScreenPrimary + i, 0x0000);
    _farpokew(_dos_ds, ScreenPrimary + i + 0x2000, 0x00e1);
  }
  __libc_mono_screen_ofs = 0;
  __libc_mono_screen_is_initted = 1;
}

void _mono_putc_nec98(int ch)
{
  int colbs = cols_nec98 * 2;
  int i;

  if (!__libc_mono_screen_is_initted)
    _mono_clear_nec98();
  if (__libc_mono_screen_ofs >= bytes_nec98) {
    for (i = 0; i < bytes_nec98 - colbs; i += 2)
      _farpokew(_dos_ds, ScreenPrimary + i,
        _farpeekw(_dos_ds, ScreenPrimary + i + colbs));
    for (; i < bytes_nec98; i+=2)
      _farpokew(_dos_ds, ScreenPrimary + i, 0x0020);
    __libc_mono_screen_ofs -= colbs;
  }
  switch (ch) {
  case '\n':
    __libc_mono_screen_ofs += colbs;
    break;
  case '\r':
    __libc_mono_screen_ofs -= __libc_mono_screen_ofs % (colbs);
    break;
  case '\b':
    __libc_mono_screen_ofs -= 2;
    break;
  default:
    _farpokew(_dos_ds, ScreenPrimary + __libc_mono_screen_ofs, (ch & 0xff));
    __libc_mono_screen_ofs += 2;
    break;
  }
}

