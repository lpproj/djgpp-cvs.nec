/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
#include <libc/stubs.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <io.h>
#include <libc/file.h>
#include <libc/local.h>
#include <libc/fd_props.h>

FILE *
fdopen(int fildes, const char *mode)
{
  FILE *f;
  int rw, oflags = 0;
  char tbchar;

  f = __alloc_file();
  if (f == NULL)
    return NULL;

  rw = (mode[1] == '+') || (mode[1] && (mode[2] == '+'));

  switch (*mode)
  {
  case 'a':
    oflags = O_CREAT | (rw ? O_RDWR : O_WRONLY) | O_APPEND;
    break;
  case 'r':
    oflags = rw ? O_RDWR : O_RDONLY;
    break;
  case 'w':
    oflags = O_TRUNC | O_CREAT | (rw ? O_RDWR : O_WRONLY);
    break;
  default:
    return (NULL);
  }
  if (mode[1] == '+')
    tbchar = mode[2];
  else
    tbchar = mode[1];
  if (tbchar == 't')
    oflags |= O_TEXT;
  else if (tbchar == 'b')
    oflags |= O_BINARY;
  else
    oflags |= (_fmode & (O_TEXT|O_BINARY));

  f->_cnt = 0;
  f->_file = fildes;
  f->_bufsiz = 0;
  if (rw)
    f->_flag = _IORW;
  else if (*mode == 'r')
    f->_flag = _IOREAD;
  else
    f->_flag = _IOWRT;

  f->_base = f->_ptr = NULL;

  setmode(fildes, oflags & (O_TEXT|O_BINARY));

  /* Set or clear the append flag according to the mode.  */
  if (__has_fd_properties(fildes))
  {
    if (*mode == 'a')
      __set_fd_flags(fildes, FILE_DESC_APPEND);
    else
      __clear_fd_flags(fildes, FILE_DESC_APPEND);
  }

  return f;
}
