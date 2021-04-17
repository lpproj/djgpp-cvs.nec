#include <bios.h>
#include <stdlib.h>
#include <libc/_machine.h>
#include "_bios.h"

static int biosprint_setup(int cmd, int byte, int port);
static int (*__libc_bios_pf_biosprint)(int, int, int) = biosprint_setup;

static int biosprint_setup(int cmd, int byte, int port)
{
  switch(__crt0_machine_type) {
#ifdef SUPPORT_IBMPC
    case MACHINE_TYPE_IBMPC:
      __libc_bios_pf_biosprint = biosprint_ibmpc;
      break;
#endif
#ifdef SUPPORT_NEC98
    case MACHINE_TYPE_NEC98:
      __libc_bios_pf_biosprint = biosprint_nec98;
      break;
#endif
    default:
      ABORT_UNSUPPORTED;
  }
  return __libc_bios_pf_biosprint(cmd, byte, port);
}

int
biosprint(int cmd, int byte, int port)
{
  return __libc_bios_pf_biosprint(cmd, byte, port);
}
