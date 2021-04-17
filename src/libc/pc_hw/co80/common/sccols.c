#include <conio.h>
#include "../sc.h"
#include "../common/_co80.h"

int
ScreenCols(void)
{
  return __libc_co80_pf_ScreenCols();
}
