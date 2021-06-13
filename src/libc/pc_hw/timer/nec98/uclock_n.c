/* Copyright (C) 2003 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
/* NEC98 and DOSV port: */
/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <libc/stubs.h>
#include <time.h>
#include <errno.h>
#include <pc.h>
#include <libc/farptrgs.h>
#include <go32.h>
#include <dpmi.h>
#include <libc/bss.h>
#include <dos.h>
#include <signal.h>
#include <setjmp.h>
#include <sys/exceptn.h>

#include <libc/_machine.h>
#include "../common/_timer.h"

#if 0
static int uclock_bss = -1;

uclock_t uclock_nec98( void )
{
/*[エミュレーションに関する問題点]*****************************
    ・タイムスタンパ高分解能使用	 307200Hz(0x4B000Hz)
    ・カレンダも使用するので時間がかかる(T_T)
 **************************************************************/
  static time_t   base_sec = 0;
  static unsigned base_tic = 0;
  time_t   rv_sec;
  unsigned rv_tic, ticL, ticH, diff_sec;
  uclock_t diff_tic;

  if (uclock_bss != __bss_count) {
    uclock_bss = __bss_count;
    base_sec = 0;
    base_tic = 0;
  }

  if (__djgpp_nec98_info.has32ndSecTimer)
    return uclock_nec98_32ndsectimer();

  rv_sec = time(NULL);
  ticH   = inportw(0x5C);
  ticL   = inportw(0x5E) & 0xff00;
  rv_tic = (ticL << 8) + ticH;
  if (base_sec == 0L) {
    base_sec = rv_sec;
    base_tic = rv_tic;
  }

  diff_sec = rv_sec - base_sec;
  if ( __crt0_machine_subtype == MACHINE_SUBTYPE_NEC98_HIRES || _farpeekb(_dos_ds, 0x45B) & 0x04 ) {
    ticL = rv_tic - base_tic;
    if ( rv_tic < base_tic )
      ticL += 0x1000000;
    if ( ticL > 0x800000 )
      diff_sec -= 8;
    else
      diff_sec += 8;
    diff_tic = (uclock_t)(diff_sec * 0x4B / 0x1000) * 0x1000000 + ticL;
    return (uclock_t)(diff_tic*UCLOCKS_PER_SEC/0x4B000);
  } else
    return (uclock_t)(diff_sec*UCLOCKS_PER_SEC);
}
#endif

extern unsigned long long __djgpp_timer_tick;
uclock_t
uclock_nec98_pit10ms(void)
{
  return (uclock_t)(__djgpp_timer_tick * UCLOCKS_PER_SEC) / 100U;
}

extern unsigned long long __djgpp_nec98_get_artic64(void);
uclock_t uclock_nec98_artic( void )
{
  return (uclock_t)(__djgpp_nec98_get_artic64() * UCLOCKS_PER_SEC) / 307200U;
}

#if 0
uclock_t
uclock_nec98_hitimer(void)
{
  const uclock_t SEC32ND_PER_DAY = 24 * 60 * 60 * 32;
  static int uclock_hitimer_bss = -1;
  static unsigned day_prev, day_count;
  unsigned s0, s, d;
  uclock_t sec32nd;

  s0 = _farpeekl(_dos_ds, 0x04f1); /* 0000:04F1 ... 04F3h */
  s = s0 & 0x3fffff;
  d = (s0 >> 22) & 3;
  if (uclock_hitimer_bss != __bss_count) {
    uclock_hitimer_bss = __bss_count;
    day_prev = d;
    day_count = 0;
  }
  if (day_prev != d) {
    day_count += (day_prev < d) ? (d - day_prev) : ((day_prev + 4) - d);
    day_prev = d;
  }
  sec32nd = SEC32ND_PER_DAY * day_count + s;
  return (sec32nd * UCLOCKS_PER_SEC) / 32U;
}
#endif
