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

#include <stdlib.h>
#include <libc/_machine.h>
#include "../common/_timer.h"

static uclock_t uclock_setup(void);
uclock_t (*__libc_timer_pf_uclock)(void) = uclock_setup;

static uclock_t uclock_setup(void)
{
  switch(__crt0_machine_type) {
#ifdef SUPPORT_IBMPC
    case MACHINE_TYPE_IBMPC:
      __libc_timer_pf_uclock = uclock_ibmpc;
      break;
#endif
#ifdef SUPPORT_NEC98
    case MACHINE_TYPE_NEC98:
      __libc_timer_pf_uclock = uclock_nec98;
      break;
#endif
    default:
      ABORT_UNSUPPORTED;
  }

  return __libc_timer_pf_uclock();
}

uclock_t
uclock(void)
{
  return __libc_timer_pf_uclock();
}
