#include <dos.h>
#include <stdlib.h>
#include <libc/_machine.h>
#include "_dos.h"

static void delay_setup(unsigned ms);
static void (*__libc_dos_pf_delay)(unsigned) = delay_setup;

void delay_setup(unsigned ms)
{
  switch(__crt0_machine_type) {
#ifdef SUPPORT_IBMPC
    case MACHINE_TYPE_IBMPC:
      __libc_dos_pf_delay = delay_ibmpc;
      break;
#endif
#ifdef SUPPORT_NEC98
    case MACHINE_TYPE_NEC98:
      __libc_dos_pf_delay = delay_nec98;
      break;
#endif
    default:
      ABORT_UNSUPPORTED;
  }
  __libc_dos_pf_delay(ms);
}

void delay(unsigned ms)
{
  __libc_dos_pf_delay(ms);
}

