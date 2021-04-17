#include <bios.h>
#include <stdlib.h>
#include <libc/_machine.h>
#include "_bios.h"

static int bioskey_setup(int cmd);
static int (*__libc_bios_pf_bioskey)(int) = bioskey_setup;

static int bioskey_setup(int cmd)
{
  switch(__crt0_machine_type) {
#ifdef SUPPORT_IBMPC
    case MACHINE_TYPE_IBMPC:
      __libc_bios_pf_bioskey = bioskey_ibmpc;
      break;
#endif
#ifdef SUPPORT_NEC98
    case MACHINE_TYPE_NEC98:
      __libc_bios_pf_bioskey = bioskey_nec98;
      break;
#endif
    default:
      ABORT_UNSUPPORTED;
  }
  return __libc_bios_pf_bioskey(cmd);
}

int
bioskey(int cmd)
{
  return __libc_bios_pf_bioskey(cmd);
}