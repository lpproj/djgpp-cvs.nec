#include <bios.h>
#include <dpmi.h>
#include <libc/_machine.h>
#include "_bios.h"

int
biosmemory(void)
{
  int rval = 0;

  switch(__crt0_machine_type)
  {
#if defined SUPPORT_IBMPC
    case MACHINE_TYPE_IBMPC:
      rval = biosmemory_ibmpc();
      break;
#endif
#if defined SUPPORT_NEC98
    case MACHINE_TYPE_NEC98:
      rval = biosmemory_nec98();
      break;
#endif
    default:
#if 0
      ABORT_UNSUPPORTED;
#endif
      break;
  }

  return rval;
}
