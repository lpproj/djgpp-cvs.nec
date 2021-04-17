#include <conio.h>
#include "../sc.h"
#include "../common/_co80.h"

void
ScreenRetrieve(void *_virtual_screen)
{
  __libc_co80_pf_ScreenRetrieve(_virtual_screen);
}
