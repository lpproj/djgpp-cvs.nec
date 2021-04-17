#include <conio.h>
#include "../sc.h"
#include "../common/_co80.h"

void
ScreenPutString(const char *_ch, int _attr, int _x, int _y)
{
  __libc_co80_pf_ScreenPutString(_ch, _attr, _x, _y);
}
