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
