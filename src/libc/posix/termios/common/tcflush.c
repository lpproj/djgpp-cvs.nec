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
__libc_termios_flush_keybuf_dos (void)
{
  while (1) {
    __dpmi_regs r;
    r.x.ax = 0x0c06;        /* flush buffer, and direct console input */
    r.h.dl = 0xff;
    __dpmi_int(0x21, &r);
    if (r.x.flags & 0x40)   /* check ZF=1 (no keyboard input) */
      break;
  }
}

int
tcflush (int handle, int which)
{
  short devmod;

  /* initialize */
  if (__libc_termios_hook_common_count != __bss_count)
    __libc_termios_init ();

  /* check handle whether valid or not */
  devmod = _get_dev_info (handle);
  if (devmod == -1)
    return -1;

  /* check console */
  if (! (devmod & _DEV_CDEV) || ! (devmod & (_DEV_STDIN|_DEV_STDOUT)))
    {
      errno = ENOTTY;
      return -1;
    }

  /* flush ... */
  switch (which)
    {
    case TCIFLUSH:
    case TCIOFLUSH:
      /* clear input queue */
      if (__libc_tty_p->t_count != 0)
	{
	  __libc_tty_p->t_count = 0;
	  __libc_tty_p->t_rpos = __libc_tty_p->t_top;
	  __libc_tty_p->t_wpos = __libc_tty_p->t_top;
	}
      /* now empty any keystrokes left in the keyboard buffer */
      __libc_termios_pf_flush_keybuf();
      break;
    case TCOFLUSH:
      /* nothing */
      break;
    default:
      errno = EINVAL;
      return -1;
    }

  return 0;
}
