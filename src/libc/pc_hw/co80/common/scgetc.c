#include <conio.h>
#include "../sc.h"
#include "../common/_co80.h"

void
ScreenGetCursor(int *_row, int *_col)
{
  __libc_co80_pf_ScreenGetCursor(_row, _col);
}
