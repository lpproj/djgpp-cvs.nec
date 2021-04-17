#include <bios.h>
#include <stdlib.h>
#include <libc/_machine.h>
#include "_bios.h"

static int biosdisk_setup(int _cmd, int _drive, int _head, int _track, int _sector, int _nsects, void *_buffer);
static unsigned _bios_disk_setup(unsigned _cmd, struct _diskinfo_t *_di);

static int (*__libc_bios_pf_biosdisk)(int, int, int, int, int, int, void *) = biosdisk_setup;
static unsigned (*__libc_bios_pf__bios_disk)(unsigned, struct _diskinfo_t *) = _bios_disk_setup;

static void biosdisks_setup(void)
{
  switch(__crt0_machine_type) {
#ifdef SUPPORT_IBMPC
    case MACHINE_TYPE_IBMPC:
      __libc_bios_pf_biosdisk = biosdisk_ibmpc;
      __libc_bios_pf__bios_disk = _bios_disk_ibmpc;
      break;
#endif
#ifdef SUPPORT_NEC98
    case MACHINE_TYPE_NEC98:
      __libc_bios_pf_biosdisk = biosdisk_nec98;
      __libc_bios_pf__bios_disk = _bios_disk_nec98;
      break;
#endif
    default:
      ABORT_UNSUPPORTED;
  }
}


static int biosdisk_setup(int _cmd, int _drive, int _head, int _track, int _sector, int _nsects, void *_buffer)
{
  biosdisks_setup();
  return __libc_bios_pf_biosdisk(_cmd, _drive, _head, _track, _sector, _nsects, _buffer);
}
int biosdisk(int _cmd, int _drive, int _head, int _track, int _sector, int _nsects, void *_buffer)
{
  return __libc_bios_pf_biosdisk(_cmd, _drive, _head, _track, _sector, _nsects, _buffer);
}

static unsigned _bios_disk_setup(unsigned _cmd, struct _diskinfo_t *_di)
{
  biosdisks_setup();
  return __libc_bios_pf__bios_disk(_cmd, _di);
}
unsigned _bios_disk(unsigned _cmd, struct _diskinfo_t *_di)
{
  return __libc_bios_pf__bios_disk(_cmd, _di);
}
