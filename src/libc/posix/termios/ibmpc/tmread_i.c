#include <libc/stubs.h>
#include <go32.h>
#include <io.h>
#include <pc.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/exceptn.h>
#include <libc/file.h>
#include <libc/ttyprvt.h>
#include <libc/farptrgs.h>
#include <libc/getdinfo.h>

#include <libc/_machine.h>
#include "../common/_termios.h"

#define __libc_termios_init_read  __libc_termios_init_read_ibmpc
#include "../tmread.c"

