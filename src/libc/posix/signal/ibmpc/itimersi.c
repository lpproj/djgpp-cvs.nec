/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 Charles Sandmann (sandmann@clio.rice.edu)
   setitimer implmentation - used for profiling and alarm
   BUGS: ONLY ONE AT A TIME, first pass code
   This software may be freely distributed, no warranty.

   Changed to work with SIGALRM & SIGPROF by Tom Demmer.
   Gotchas:
     - It relies on uclock(), which does not work under Windows 3.X
       and sometimes under Windows 9X.
     - It screws up debuggers compiled with v2.02 or earlier, since
       debugging support before v2.03 couldn't pass signals to
       debugged programs.
     (Both of the above were true for the old version, too.)
*/
/* NEC98 and DOSV port: */
/* modified by lpproj, 2021 */

#include <libc/stubs.h>
#include <sys/time.h>
#include <errno.h>
#include <dpmi.h>
#include <signal.h>
#include <go32.h>

#include <time.h>
#include <libc/_machine.h>
#include "../common/_itimer.h"

void __libc_itimer_handle_itimer_ibmpc(void)
{
  __dpmi_paddr int_timer;

  __dpmi_get_protected_mode_interrupt_vector(__djgpp_timer_hwint, &__djgpp_old_timer);
  int_timer.selector = _my_cs();
  int_timer.offset32 = (unsigned) &__djgpp_timer_hdlr;
  __dpmi_set_protected_mode_interrupt_vector(__djgpp_timer_hwint, &int_timer);
}

void __libc_itimer_unhandle_itimer_ibmpc(void)
{
  __dpmi_set_protected_mode_interrupt_vector(__djgpp_timer_hwint, &__djgpp_old_timer);
}

