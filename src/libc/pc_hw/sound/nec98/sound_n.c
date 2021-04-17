/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
/* NEC98 and DOSV port: */
/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <go32.h>
#include <sys/farptr.h>
#include <pc.h>
#include "../common/_sound.h"

void sound_nec98(int freq)
{
  int scale;
  if (freq == 0) {
    outportb(0x37, 0x07);
    return;
  }
  if ( _farpeekb(_dos_ds, 0x00501) & 0x80 )
    scale = 100 * 0x4e00 / freq;
  else
    scale = 100 * 0x6000 / freq;
  outportb(0x3fdf, 0x76);
  outportb(0x3fdb, scale & 0xff);
  outportb(0x3fdb, scale >> 8);
  outportb(0x37, 0x06);
}

