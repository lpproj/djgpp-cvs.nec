#include <conio.h>
#include "../sc.h"
#include "../common/_co80.h"

void
ScreenVisualBell(void)
{
  __libc_co80_pf_ScreenVisualBell();
}
