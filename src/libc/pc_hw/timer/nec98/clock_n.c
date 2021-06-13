/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
/* NEC98 and DOSV port: */
/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <time.h>
#include <go32.h>
#include <libc/farptrgs.h>
#include <libc/bss.h>

#include <pc.h>
#include <libc/_machine.h>
#include "../common/_timer.h"

#if 1
extern unsigned long long __djgpp_timer_tick;
clock_t clock_nec98( void )
{
  return (clock_t)(__djgpp_timer_tick * CLOCKS_PER_SEC) / 100U;
}
#else
static int clock_bss = -1;

clock_t clock_nec98( void )
{
/*[エミュレーションに関する問題点]*****************************
    ・タイムスタンパ低分解能使用	 307200/256Hz = 1200Hz
    ・カレンダも使用するので時間がかかる(T_T)
 **************************************************************/
  static time_t   base_sec = 0;
  static unsigned base_tic = 0;
  time_t   rv_sec;
  unsigned rv_tic, diff_sec, diff_tic;

  if (clock_bss != __bss_count) {
    clock_bss = __bss_count;
    base_sec = 0;
    base_tic = 0;
  }

  rv_sec = time(NULL);
  rv_tic = inportw(0x5E);
  if (base_sec == 0L) {
    base_sec = rv_sec;
    base_tic = rv_tic;
  }

  diff_sec = rv_sec - base_sec;
  if ( __crt0_machine_subtype == MACHINE_SUBTYPE_NEC98_HIRES || _farpeekb(_dos_ds, 0x45B) & 0x04 ) {
    diff_tic = rv_tic - base_tic;
    if ( rv_tic < base_tic )
      diff_tic += 0x10000;
    if ( diff_tic > 0x8000 )
      diff_sec -= 8;
    else
      diff_sec += 8;
    diff_tic += (unsigned)(diff_sec * 1200 / 0x10000) * 0x10000;
    return (clock_t)(diff_tic*CLOCKS_PER_SEC/1200);
  } else
    return (clock_t)(diff_sec*CLOCKS_PER_SEC);
}
#endif

