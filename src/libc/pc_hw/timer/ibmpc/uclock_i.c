#include <libc/stubs.h>
#include <time.h>
#include <errno.h>
#include <pc.h>
#include <libc/farptrgs.h>
#include <go32.h>
#include <dpmi.h>
#include <libc/bss.h>
#include <dos.h>
#include <signal.h>
#include <setjmp.h>
#include <sys/exceptn.h>

#include "../common/_timer.h"

#ifdef uclock
# undef uclock
#endif

#define uclock uclock_ibmpc
#include "../uclock.c"

