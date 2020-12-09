/* Copyright (C) 2020 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <string.h>

size_t
strlen(const char *str)
{
  const char *s;

  for (s = str; *s; ++s);
  return s - str;
}

