/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2000 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
/*
 * tminit.c - initializer and main part of termios emulation.
 *   designed for DJGPP by Daisuke Aoyama <jack@st.rim.or.jp>
 *   special thanks to Ryo Shimizu
 */
/* NEC98 and DOSV port: */
/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <libc/stubs.h>
#include <stdio.h>
#include <termios.h>
#include <libc/bss.h>
#include <libc/file.h>
#include <libc/ttyprvt.h>

#include <libc/_machine.h>
#include "../common/_termios.h"

void (*__libc_termios_pf_flush_keybuf)(void) = __libc_termios_flush_keybuf_dos;

/* tty buffers */
struct tty __libc_tty_internal = TTYDEFAULT;
struct tty *__libc_tty_p = &__libc_tty_internal;

/* global only in the termios functions */
int __libc_termios_hook_common_count = -1;


/* static functions */
static void __libc_termios_fflushall(void);

/******************************************************************************/
/* initialize function ********************************************************/

static void
__libc_termios_fflushall(void)
{
  fflush(NULL);
}

void
__libc_termios_init(void)
{
  if (__libc_termios_hook_common_count != __bss_count)
  {
    __libc_termios_hook_common_count = __bss_count;

    /* flush all buffered streams */
    __libc_termios_fflushall ();

  switch(__crt0_machine_type) {
#ifdef SUPPORT_IBMPC
    case MACHINE_TYPE_IBMPC:
      __libc_termios_pf_flush_keybuf = __libc_termios_flush_keybuf_ibmpc;
      __libc_termios_init_read_ibmpc();
      __libc_termios_init_write_ibmpc();
      break;
#endif
#ifdef SUPPORT_NEC98
    case MACHINE_TYPE_NEC98:
# if 0
      __libc_termios_init_read_nec98();
      __libc_termios_init_write_nec98();
# endif
      break;
#endif
    default:
#if 0
      ABORT_UNSUPPORTED;
#endif
      break;
  }

    /* import parameters */
    /* __libc_tty_p = ...; */
  }
}
