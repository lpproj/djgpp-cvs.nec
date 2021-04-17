/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <bios.h>
#include <dpmi.h>
#include "../common/_bios.h"

long biostime_nec98(int cmd, long newtime)
{
  _bios_timeofday_nec98(cmd, (unsigned long *)&newtime);
  return newtime;
}

