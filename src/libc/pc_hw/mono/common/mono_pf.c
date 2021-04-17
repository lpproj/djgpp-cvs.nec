/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <stdarg.h>
#include <stdio.h>
#include <sys/mono.h>
#include <libc/farptrgs.h>
#include <go32.h>

#include <libc/_machine.h>
#include "_mono.h"

void _mono_printf(const char *fmt, ...)
{
  int i;
  char buf[1000];
  va_list a = 0;
  va_start(a, fmt);
  vsnprintf(buf, sizeof(buf), fmt, a);
  for (i=0; buf[i]; i++)
    _mono_putc(buf[i]);
  va_end(a);
}
