/* Copyright (C) 2018 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2017 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2002 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1997 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
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
#include <libc/_machine.h>
#include <stdint.h>
#include "../common/_co80.h"

#define refreshvirtualscreen(c,r,count) _conio_refreshvirtualscreen_ibmpc(c,r,count)

static void mayrefreshline(int c, int r, int *srow, int *scol, int *ecol);
static int isEGA(void);

#define DBGGTINFO   0

void
_conio_refreshvirtualscreen_ibmpc(int c, int r, int count)
{
  __dpmi_regs regs;

  regs.x.es = ScreenVirtualSegment;
  regs.x.di = VOFFSET(r, c);
  regs.h.ah = 0xff;	/* Refresh Screen */
  regs.x.cx = count;	/* number of characters */
  __dpmi_int(0x10, &regs);
}

static void
mayrefreshline(int c, int r, int *srow, int *scol, int *ecol)
{
  if (*ecol != *scol)
    refreshvirtualscreen(*scol, *srow, *ecol-*scol);
  *srow = r;
  *scol = *ecol = c;
}

int
puttext_ibmpc(int c, int r, int c2, int r2, void *buf)
{
  short *cbuf = (short *)buf;
  /* we should check for valid parameters, and maybe return 0 */
  r--, r2--, c--, c2--;
  for (; r <= r2; r++)
  {
    dosmemput(cbuf, (c2-c+1)*2, VIDADDR(r, c));
    cbuf += c2-c+1;
    if (ScreenVirtualSegment != 0)
      refreshvirtualscreen(c, r, c2-c+1);
  }
  return 1;
}


int
_conio_gettext_ibmpc(int c, int r, int c2, int r2, void *buf)
{
  short *cbuf = (short *)buf;
  /* we should check for valid parameters, and maybe return 0 */
  r--, r2--, c--, c2--;
  for (; r <= r2; r++)
  {
    dosmemget(VIDADDR(r, c), (c2-c+1)*2, cbuf);
    cbuf += c2-c+1;
  }
  return 1;
}

void
textmode_ibmpc(int mode)
{
  __dpmi_regs regs;
  int mode_to_set = mode;
  if (mode == LASTMODE)
    mode = mode_to_set = last_mode;

  /* Should we support 2 LAST_MODEs in a row?  Right now we do; if not,
     put an ``else'' clause before next line.  */
  last_mode = txinfo.currmode;
  if (mode == C4350)
    /* 
     * just set mode 3 and load 8x8 font, idea taken 
     * (and code translated from Assembler to C)
     * from Csaba Biegels stdvga.asm
     */
    mode_to_set = 0x03;  
  regs.h.ah = 0x00;		/* set mode */
  regs.h.al = mode_to_set;
  __dpmi_int(0x10, &regs);
  if (mode == C80 || mode == BW80 || mode == C4350)
  {
    if (isEGA())
    {
      /* 
       * enable cursor size emulation, see Ralf Browns
       * interrupt list
       */
      regs.h.ah = 0x12;
      regs.h.bl = 0x34;
      regs.h.al = 0x00;		/* 0: enable (1: disable) */
      __dpmi_int(0x10, &regs);
    }
  }
  if (mode == C4350)
  {
    if (!isEGA())
      return;
    /* load 8x8 font */
    regs.x.ax = 0x1112;         
    regs.x.bx = 0;
    __dpmi_int(0x10, &regs);
  }
  /*    _setcursortype(_NORMALCURSOR); */
  /* reinitialize txinfo structure to take into account new mode */
  gppconio_init();
#if 0
  /*
   * For mode C4350 the screen is not cleared on my OAK-VGA.
   * Should we clear it here? TURBOC doesn't so we don't bother either.
   */
  clrscr();
#endif
}    

void
_setcursortype_ibmpc(int type)
{
  __dpmi_regs reg;
  unsigned cursor_shape;

  switch (type)
  {
  case _NOCURSOR:
    cursor_shape = 0x2000;
    break;
  case _SOLIDCURSOR:
    cursor_shape = 0x0007;
    break;
    /*      case _NORMALCURSOR: */
  default:
    cursor_shape = 0x0607;
    break;
  }
  reg.h.ah = 1;
  reg.x.cx = cursor_shape;
  __dpmi_int(0x10, &reg);
}


static void
fillrow(int row, int left, int right, int fill)
{
  int col;
  short filler[right-left+1];
  
  for (col = left; col <= right; col++)
    filler[col-left] = fill;
  dosmemput(filler, (right-left+1)*2, VIDADDR(row, left));
  if (ScreenVirtualSegment != 0)
    refreshvirtualscreen(left, row, right-left+1);
}

void
clrscr_ibmpc(void)
{
  short filler[txinfo.winright - txinfo.winleft + 1];
  int row, col;
  for (col=0; col < txinfo.winright - txinfo.winleft + 1; col++)
    filler[col] = ' ' | (ScreenAttrib << 8);
  for (row=txinfo.wintop-1; row < txinfo.winbottom; row++)
    {
      dosmemput(filler, (txinfo.winright - txinfo.winleft + 1)*2,
		VIDADDR(row, txinfo.winleft - 1));
      if (ScreenVirtualSegment != 0)
	refreshvirtualscreen(txinfo.winleft - 1, row, txinfo.winright - txinfo.winleft + 1);
    }
  gotoxy(1, 1);
}

/* 
 * kbhit from libc in libsrc/c/dos/kbhit.s doesn't check
 * for ungotten chars, so we have to provide a new one
 * Don't call it kbhit, rather use a new name (_conio_kbhit)
 * and do a #define kbhit _conio_kbhit in gppconio.h.
 * The old kbhit still can be used if gppconio.h
 * is not included of after #undef kbhit
 * If you don't use ungetch (directly or indirectly by cscanf)
 * both kbhit and _conio_kbhit are the same.
 * So this shouldn't cause any trouble with previously written
 * source, because ungetch wasn't available.
 * The only problem might be, if anybody just included gppconio.h
 * and has not linked with libpc, (I can't think of a good reason
 * for this). This will result a link error (undefined symbol _conio_kbhit).
 */

#undef kbhit  /* want to be able to call kbhit from libc */

void
insline_ibmpc(void)
{
  int row, col, left, right, nbytes, bot, fill;
  ScreenGetCursor(&row, &col);
  left = txinfo.winleft - 1;
  right = txinfo.winright - 1;
  nbytes = (right-left+1)*2;
  bot = txinfo.winbottom-1;
  fill = ' ' | (ScreenAttrib << 8);
  while (bot > row)
  {
    movedata(_dos_ds, VIDADDR(bot-1, left),
	     _dos_ds, VIDADDR(bot, left),
	     nbytes);
    if (ScreenVirtualSegment != 0)
      refreshvirtualscreen(left, bot-1, nbytes/2);
    bot--;
  }
  fillrow(row,left,right,fill);
}

void
delline_ibmpc(void)
{
  int row, col, left, right, nbytes, bot, fill;
  ScreenGetCursor(&row, &col);
  left = txinfo.winleft - 1;
  right = txinfo.winright - 1;
  nbytes = (right-left+1)*2;
  bot = txinfo.winbottom-1;
  fill = ' ' | (ScreenAttrib << 8);
  while(row < bot)
  {
    movedata(_dos_ds, VIDADDR(row+1, left),
	     _dos_ds, VIDADDR(row, left),
	     nbytes);
    if (ScreenVirtualSegment != 0)
      refreshvirtualscreen(left, row, nbytes/2);
    row++;
  }
  fillrow(bot,left,right,fill);
}


int
cputs_ibmpc(const char *s)
{
  int     row, col,c;
  const unsigned char *ss = (const unsigned char *)s;
  short *viaddr;
  short sa = ScreenAttrib << 8;
  int srow, scol, ecol;
  ScreenGetCursor(&row, &col);
  viaddr = (short *)(uintptr_t)VIDADDR(row,col);
  /*
   * DOS/V: simply it refreshes screen between scol and ecol when cursor moving.
   */
  srow = row;
  scol = ecol = col;

  /* 
   * Instead of just calling putch; we do everything by hand here,
   * This is much faster. We don't move the cursor after each character,
   * only after the whole string is written, because ScreenSetCursor
   * needs to long because of switching to real mode needed with djgpp. 
   * You won't recognize the difference.
   */
  while ((c = *ss++))
  {
    /*  first, handle the character */
    if (c == '\n')
    {
      row++;
      viaddr += txinfo.screenwidth;
      if (ScreenVirtualSegment != 0)
	mayrefreshline(col, row, &srow, &scol, &ecol);
    }
    else if (c == '\r')
    {
      col = txinfo.winleft - 1;
      viaddr = (short *)(uintptr_t)VIDADDR(row,col);
      if (ScreenVirtualSegment != 0)
	mayrefreshline(col, row, &srow, &scol, &ecol);
    }
    else if (c == '\b')
    {
      if (col > txinfo.winleft-1) 
      {
	col--;
	viaddr--;
      }
      else if (row > txinfo.wintop -1)
      {
	/* 
	 * Turbo-C ignores this case. We want to be able to
	 * edit strings with backspace in gets after
	 * a linefeed, so we are smarter
	 */
	row--;
	col = txinfo.winright-1;
	viaddr = (short *)(uintptr_t)VIDADDR(row,col);
      }
      if (ScreenVirtualSegment != 0)
	mayrefreshline(col, row, &srow, &scol, &ecol);
    }
    else if (c == 0x07)
      _conio_bell();
    else {
      short q = c | sa;
      dosmemput(&q, 2, (int)viaddr);
      viaddr++;
      col++;
      ecol++;
    }
      
    /* now, readjust the window     */
      
    if (col >= txinfo.winright) {
      col = txinfo.winleft - 1;
      row++;
      viaddr = (short *)(uintptr_t)VIDADDR(row,col);
      if (ScreenVirtualSegment != 0)
	mayrefreshline(col, row, &srow, &scol, &ecol);
    }
      
    if (row >= txinfo.winbottom) {
      /* refresh before scroll */
      if (ScreenVirtualSegment != 0)
	mayrefreshline(col, row, &srow, &scol, &ecol);
      if (_wscroll)
      {
	ScreenSetCursor(txinfo.wintop-1,0); /* goto first line in window */
	delline();		/* and delete it */
      }
      row--;
      srow--;
      viaddr -= txinfo.screenwidth;
    }
  }
  
  /* refresh the rest of cols */
  if (ScreenVirtualSegment != 0)
    mayrefreshline(col, row, &srow, &scol, &ecol);
  ScreenSetCursor(row, col);
  txinfo.cury = row - txinfo.wintop + 2;
  txinfo.curx = col - txinfo.winleft + 2;
  return(*(--ss));
}

int
__libc_conio_get_screenattrib_ibmpc(void)
{
  __dpmi_regs regs;
  regs.h.ah = 0x08;		/* read character and attribute */
  regs.h.bh = 0;		/* video page 0 */
  __dpmi_int(0x10, &regs);
  return(regs.h.ah & 0x7f);	/* strip highest (BLINK) bit */
}

/* Check if we have at least EGA.
   Return 1 if EGA, 2 if VGA/PGA/MCGA, else 0. */
static int
isEGA(void)
{
  if (adapter_type == -1)
    {
      __dpmi_regs regs;

      /* Get display combination code.  */
      regs.x.ax = 0x1a00;
      __dpmi_int(0x10, &regs);
      if (regs.h.al == 0x1a)    /* if Int 10h/AX=1A00h supported */
        switch (regs.h.bl)
          {
            case 4:
            case 5:
                adapter_type = 1; /* EGA */
                break;
            case 6:             /* PGA */
            case 7:             /* VGA */
            case 8:             /* VGA */
            case 10:            /* MCGA */
            case 11:            /* MCGA */
            case 12:            /* MCGA */
                adapter_type = 2;
                break;
            default:
                adapter_type = 0;
          }

      else
        {
          /* Int 10h/AX=1A00h not supported.  Try getting EGA info.  */
          regs.h.ah = 0x12;
          regs.h.bl = 0x10;
          regs.h.bh = 0xff;
          __dpmi_int(0x10, &regs);
          adapter_type = (regs.h.bh != 0xff);
        }
    }

  return adapter_type;
}

/* Set screen scan lines and load appropriate font.
   SCAN_LINES and FONT are as required by Int 10h functions 12h and 11h */
static void
set_scan_lines_and_font(int scan_lines, int font)
{
  __dpmi_regs regs;

  /* Set 200/350/400 scan lines.  */
  regs.h.ah = 0x12;
  regs.h.al = scan_lines;       /* 0: 200, 1: 350, 2: 400 */
  regs.h.bl = 0x30;
  __dpmi_int(0x10, &regs);

  /* Scan lines setting only takes effect when video mode is set.  */
  regs.x.ax = txinfo.currmode == 7 ? 7 : 3;
  __dpmi_int(0x10, &regs);

  /* Load a ROM BIOS font (0x11: 8x14, 0x12: 8x8, 0x14: 8x16).  */
  regs.h.bl = 0;                /* block zero */
  regs.h.ah = 0x11;
  regs.h.al = font & 0xff;
  __dpmi_int(0x10, &regs);
}

/* Stretch a 8x8 font to the 8x10 character box.  This is required to
   use 80x40 mode on a VGA or 80x35 mode on an EGA, because the character
   box is 10 lines high, and the ROM BIOS doesn't have an appropriate font.
   So we create one from the 8x8 font by adding an extra blank line
   from each side.  */
static void
maybe_create_8x10_font(void)
{
  unsigned long src, dest, i, j;

  if (font_seg == -1)
    {
      __dpmi_regs regs;
      int buf_pm_sel;
      
      /* Allocate buffer in conventional memory. */
      font_seg = __dpmi_allocate_dos_memory(160, &buf_pm_sel);

      if (font_seg == -1)
        return;

      /* Get the pointer to the 8x8 font table.  */
      regs.h.bh = 3;
      regs.x.ax = 0x1130;
      __dpmi_int(0x10, &regs);
      src =  ( ( (unsigned)regs.x.es ) << 4 ) + regs.x.bp;
      dest = ( (unsigned)font_seg ) << 4;

      /* Now copy the font to our table, stretching it to 8x10. */
      _farsetsel(_dos_ds);
      for (i = 0; i < 256; i++)
        {
          /* Fill first extra scan line with zeroes. */
          _farnspokeb(dest++, 0);

          for (j = 0; j < 8; j++)
            {
              unsigned char val = _farnspeekb(src++);

              _farnspokeb(dest++, val);
            }

          /* Fill last extra scan line with zeroes. */
          _farnspokeb(dest++, 0);
        }
    }
}

/* Load the 8x10 font we created into character generator RAM.  */
static void
load_8x10_font(void)
{
  __dpmi_regs regs;

  maybe_create_8x10_font();         /* create if needed */
  if (font_seg == -1)
    return;
  regs.x.es = font_seg;             /* pass pointer to our font in ES:BP */
  regs.x.bp = 0;
  regs.x.dx = 0;                    /* 1st char: ASCII 0 */
  regs.x.cx = 256;                  /* 256 chars */
  regs.h.bh = 10;                   /* 10 points per char */
  regs.h.bl = 0;                    /* block 0 */
  regs.x.ax = 0x1110;
  __dpmi_int(0x10, &regs);
}

/* Set screen scan lines and load 8x10 font.
   SCAN_LINES is as required by Int 10h function 12h. */
static void
set_scan_lines_and_8x10_font(int scan_lines)
{
  __dpmi_regs regs;

  regs.h.bl = 0x30;
  regs.h.ah = 0x12;
  regs.h.al = scan_lines;           /* 0: 200, 1: 350, 2: 400 */
  __dpmi_int(0x10, &regs);

  /* Set video mode, so that scan lines we set will take effect.  */
  regs.x.ax = txinfo.currmode == 7 ? 7 : 3;
  __dpmi_int(0x10, &regs);

  /* Load our 8x10 font and enable intensity bit.  */
  load_8x10_font();
}

/* Switch to screen lines given by NLINES.  */
void
_set_screen_lines_ibmpc(int nlines)
{
  switch (nlines)
    {
      __dpmi_regs regs;

      case 25:
          if (adapter_type)
            {
              /* Set 350 scan lines for EGA, 400 for VGA.  */
              regs.h.bl = 0x30;
              regs.h.ah = 0x12;
              regs.h.al = (adapter_type > 1 ? 2 : 1);
              __dpmi_int(0x10, &regs);

              /* Load ROM BIOS font: 8x14 for EGA, 8x16 for VGA.  */
              regs.h.bl = 0;
              regs.h.ah = 0x11;
              regs.h.al = (adapter_type > 1 ? 0x14 : 0x11);
              __dpmi_int(0x10, &regs);
            }

          /* Set video mode.  */
          regs.x.ax = txinfo.currmode == 7 ? 7 : 3;
          __dpmi_int(0x10, &regs);
          break;
      case 28:      /* VGA only */
          if (adapter_type > 1)
            set_scan_lines_and_font(2, 0x11);
          break;
      case 35:      /* EGA or VGA */
          if (adapter_type)
            set_scan_lines_and_8x10_font(1);
          break;
      case 40:      /* VGA only */
          if (adapter_type > 1)
            set_scan_lines_and_8x10_font(2);
          break;
      case 43:      /* EGA or VGA */
          if (adapter_type)
            set_scan_lines_and_font(1, 0x12);
          break;
      case 50:      /* VGA only */
          if (adapter_type > 1)
            set_scan_lines_and_font(2, 0x12);
          break;
    }

  _conio_gettextinfo(&txinfo);
}

void
blinkvideo_ibmpc(void)
{

  /* Set intensity/blinking bit to BLINKING.  */
  __dpmi_regs regs;
  regs.h.bl = 1;
  regs.x.ax = 0x1003;
  __dpmi_int(0x10, &regs);
  intense_bg_mode = (_farpeekb(_dos_ds, 0x465) & 0x20) == 0;
}

void
intensevideo_ibmpc(void)
{

  /* Set intensity/blinking bit to INTENSE (bright background).  */
  __dpmi_regs regs;
  regs.h.bl = 0;
  regs.x.ax = 0x1003;
  __dpmi_int(0x10, &regs);
  intense_bg_mode = (_farpeekb(_dos_ds, 0x465) & 0x20) == 0;
}


void
__libc_conio_init_sub_ibmpc(void)
{
  __dpmi_regs regs;

  (void)isEGA();    /* sets the global ADAPTER_TYPE */

  if (oldattrib == -1)
    oldattrib = __libc_conio_get_screenattrib_ibmpc();
  if (last_mode == 0xffff)
    last_mode = __libc_conio_getvideomode();
  _conio_gettextinfo(&txinfo);
  if (txinfo.currmode == 7)	/* MONO */
    ScreenAddress = 0xb0000UL;
  else
    ScreenAddress = 0xb8000UL;
  intense_bg_mode = (_farpeekb(_dos_ds, 0x465) & 0x20) == 0;

  regs.x.es = regs.x.di = 0;	/* Dummy for checking */
  regs.h.ah = 0xfe;		/* Get Video Buffer */
  __dpmi_int(0x10, &regs);
  ScreenVirtualSegment = regs.x.es;
  ScreenVirtualOffset = regs.x.di;
}

