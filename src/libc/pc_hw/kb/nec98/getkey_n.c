/* Copyright (C) 1997 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
/* NEC98 and DOSV port: */
/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <pc.h>
#include <dpmi.h>
#include <go32.h>
#include <libc/_machine.h>
#include "../common/_kb.h"


int
getkey_nec98_raw(void)
{
  __dpmi_regs r;

  do {
    r.h.ah = 0;
    __dpmi_int(0x18, &r);
  } while ((r.d.eax & 0xffff) == 0xffff);

  return r.h.al ? r.h.al : r.h.ah;
}

int
getkey_nec98(void)
{
  __dpmi_regs r;

  do {
    r.h.ah = 0;
    __dpmi_int(0x18, &r);
  } while ((r.d.eax & 0xffff) == 0xffff);

  return __libc_kb_conv_scancode_nec98_to_ibmpc(r.h.ah, 0);
}
