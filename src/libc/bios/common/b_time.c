#include <bios.h>
#include <stdio.h>
#include <stdlib.h>
#include <libc/_machine.h>
#include "_bios.h"

static long biostime_setup(int cmd, long newtime);
static unsigned _bios_timeofday_setup(unsigned _cmd, unsigned long * _tv);
static long (*__libc_bios_pf_biostime)(int, long) = biostime_setup;
static unsigned (*__libc_bios_pf__bios_timeofday)(unsigned, unsigned long *) = _bios_timeofday_setup;

static void bios_time_setup(void)
{
  switch(__crt0_machine_type) {
#ifdef SUPPORT_IBMPC
    case MACHINE_TYPE_IBMPC:
      __libc_bios_pf__bios_timeofday = _bios_timeofday_ibmpc;
      __libc_bios_pf_biostime = biostime_ibmpc;
      break;
#endif
#ifdef SUPPORT_NEC98
    case MACHINE_TYPE_NEC98:
      __libc_bios_pf__bios_timeofday = _bios_timeofday_nec98;
      __libc_bios_pf_biostime = biostime_nec98;
      break;
#endif
    default:
      ABORT_UNSUPPORTED;
  }
}

static unsigned _bios_timeofday_setup(unsigned _cmd, unsigned long * _tv)
{
  bios_time_setup();
  return __libc_bios_pf__bios_timeofday(_cmd, _tv);
}

static long biostime_setup(int cmd, long newtime)
{
  bios_time_setup();
  return __libc_bios_pf_biostime(cmd, newtime);
}

long biostime(int cmd, long newtime)
{
  return __libc_bios_pf_biostime(cmd, newtime);
}

unsigned _bios_timeofday(unsigned _cmd, unsigned long * _tv)
{
  return __libc_bios_pf__bios_timeofday(_cmd, _tv);
}

