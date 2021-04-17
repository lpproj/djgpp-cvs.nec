#include <bios.h>
#include <stdlib.h>
#include <libc/_machine.h>
#include "_bios.h"

static int bioscom_setup(int cmd, char data, int port);
static int (*__libc_bios_pf_bioscom)(int, char, int) = bioscom_setup;

static int bioscom_setup(int cmd, char data, int port)
{
  switch(__crt0_machine_type) {
#ifdef SUPPORT_IBMPC
    case MACHINE_TYPE_IBMPC:
      __libc_bios_pf_bioscom = bioscom_ibmpc;
      break;
#endif
#ifdef SUPPORT_NEC98
    case MACHINE_TYPE_NEC98:
      __libc_bios_pf_bioscom = bioscom_nec98;
      break;
#endif
    default:
      ABORT_UNSUPPORTED;
  }
  return __libc_bios_pf_bioscom(cmd, data, port);
}

int bioscom(int cmd, char data, int port)
{
  return __libc_bios_pf_bioscom(cmd, data, port);
}

