/* base code by takas 1997-2000 for libc(AT/98) */
#include <bios.h>
#include <dpmi.h>
#include "../common/_bios.h"

unsigned _bios_timeofday_nec98(unsigned _cmd, unsigned long *_timeval)
{
  static unsigned long base_tics = 0;
  static unsigned int  base_time = 0, last_time = 0;
  unsigned int this_time = 0, midnight = 0;
  __dpmi_regs r;

  r.h.ah = 0x2C;
  __dpmi_int(0x21, &r);
  this_time = ((r.h.ch*60+r.h.cl)*60+r.h.dh)*100+r.h.dl;

  if ( this_time < last_time ) { /* midnight passed */
    base_tics = 0;
    base_time = 0;
    midnight  = 1;
  }
  last_time = this_time;

  if ( _cmd == _TIME_SETCLOCK ) { /* SET */
    base_tics = *_timeval;
    base_time = this_time;
  } else                          /* GET */
    *_timeval = (this_time-base_time)*91/500 + base_tics;

  return midnight;
}

