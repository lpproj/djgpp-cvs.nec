/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <bios.h>
#include <dpmi.h>
#include <stdlib.h>
#include "../common/_bios.h"

int biosdisk_nec98(int cmd, int drive, int head, int track, int sector, int nsects, void *buffer)
{
  /* NOT to be implemented */
  return -1;
}

unsigned _bios_disk_nec98(unsigned _cmd, struct diskinfo_t *_di)
{
  /* NOT to be implemented */
  return -1;
}
