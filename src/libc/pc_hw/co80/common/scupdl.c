#include <conio.h>
#include "../sc.h"
#include "../common/_co80.h"

void
ScreenUpdateLine(const void *_virtual_screen_line, int _row)
{
  __libc_co80_pf_ScreenUpdateLine(_virtual_screen_line, _row);
}
