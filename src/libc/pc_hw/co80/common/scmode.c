#include <conio.h>
#include "../sc.h"
#include "../common/_co80.h"

int
ScreenMode(void)
{
  return __libc_co80_pf_ScreenMode();
}
