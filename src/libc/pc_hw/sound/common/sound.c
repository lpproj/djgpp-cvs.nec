#include <pc.h>
#include <stdlib.h>
#include <libc/_machine.h>
#include "../common/_sound.h"

static void sound_setup(int freq);
void (*__libc_sound_pf_sound)(int freq) = sound_setup;



static void sound_setup(int freq)
{
  switch(__crt0_machine_type) {
#ifdef SUPPORT_IBMPC
    case MACHINE_TYPE_IBMPC:
      __libc_sound_pf_sound = sound_ibmpc;
      break;
#endif
#ifdef SUPPORT_NEC98
    case MACHINE_TYPE_NEC98:
      __libc_sound_pf_sound = sound_nec98;
      break;
#endif
    default:
      ABORT_UNSUPPORTED;
  }

  __libc_sound_pf_sound(freq);
}

void
sound(int freq)
{
  __libc_sound_pf_sound(freq);
}
