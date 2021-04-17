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

void
ScreenGetCursor_nec98(int *_row, int *_col)
{
  *_row = _farpeekb(dossel, 0x600 + 0x110);
  *_col = _farpeekb(dossel, 0x600 + 0x11C);
}