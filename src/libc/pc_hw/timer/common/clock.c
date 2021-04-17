#include <time.h>

#include <stdlib.h>
#include <libc/_machine.h>
#include "../common/_timer.h"

static clock_t clock_setup(void);
clock_t (*__libc_timer_pf_clock)(void) = clock_setup;

static clock_t clock_setup(void)
{
  switch(__crt0_machine_type) {
#ifdef SUPPORT_IBMPC
    case MACHINE_TYPE_IBMPC:
      __libc_timer_pf_clock = clock_ibmpc;
      break;
#endif
#ifdef SUPPORT_NEC98
    case MACHINE_TYPE_NEC98:
      __libc_timer_pf_clock = clock_nec98;
      break;
#endif
    default:
      ABORT_UNSUPPORTED;
  }

  return __libc_timer_pf_clock();
}


clock_t
clock(void)
{
  return __libc_timer_pf_clock();
}