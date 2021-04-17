#include <stdarg.h>
#include <stdio.h>
#include <sys/mono.h>
#include <libc/farptrgs.h>
#include <go32.h>

#include <stdlib.h>
#include <libc/_machine.h>
#include "_mono.h"

static void _mono_clear_setup(void);
static void _mono_putc_setup(int c);
void (*__libc_mono_of__mono_clear)(void) = _mono_clear_setup;
void (*__libc_mono_of__mono_putc)(int c) = _mono_putc_setup;

int __libc_mono_screen_is_initted = 0;
int __libc_mono_screen_ofs = 0;

static void _mono_setup(void)
{
  switch(__crt0_machine_type) {
#ifdef SUPPORT_IBMPC
    case MACHINE_TYPE_IBMPC:
      __libc_mono_of__mono_clear = _mono_clear_ibmpc;
      __libc_mono_of__mono_putc = _mono_putc_ibmpc;
      break;
#endif
#ifdef SUPPORT_NEC98
    case MACHINE_TYPE_NEC98:
      __libc_mono_of__mono_clear = _mono_clear_nec98;
      __libc_mono_of__mono_putc = _mono_putc_nec98;
      break;
#endif
    default:
      ABORT_UNSUPPORTED;
  }
}

static void _mono_clear_setup(void)
{
  _mono_setup();
  __libc_mono_of__mono_clear();
}
void _mono_clear(void)
{
  __libc_mono_of__mono_clear();
}

static void _mono_putc_setup(int c)
{
  _mono_setup();
  __libc_mono_of__mono_putc(c);
}
void _mono_putc(int c)
{
  __libc_mono_of__mono_putc(c);
}

