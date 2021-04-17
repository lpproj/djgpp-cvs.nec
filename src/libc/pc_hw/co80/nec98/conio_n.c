/* NEC98 and DOSV port: */
/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <libc/stubs.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <pc.h>
#include <errno.h>
#include <unistd.h>
#include <go32.h>
#include <dpmi.h>
#include <libc/farptrgs.h>
#include <conio.h>
#include <libc/bss.h>
#include <libc/unconst.h>
#include <string.h>
#include <libc/_machine.h>
#include <stdint.h>
#include "../sc.h"
#include "../common/_co80.h"

/*
  TODO(1): support extra text modes (20lines, 31lines on hi-res, 40columns, 30bios...)
  TODO(2): support double byte character (kanji)
*/

void
_conio_refreshvirtualscreen_nec98(int c, int r, int count)
{
  (void)c;
  (void)r;
  (void)count;
}


int puttext_nec98(int c, int r, int c2, int r2, void *buf)
{
  /* todo: support DBCS (kanji) */
  const unsigned char *s = buf;
  int x, y;

  if ( c <= 0 || r <= 0 || c > c2 || r > r2 || c2 > ScreenCols_nec98() || r2 > ScreenRows_nec98())
    return 0;

  --c; --r; --c2; --r2;
  _farsetsel(dossel);
  for(y=r; y<=r2; ++y) {
    unsigned scptr = VIDADDR(y, c);
    for(x=c; x<=c2; ++x) {
      _farnspokew(scptr, *s);
      _farnspokew(scptr + 0x2000, _conio_attr_ibmpc_to_nec98(s[1]));
      scptr += 2;
      s += 2;
    }
  }

  return 1;
}

int _conio_gettext_nec98(int c, int r, int c2, int r2, void *buf)
{
  /* todo: support DBCS (kanji) */
  unsigned char *s = buf;
  int x, y;

  if ( c <= 0 || r <= 0 || c > c2 || r > r2 || c2 > ScreenCols_nec98() || r2 > ScreenRows_nec98())
    return 0;

  --c; --r; --c2; --r2;
  _farsetsel(dossel);
  for(y=r; y<=r2; ++y) {
    unsigned scptr = VIDADDR(y, c);
    for(x=c; x<=c2; ++x) {
      *s = _farnspeekb(scptr);
      s[1] = _conio_attr_nec98_to_ibmpc(_farnspeekb(scptr + 0x2000));
      s += 2;
    }
  }

  return 1;
}

void textmode_nec98(int mode)
{
  gppconio_init();
}

void _setcursortype_nec98(int type)
{
  int show = 1;
  __dpmi_regs r;
  switch ( type ) {
  case _NOCURSOR:
    show = 0;
    r.h.ah = 0x12;
    __dpmi_int(0x18, &r);
    break;
  default:  /* _SOLIDCURSOR: _NORMALCURSOR: */
    r.x.ax = 0x1000;
    __dpmi_int(0x18, &r);
    r.h.ah = 0x11;
    __dpmi_int(0x18, &r);
    break;
  }
  _farpokeb(_dos_ds, 0x600 + 0x11b, show);
}

static void fillrow_nec98(int row, int left, int right, int fill)
{
  int col;
  unsigned short filler[right-left+1], cfill;

  cfill = fill & 0x00ff;
  for (col = left; col <= right; col++)
    filler[col-left] = cfill;
  dosmemput(filler, (right-left+1)*2, VIDADDR(row, left));
  cfill = fill >> 8; cfill = (unsigned short)_conio_attr_ibmpc_to_nec98(cfill);
  for (col = left; col <= right; col++)
    filler[col-left] = cfill;
  dosmemput(filler, (right-left+1)*2, VIDADDR(row, left)+0x2000);
}

void clrscr_nec98(void)
{
  unsigned short tfiller[txinfo.winright - txinfo.winleft + 1];
  unsigned short afiller[txinfo.winright - txinfo.winleft + 1];
  unsigned short cfill = (unsigned short)_conio_attr_ibmpc_to_nec98(ScreenAttrib);
  int row, col;

  for (col=0; col < txinfo.winright - txinfo.winleft + 1; col++) {
    tfiller[col] = (unsigned short)' ';
    afiller[col] = cfill;
  }
  for (row=txinfo.wintop-1; row < txinfo.winbottom; row++) {
    dosmemput(tfiller, (txinfo.winright - txinfo.winleft + 1)*2,
              VIDADDR(row, txinfo.winleft - 1));
    dosmemput(afiller, (txinfo.winright - txinfo.winleft + 1)*2,
              VIDADDR(row, txinfo.winleft - 1)+0x2000);
  }
  gotoxy(1, 1);
}

void insline_nec98(void)
{
  int row, col, left, right, nbytes, bot, fill;
  ScreenGetCursor(&row, &col);
  left = txinfo.winleft - 1;
  right = txinfo.winright - 1;
  nbytes = (right-left+1)*2;
  bot = txinfo.winbottom-1;
  fill = ' ' | (ScreenAttrib << 8);
  while (bot > row) {
    movedata(_dos_ds, VIDADDR(bot-1, left),
             _dos_ds, VIDADDR(bot, left), nbytes);
    movedata(_dos_ds, VIDADDR(bot-1, left)+0x2000,
             _dos_ds, VIDADDR(bot, left)+0x2000, nbytes);
    bot--;
  }
  fillrow_nec98(row,left,right,fill);
}

void delline_nec98(void)
{
  int row, col, left, right, nbytes, bot, fill;
  ScreenGetCursor(&row, &col);
  left = txinfo.winleft - 1;
  right = txinfo.winright - 1;
  nbytes = (right-left+1)*2;
  bot = txinfo.winbottom-1;
  fill = ' ' | (ScreenAttrib << 8);
  while (row < bot) {
    movedata(_dos_ds, VIDADDR(row+1, left),
             _dos_ds, VIDADDR(row, left), nbytes);
    movedata(_dos_ds, VIDADDR(row+1, left)+0x2000,
             _dos_ds, VIDADDR(row, left)+0x2000, nbytes);
    row++;
  }
  fillrow_nec98(bot,left,right,fill);
}

int cputs_nec98(const char *s)
{
  /* todo: DBCS */
  int row, col;
  const unsigned char *ss = (const unsigned char *)s;
  unsigned short *viaddr;
  unsigned short c, sa = _conio_attr_ibmpc_to_nec98(ScreenAttrib);

  ScreenGetCursor(&row, &col);
  viaddr = (unsigned short *)(uintptr_t)VIDADDR(row, col);

  while ((c = *ss++)) {
    switch ( c ) {
    case '\n':
      row++;
      viaddr += txinfo.screenwidth;
      break;
    case '\r':
      col = txinfo.winleft - 1;
      viaddr = (unsigned short *)(uintptr_t)VIDADDR(row, col);
      break;
    case '\b':
      if (col > txinfo.winleft-1) {
        col--;
        viaddr--;
      } else if (row > txinfo.wintop-1) {
        row--;
        col = txinfo.winright-1;
        viaddr = (unsigned short *)(uintptr_t)VIDADDR(row,col);
      }
      break;
    case 0x07:
      _conio_bell();
      break;
    default:
      dosmemput(&c,  2, (int)viaddr);
      dosmemput(&sa, 2, (int)viaddr+0x2000);
      viaddr++;
      col++;
    }

    if (col >= txinfo.winright) {
      col = txinfo.winleft - 1;
      row++;
      viaddr = (unsigned short *)(uintptr_t)VIDADDR(row,col);
    }
    if (row >= txinfo.winbottom) {
      ScreenSetCursor(txinfo.wintop-1, txinfo.winleft-1);
      delline();
      row--;
      viaddr -= txinfo.screenwidth;
    }
  }

  ScreenSetCursor(row, col);
  txinfo.cury = row - txinfo.wintop + 2;
  txinfo.curx = col - txinfo.winleft + 2;
  return(*(--ss));
}

int __libc_conio_get_screenattrib_nec98(void)
{
#if 1
  return _conio_attr_nec98_to_ibmpc(_farpeekb(_dos_ds, 0x600 + 0x11d));
#else
  int row, col;
  ScreenGetCursor(&row, &col);
  return _conio_attr_nec98_to_ibmpc(_farpeekb(_dos_ds, VIDADDR(row,col)+0x2000));
#endif
}

void _set_screen_lines_nec98(int nlines)
{
  /* Not implemented yet */
}

void blinkvideo_nec98(void)
{
  /* PC-AT: Set intensity/blinking bit to BLINKING. */
  /* PC-98: Set ATR4 to VL */
  outportb(0x68, 0x00);
}

void intensevideo_nec98(void)
{
  /* PC-AT: Set intensity/blinking bit to INTENSE (bright background). */
  /* PC-98: Set ATR4 to BG */
  outportb(0x68, 0x01);
}

void
__libc_conio_init_sub_nec98(void)
{
  if (__libc_conio_oldattrib == -1)
    __libc_conio_oldattrib = __libc_conio_get_screenattrib_nec98();
  if (__libc_conio_last_mode == 0xffff)
    __libc_conio_last_mode = __libc_conio_getvideomode();
  _conio_gettextinfo(&__libc_conio_txinfo);
  __libc_conio_adapter_type = 2; /* VGA (dummy) */
  __libc_conio_ScreenAddress = ScreenPrimary;
  ScreenVirtualSegment = ScreenPrimary >> 4;
  ScreenVirtualOffset = 0;
}
