#include <pc.h>
#include <dpmi.h>
#include <stdlib.h>
#include <libc/_machine.h>
#include "../common/_kb.h"

static int getkey_setup(void);
static int getxkey_setup(void);
static int kbhit_setup(void);
#if 0
static const unsigned char *__get_extended_key_string_setup(int xkey_code);
#endif

int (*__libc_kb_pf_getkey)(void) = getkey_setup;
int (*__libc_kb_pf_getxkey)(void) = getxkey_setup;
int (*__libc_kb_pf_kbhit)(void) = kbhit_setup;


static void _kb_setup(void)
{
  switch(__crt0_machine_type) {
#ifdef SUPPORT_IBMPC
    case MACHINE_TYPE_IBMPC:
      __libc_kb_pf_getkey = getkey_ibmpc;
      __libc_kb_pf_getxkey = getxkey_ibmpc;
      __libc_kb_pf_kbhit = kbhit_ibmpc;
      break;
#endif
#ifdef SUPPORT_NEC98
    case MACHINE_TYPE_NEC98:
      __libc_kb_pf_getkey = getkey_nec98;
      __libc_kb_pf_getxkey = getkey_nec98;      /* getkey_nec98 */
      __libc_kb_pf_kbhit = kbhit_nec98;
      break;
#endif
    default:
      ABORT_UNSUPPORTED;
  }
}

static int getkey_setup(void)
{
  _kb_setup();
  return __libc_kb_pf_getkey();
}
static int getxkey_setup(void)
{
  _kb_setup();
  return __libc_kb_pf_getxkey();
}
static int kbhit_setup(void)
{
  _kb_setup();
  return __libc_kb_pf_kbhit();
}

