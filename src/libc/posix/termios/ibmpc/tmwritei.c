#include <libc/stubs.h>
#include <go32.h>
#include <io.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <libc/file.h>
#include <libc/ttyprvt.h>
#include <libc/farptrgs.h>
#include <libc/getdinfo.h>

#include <libc/_machine.h>
#include "../common/_termios.h"

#define __libc_termios_init_write  __libc_termios_init_write_ibmpc
#include "../tmwrite.c"

