#include <conio.h>
#include "../sc.h"
#include "../common/_co80.h"

void
ScreenUpdate(const void *_virtual_screen)
{
  __libc_co80_pf_ScreenUpdate(_virtual_screen);
}
