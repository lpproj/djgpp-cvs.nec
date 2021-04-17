#include <conio.h>
#include <libc/stubs.h>
#include <dpmi.h>
#include <go32.h>
#include <libc/farptrgs.h>
#include <sys/segments.h>
#include <pc.h>
#include "../common/_co80.h"

#define ScreenSetCursor(r,c) ScreenSetCursor_ibmpc(r,c)
#include "../scsetc.c"
