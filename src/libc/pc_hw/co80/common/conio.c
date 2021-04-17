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
#include "_co80.h"

static int (*__libc_conio_pf_puttext)(int c, int r, int c2, int r2, void *buf);
static int (*__libc_conio_pf__conio_gettext)(int c, int r, int c2, int r2, void *buf);
static void (*__libc_conio_pf_textmode)(int mode);
static void (*__libc_conio_pf__setcursortype)(int type);
static void (*__libc_conio_pf_clrscr)(void);
static void (*__libc_conio_pf_insline)(void);
static void (*__libc_conio_pf_delline)(void);
static int (*__libc_conio_pf_cputs)(const char *s);
static void (*__libc_conio_pf__set_screen_lines)(int nlines);
static void (*__libc_conio_pf_blinkvideo)(void);
static void (*__libc_conio_pf_intensevideo)(void);
static void (*__libc_conio_pf__conio_refreshvirtualscreen)(int c, int r, int count);
static unsigned (*__libc_conio_pf_VIDADDR)(int r, int c) = __libc_conio_VIDADDR_common;
static unsigned (*__libc_conio_pf_VOFFSET)(int r, int c) = __libc_conio_VOFFSET_common;

static int (*__libc_conio_pf_get_screenattrib)(void);


static void (*__libc_conio_pf__conio_bell)(void) = _conio_bell_dos;

#define refreshvirtualscreen(c,r,count) (__libc_conio_pf__conio_refreshvirtualscreen(c,r,count))

int _wscroll = 1;

int directvideo = 1;  /* We ignore this */

static int _scan_getche(FILE *fp);
static int _scan_ungetch(int c, FILE *fp);

#define DBGGTINFO   0

unsigned __libc_conio_ScreenAddress = 0xb8000UL; /* initialize just in case */
unsigned short __libc_conio_ScreenVirtualSegment = 0; /* 0: non DOS/V */
unsigned short __libc_conio_ScreenVirtualOffset = 0;  /* !0: DOS/V virtual VRAM address */

#if 1
struct text_info __libc_conio_txinfo;
int __libc_conio_ungot_char;
int __libc_conio_char_avail = 0;

int __libc_conio_adapter_type = -1;         /* 1: EGA, 2: VGA/PGA/MCGA, else 0 */
int __libc_conio_font_seg = -1;             /* segment of DOS buffer for 8x10 font */
unsigned __libc_conio_last_mode = 0xffff;   /* video mode when before program start */
int __libc_conio_oldattrib =  -1;           /* text attribute before program start */

int __libc_conio_intense_bg_mode;           /* non-zero if high bit is for bright bg */

int __libc_conio_conio_count = -1;
#else
static struct text_info txinfo;
static int ungot_char;
static int char_avail = 0;

static int adapter_type = -1;       /* 1: EGA, 2: VGA/PGA/MCGA, else 0 */
static int font_seg = -1;           /* segment of DOS buffer for 8x10 font */
static unsigned last_mode = 0xffff; /* video mode when before program start */
static int oldattrib =  -1;         /* text attribute before program start */

static int intense_bg_mode;         /* non-zero if high bit is for bright bg */

static int conio_count = -1;
#endif

#if 0
#define VIDADDR(r,c) (ScreenAddress + 2*(((r) * txinfo.screenwidth) + (c)))
#define VOFFSET(r,c) (ScreenVirtualOffset + 2*(((r) * txinfo.screenwidth) + (c)))
#endif

unsigned __libc_conio_VIDADDR_common(int r, int c)
{
  return ScreenAddress + 2 * (r * __libc_conio_txinfo.screenwidth + c);
}
unsigned __libc_conio_VOFFSET_common(int r, int c)
{
  return (unsigned)ScreenVirtualOffset + 2 * (r * __libc_conio_txinfo.screenwidth + c);
}

unsigned __libc_conio_VIDADDR(int r, int c)
{
  return __libc_conio_pf_VIDADDR(r,c);
}
unsigned __libc_conio_VOFFSET(int r, int c)
{
  return __libc_conio_pf_VOFFSET(r,c);
}


// #define INCL_IBMPC

void
_conio_bell_dos(void)
{
  __dpmi_regs regs;

  regs.h.al = 0x07;
  __dpmi_int(0x29, &regs);
}

void
_conio_bell(void)
{
  __libc_conio_pf__conio_bell();
}

int
puttext(int c, int r, int c2, int r2, void *buf)
{
  return __libc_conio_pf_puttext(c, r, c2, r2, buf);
}

int
_conio_gettext(int c, int r, int c2, int r2, void *buf)
{
  return __libc_conio_pf__conio_gettext(c, r, c2, r2, buf);
}
        
void
gotoxy(int col, int row)
{
  ScreenSetCursor(row + txinfo.wintop - 2, col + txinfo.winleft - 2);
  txinfo.curx = col;
  txinfo.cury = row;
}

int
wherex(void)
{
  int row, col;
  
  ScreenGetCursor(&row, &col);
  
  return col - txinfo.winleft + 2;
}

int
wherey(void)
{
  int row, col;
  
  ScreenGetCursor(&row, &col);
  
  return row - txinfo.wintop + 2;
}

void
textmode(int mode)
{
  __libc_conio_pf_textmode(mode);
}
    
void
textattr(int attr)
{
  txinfo.attribute = ScreenAttrib = (unsigned char)attr;
}

void
textcolor(int color)
{
  /* strip blinking (highest) bit and textcolor */
  int bg = ScreenAttrib & (intense_bg_mode ? 0xf0 : 0x70);
  txinfo.attribute = (bg | (color & (intense_bg_mode ? 0x0f : 0x8f)));
  ScreenAttrib = txinfo.attribute;
}

void
textbackground(int color)
{
  /* strip background color from ScreenAttrib, keep blinking bit */
  int fg = ScreenAttrib & (intense_bg_mode ? 0x0f : 0x8f);

  /* high intensity background colors (>7) are not allowed, unless
     intense_bg_mode is on, so we strip 0x08 bit (and higher bits) of color */
  color &= (intense_bg_mode ? 0x0f : 0x07);
  txinfo.attribute = ScreenAttrib = (fg | (color << 4));
}

void
highvideo(void)
{
  txinfo.attribute = (ScreenAttrib |= 0x08);
}

void
lowvideo(void)
{
  txinfo.attribute = (ScreenAttrib &= 0xf7);
}

void
normvideo(void)
{
  txinfo.attribute = ScreenAttrib = txinfo.normattr;
}

void
_setcursortype(int type)
{
  __libc_conio_pf__setcursortype(type);
}

static void
getwincursor(int *row, int *col)
{
  ScreenGetCursor(row, col);
}

void
clreol(void)
{
  short   image[ 256 ];
  short   val = ' ' | (ScreenAttrib << 8);
  int     c, row, col, ncols;
  
  getwincursor(&row, &col);
  ncols = txinfo.winright - col;
  
  for (c = 0; c < ncols; c++)
    image[ c ] = val;
  
  puttext(col + 1, row + 1, txinfo.winright, row + 1, image);
}

void
clrscr(void)
{
  __libc_conio_pf_clrscr();
}

#define bell _conio_bell

int
putch(int c)
{
  int     row, col;
  
  ScreenGetCursor(&row, &col);
  
  /*  first, handle the character */
  if (c == '\n')
  {
    row++;
  }
  else if (c == '\r')
  {
    col = txinfo.winleft - 1;
  }
  else if (c == '\b')
  {
    if (col > txinfo.winleft - 1)
      col--;  
    else if (row > txinfo.wintop -1)
    {
      /* 
       * Turbo-C ignores this case; we are smarter.
       */
      row--;
      col = txinfo.winright-1;
    }  
  }      
  else if (c == 0x07)
    _conio_bell();
  else {
    ScreenPutChar(c, ScreenAttrib, col, row);
    if (ScreenVirtualSegment != 0)
      refreshvirtualscreen(col, row, 1);
    col++;
  }
  
  /* now, readjust the window     */
  
  if (col >= txinfo.winright)
  {
    col = txinfo.winleft - 1;
    row++;
  }
  
  if (row >= txinfo.winbottom)
  {
    /* scrollwin(0, txinfo.winbottom - txinfo.wintop, 1); */
    if (_wscroll)
    {
      ScreenSetCursor(txinfo.wintop-1,0);
      delline();
    }
    row--;
  }
  
  ScreenSetCursor(row, col);
  txinfo.cury = row - txinfo.wintop + 2;
  txinfo.curx = col - txinfo.winleft + 2;
  return c;
}

int
getche(void)
{
  if (char_avail)
    /*
     * We don't know, wether the ungot char was already echoed
     * we assume yes (for example in cscanf, probably the only
     * place where ungetch is ever called.
     * There is no way to check for this really, because
     * ungetch could have been called with a character that
     * hasn't been got by a conio function.
     * We don't echo again.
     */ 
    return(getch());
  return (putch(getch()));
}

int
getch(void)
{
  __dpmi_regs regs;
  int c;

  /* Flush any buffered output, otherwise they might get confusing
     out-of-order execution (and we get to answer FAQs).  */
  if (isatty(0))
  {
    if ((stdout->_flag&_IOLBF) && isatty(fileno(stdout)))
      fflush(stdout);
    if ((stderr->_flag&_IOLBF) && isatty(fileno(stderr)))
      fflush(stderr);
  }
  if (char_avail)
  {
    c = ungot_char;
    char_avail = 0;
  }
  else
  {
    regs.x.ax = 0x0700;
    __dpmi_int(0x21, &regs);
    c = regs.h.al;
  }
  return(c);
}

int
ungetch(int c)
{
  if (char_avail)
    return(EOF);
  ungot_char = c;
  char_avail = 1;
  return(c);
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

int
_conio_kbhit(void)
{
  if (char_avail)
    return(1);
  else
    return(kbhit());
}    

/*
 * The next two functions are needed by cscanf
 */
static int
_scan_getche(FILE *fp)
{
  return(getche());
}

static int
_scan_ungetch(int c, FILE *fp)
{
  return(ungetch(c));
}


#ifdef INCL_IBMPC
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
#endif
void
insline(void)
{
  __libc_conio_pf_insline();
}


#ifdef INCL_IBMPC
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
#endif
void
delline(void)
{
  __libc_conio_pf_delline();
}


void
window(int left, int top, int right, int bottom)
{
  if (top < 1 || left < 1 || right > txinfo.screenwidth ||
      bottom > txinfo.screenheight)
    return;
  
  txinfo.wintop = top;
  txinfo.winleft = left;
  txinfo.winright = right;
  txinfo.winbottom = bottom;
  gotoxy(1,1);
}


#ifdef INCL_IBMPC
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
#endif
int
cputs(const char *s)
{
  return __libc_conio_pf_cputs(s);
}


int
cprintf(const char *fmt, ...)
{
  int     cnt;
  char    buf[ 2048 ];		/* this is buggy, because buffer might be too small. */
  va_list ap;
  
  va_start(ap, fmt);
  cnt = vsnprintf(buf, sizeof(buf), fmt, ap);
  va_end(ap);
  
  cputs(buf);
  return cnt;
}

char *
cgets(char *string)
{
  unsigned len = 0;
  unsigned int maxlen_wanted;
  char *sp;
  int c;
  /*
   * Be smart and check for NULL pointer.
   * Don't know wether TURBOC does this.
   */
  if (!string)
    return(NULL);
  maxlen_wanted = (unsigned int)((unsigned char)string[0]);
  sp = &(string[2]);
  /* 
   * Should the string be shorter maxlen_wanted including or excluding
   * the trailing '\0' ? We don't take any risk.
   */
  while(len < maxlen_wanted-1)
  {
    c=getch();
    /*
     * shold we check for backspace here?
     * TURBOC does (just checked) but doesn't in cscanf (thats harder
     * or even impossible). We do the same.
     */
    if (c == '\b')
    {
      if (len > 0)
      {
	cputs("\b \b");		/* go back, clear char on screen with space
				   and go back again */
	len--;
	sp[len] = '\0';		/* clear the character in the string */
      }
    }
    else if (c == '\r')
    {
      sp[len] = '\0';
      break;
    }
    else if (c == 0)
    {
      /* special character ends input */
      sp[len] = '\0';
      ungetch(c);		/* keep the char for later processing */
      break;
    }
    else
    {
      sp[len] = putch(c);
      len++;
    }
  }
  sp[maxlen_wanted-1] = '\0';
  string[1] = (char)((unsigned char)len);
  return(sp);   
}    

int
cscanf(const char *fmt, ...)
{
  va_list args;
  int ret;

  va_start(args, fmt);
  ret = _doscan_low(NULL, _scan_getche, _scan_ungetch, fmt, args);
  va_end(args);

  return(ret);
}

int
movetext(int left, int top, int right, int bottom, int dleft, int dtop)
{
  char    *buf = alloca((right - left + 1) * (bottom - top + 1) * 2);
  
  _conio_gettext(left, top, right, bottom, buf);
  puttext(dleft, dtop, dleft + right - left, dtop + bottom - top, buf);
  return 1;
}

void
_conio_gettextinfo(struct text_info *t)
{
  int row, col;
  
  t->winleft = t->wintop = 1;
  t->winright = t->screenwidth = ScreenCols();
  t->winbottom = t->screenheight = ScreenRows();
  ScreenAttrib = t->attribute = __libc_conio_get_screenattrib();
  t->normattr = __libc_conio_oldattrib;
  t->currmode = __libc_conio_getvideomode();
  ScreenGetCursor(&row, &col);
  t->curx = col+1;
  t->cury = row+1;
#if DBGGTINFO
  printf("left=%2d,right=%2d,top=%2d,bottom=%2d\n",t->winleft,
	 t->winright,t->wintop,t->winbottom);
  printf("scrht=%2d,scrwid=%2d,norm=%2x,mode=%2d,x=%2d,y=%2d\n",
	 t->screenheight, t->screenwidth, t->normattr, t->currmode,
	 t->curx, t->cury);
#endif
}

int __libc_conio_get_screenattrib(void)
{
  return __libc_conio_pf_get_screenattrib();
}

void
gettextinfo(struct text_info *t)
{
  *t = txinfo; 
#if DBGGTINFO
  printf("left=%2d,right=%2d,top=%2d,bottom=%2d\n",t->winleft,
	 t->winright,t->wintop,t->winbottom);
  printf("scrht=%2d,scrwid=%2d,norm=%2x,mode=%2d,x=%2d,y=%2d\n",
	 t->screenheight, t->screenwidth, t->normattr, t->currmode,
	 t->curx, t->cury);
#endif
}

int
__libc_conio_getvideomode(void)
{
  int mode = ScreenMode();
  /* 
   * in mode C80 we might have loaded a different font
   */
  if (mode == C80)
    if (ScreenRows() > 25)
      mode = C4350;
  return(mode);
}

void
_set_screen_lines(int nlines)
{
  __libc_conio_pf__set_screen_lines(nlines);
}

void
blinkvideo(void)
{
  __libc_conio_pf_blinkvideo();
}

void
intensevideo(void)
{
  __libc_conio_pf_intensevideo();
}


void
gppconio_init(void)
{
  /* Force initialization in restarted programs (emacs).  */
  if (__libc_conio_conio_count != __bss_count)
    {
      __libc_conio_conio_count = __bss_count;
      __libc_conio_oldattrib = -1;
      __libc_conio_last_mode = 0xffff;
      __libc_conio_font_seg = -1;
    }

  switch(__crt0_machine_type)
  {
#ifdef SUPPORT_IBMPC
    case MACHINE_TYPE_IBMPC:
      __libc_conio_pf_puttext = puttext_ibmpc;
      __libc_conio_pf__conio_gettext = _conio_gettext_ibmpc;
      __libc_conio_pf_textmode = textmode_ibmpc;
      __libc_conio_pf__setcursortype = _setcursortype_ibmpc;
      __libc_conio_pf_clrscr = clrscr_ibmpc;
      __libc_conio_pf_insline = insline_ibmpc;
      __libc_conio_pf_delline = delline_ibmpc;
      __libc_conio_pf_cputs = cputs_ibmpc;
      __libc_conio_pf__set_screen_lines = _set_screen_lines_ibmpc;
      __libc_conio_pf_blinkvideo = blinkvideo_ibmpc;
      __libc_conio_pf_intensevideo = intensevideo_ibmpc;
      __libc_conio_pf__conio_refreshvirtualscreen = _conio_refreshvirtualscreen_ibmpc;
      /*
      __libc_conio_pf_VIDADDR = __libc_conio_VIDADDR_ibmpc;
      __libc_conio_pf_VOFFSET = __libc_conio_VOFFSET_ibmpc;
      */
      __libc_conio_pf_get_screenattrib = __libc_conio_get_screenattrib_ibmpc;
      __libc_conio_init_sub_ibmpc();
      break;
#endif
#if defined SUPPORT_NEC98
    case MACHINE_TYPE_NEC98:
      __libc_conio_pf_puttext = puttext_nec98;
      __libc_conio_pf__conio_gettext = _conio_gettext_nec98;
      __libc_conio_pf_textmode = textmode_nec98;
      __libc_conio_pf__setcursortype = _setcursortype_nec98;
      __libc_conio_pf_clrscr = clrscr_nec98;
      __libc_conio_pf_insline = insline_nec98;
      __libc_conio_pf_delline = delline_nec98;
      __libc_conio_pf_cputs = cputs_nec98;
      __libc_conio_pf__set_screen_lines = _set_screen_lines_nec98;
      __libc_conio_pf_blinkvideo = blinkvideo_nec98;
      __libc_conio_pf_intensevideo = intensevideo_nec98;
      __libc_conio_pf__conio_refreshvirtualscreen = _conio_refreshvirtualscreen_nec98;
      /*
      __libc_conio_pf_VIDADDR = __libc_conio_VIDADDR_nec98;
      __libc_conio_pf_VOFFSET = __libc_conio_VOFFSET_nec98;
      */
      __libc_conio_pf_get_screenattrib = __libc_conio_get_screenattrib_nec98;
      __libc_conio_init_sub_nec98();
      break;
#endif
    default:
      ABORT_UNSUPPORTED;
      break;
  }

  if (ScreenVirtualSegment != 0)
    ScreenAddress = (ScreenVirtualSegment << 4UL) + ScreenVirtualOffset;
  ScreenPrimary = ScreenAddress;

#if 0
  /* Why should gppconio_init() restore OLDATTRIB?  I think it
     shouldn't, because this causes change of colors when all
     user wants is to update TXINFO.  And besides, _gettextinfo()
     above has already set ScreenAttrib.  */
  ScreenAttrib = txinfo.normattr = txinfo.attribute = oldattrib;
#endif
}

__asm__(".section .ctor; .long _gppconio_init; .section .text");
