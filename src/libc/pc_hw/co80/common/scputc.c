#include <conio.h>
#include "../sc.h"
#include "../common/_co80.h"

void
ScreenPutChar(int _ch, int _attr, int _x, int _y)
{
  __libc_co80_pf_ScreenPutChar(_ch, _attr, _x, _y);
}
