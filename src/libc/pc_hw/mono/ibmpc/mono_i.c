/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
/* NEC98 and DOSV port: */
/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <stdarg.h>
#include <stdio.h>
#include <sys/mono.h>
#include <libc/farptrgs.h>
#include <go32.h>

#include <libc/_machine.h>
#include "../common/_mono.h"

#define TOPROW 5*160
#define BOTROW 20*160
#define LIN(r,c) (0xb0000 + (r)*160 + (c)*2)

void _mono_clear_ibmpc(void)
{
  for (__libc_mono_screen_ofs=TOPROW; __libc_mono_screen_ofs < BOTROW; __libc_mono_screen_ofs += 2)
    _farpokew(_dos_ds, 0xb0000 + __libc_mono_screen_ofs, 0x0720);
  __libc_mono_screen_ofs = TOPROW;
  __libc_mono_screen_is_initted = 1;
}

void _mono_putc_ibmpc(int ch)
{
  if (!__libc_mono_screen_is_initted)
    _mono_clear_ibmpc();
  if (__libc_mono_screen_ofs >= BOTROW)
  {
    int i;
    for (i=TOPROW; i<BOTROW-160; i+=2)
      _farpokew(_dos_ds, 0xb0000+i, _farpeekw(_dos_ds, 0xb0000+i+160));
    for (; i<BOTROW; i+=2)
      _farpokew(_dos_ds, 0xb0000+i, 0x0720);
    __libc_mono_screen_ofs -= 160;
  }
  switch (ch)
  {
  case '\n':
    __libc_mono_screen_ofs += 160;
    break;
  case '\r':
    __libc_mono_screen_ofs -= __libc_mono_screen_ofs % 160;
    break;
  case '\b':
    __libc_mono_screen_ofs -= 2;
    break;
  default:
    _farpokew(_dos_ds, 0xb0000 + __libc_mono_screen_ofs, 0x0700 | (ch & 0xff));
    __libc_mono_screen_ofs += 2;
    break;
  }
}
