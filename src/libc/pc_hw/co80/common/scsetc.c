#include <conio.h>
#include "../sc.h"
#include "../common/_co80.h"

void
ScreenSetCursor(int _row, int _col)
{
  __libc_co80_pf_ScreenSetCursor(_row, _col);
}
