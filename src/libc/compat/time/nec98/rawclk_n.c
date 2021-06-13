/* Copyright (C) 1997 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
/* NEC98 port: */
/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <time.h>
#include <go32.h>
#include <libc/farptrgs.h>
#include <libc/_machine.h>
#include <bios.h>
#include "../common/_c_time.h"

unsigned _bios_timeofday_nec98(unsigned _cmd, unsigned long *_timeval);

unsigned long
rawclock_nec98_fallback(void)
{
  unsigned long ticks = 0;

  _bios_timeofday_nec98(_TIME_GETCLOCK, &ticks);
  return ticks;
}

static inline unsigned long _nec98_hitimer_raw(void)
{
  return _farpeekl(_dos_ds, 0x04f1) & 0x3fffff;
}

unsigned long
rawclock_nec98_hitimer_raw(void)
{
  return _nec98_hitimer_raw();
}

unsigned long
rawclock_nec98_hitimer(void)
{
  unsigned long s32nd = _nec98_hitimer_raw();
  /* s55ms = (s32nd * 100 / 32) * 91 / 500; */
  return (s32nd * 91) / (5 * 32);
}

