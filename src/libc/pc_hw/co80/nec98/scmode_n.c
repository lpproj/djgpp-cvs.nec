/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <conio.h>
#include <dpmi.h>
#include <go32.h>
#include <libc/farptrgs.h>
#include <sys/segments.h>
#include "../sc.h"
#include <libc/_machine.h>
#include "../common/_co80.h"

int
ScreenMode_nec98(void)
{
  /* todo: 40cols mode, 200lines mode, 480lines mode, etc... */
  return 0x03;
}
