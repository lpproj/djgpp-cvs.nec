#include <time.h>
#include <go32.h>
#include <libc/_machine.h>
#include "../common/_c_time.h"

static unsigned long rawclock_setup(void);
static unsigned long (*__libc_compat_pf_rawclock)(void) = rawclock_setup;

static unsigned long rawclock_setup(void)
{
  switch(__crt0_machine_type) {
#ifdef SUPPORT_IBMPC
    case MACHINE_TYPE_IBMPC:
      __libc_compat_pf_rawclock = rawclock_ibmpc;
      break;
#endif
#ifdef SUPPORT_NEC98
    case MACHINE_TYPE_NEC98:
      __libc_compat_pf_rawclock = rawclock_nec98;
      break;
#endif
    default:
      ABORT_UNSUPPORTED;
  }
  return __libc_compat_pf_rawclock();
}

unsigned long
rawclock(void)
{
  return __libc_compat_pf_rawclock();
}

