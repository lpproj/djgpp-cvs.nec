/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
/* NEC98 and DOSV port: */
/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <unistd.h>
#include <go32.h>
#include <libc/farptrgs.h>
#include <libc/bss.h>

#include <time.h>
#include <libc/_machine.h>
#include "../common/_unistd.h"

static int pid_count = -1;
static pid_t my_pid;

pid_t
getpid(void)
{
  if (pid_count != __bss_count)
  {
    pid_count = __bss_count;
    switch(__crt0_machine_type) {
#ifdef SUPPORT_NEC98
      case MACHINE_TYPE_NEC98:
        my_pid = (pid_t)time(NULL);
        break;
#endif
#ifdef SUPPORT_IBMPC
      case MACHINE_TYPE_IBMPC:
        /* fallthrough */
#endif
      default:
        my_pid = _farpeekw(_dos_ds, 0x46c);
        break;
    }
    my_pid &= 0x3fff;
    my_pid |= 0x1000;
  }

  return my_pid;
}
