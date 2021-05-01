/* Copyright (C) 2015 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2002 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2000 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
#include <errno.h>
#include <io.h>
#include <termios.h>
#include <libc/bss.h>
#include <libc/ttyprvt.h>
#include <libc/farptrgs.h>
#include <libc/getdinfo.h>
#include <dpmi.h>
#include <go32.h>

/* NEC98 and DOSV port: */
/* modified by lpproj, 2021 */
#include <libc/_machine.h>
#include "../common/_termios.h"

void
__libc_termios_flush_keybuf_ibmpc (void)
{
  while (1) {
    __dpmi_regs r;
    r.h.ah = 0x11;
    __dpmi_int(0x16, &r);
    if (r.x.flags & 0x40) /* if Zero flag is set, no key is waiting */
      break;
    r.h.ah = 0x10;
    __dpmi_int(0x16, &r);
  }
}

