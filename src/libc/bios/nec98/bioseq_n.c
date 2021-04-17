/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <bios.h>
#include <dpmi.h>
#include <go32.h>
#include <pc.h>
#include <libc/farptrgs.h>
#include <libc/_machine.h>
#include "../common/_bios.h"

int biosequip_nec98(void)
{
  int flag = 0x4025;

  /* 2nd CCU */
  outportb(0x23f, 0);
  if ( inportb(0x23f) == 0x00 )
    flag |= 0x0400;
  else
    flag |= 0x0200;

  /* FPU */
  if ( _farpeekb(_dos_ds, (__crt0_machine_subtype == MACHINE_SUBTYPE_NEC98_HIRES) ? 0xE3FEA : 0xA3FEA) & 0x18 )
    flag |= 0x0002;

  return flag;
}

