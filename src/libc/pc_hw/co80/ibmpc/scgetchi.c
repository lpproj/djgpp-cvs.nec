#include <conio.h>
#include <libc/stubs.h>
#include <dpmi.h>
#include <go32.h>
#include <libc/farptrgs.h>
#include <sys/segments.h>
#include <pc.h>
#include "../common/_co80.h"

#define ScreenGetChar ScreenGetChar_ibmpc
#include "../scgetch.c"
