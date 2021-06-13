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

int __djgpp_nec98_itimer_interval = 5;  /* 10ms * 5 = by 50ms */

extern int __djgpp_nec98_itimer_enabled;
extern int __djgpp_nec98_itimer_interval_count;

void __libc_itimer_handle_itimer_nec98(void)
{
  __djgpp_nec98_itimer_enabled = 1;
  __djgpp_nec98_itimer_interval_count = __djgpp_nec98_itimer_interval;
}

void __libc_itimer_unhandle_itimer_nec98(void)
{
  __djgpp_nec98_itimer_enabled = 0;
}

