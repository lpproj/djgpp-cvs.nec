#include <dpmi.h>
#include <go32.h>
#include <conio.h>
#include <stdlib.h>
#include <libc/_machine.h>
#include "../sc.h"
#include "../common/_co80.h"

static void ScreenClear_setup(void);
static int ScreenCols_setup(void);
static void ScreenGetCursor_setup(int *_row, int *_col);
static void ScreenGetChar_setup(int *_ch, int *_attr, int _x, int _y);
static int ScreenMode_setup(void);
static void ScreenPutChar_setup(int _ch, int _attr, int _x, int _y);
static void ScreenPutString_setup(const char *_ch, int _attr, int _x, int _y);
static void ScreenRetrieve_setup(void *_virtual_screen);
static int ScreenRows_setup(void);
static void ScreenSetCursor_setup(int _row, int _col);
static void ScreenUpdate_setup(const void *_virtual_screen);
static void ScreenUpdateLine_setup(const void *_virtual_screen_line, int _row);
static void ScreenVisualBell_setup(void);


void (*__libc_co80_pf_ScreenClear)(void) = ScreenClear_setup;
int (*__libc_co80_pf_ScreenCols)(void) = ScreenCols_setup;
void (*__libc_co80_pf_ScreenGetCursor)(int *_row, int *_col) = ScreenGetCursor_setup;
void (*__libc_co80_pf_ScreenGetChar)(int *_ch, int *_attr, int _x, int _y) = ScreenGetChar_setup;
int (*__libc_co80_pf_ScreenMode)(void) = ScreenMode_setup;
void (*__libc_co80_pf_ScreenPutChar)(int _ch, int _attr, int _x, int _y) = ScreenPutChar_setup;
void (*__libc_co80_pf_ScreenPutString)(const char *_ch, int _attr, int _x, int _y) = ScreenPutString_setup;
void (*__libc_co80_pf_ScreenRetrieve)(void *_virtual_screen) = ScreenRetrieve_setup;
int (*__libc_co80_pf_ScreenRows)(void) = ScreenRows_setup;
void (*__libc_co80_pf_ScreenSetCursor)(int _row, int _col) = ScreenSetCursor_setup;
void (*__libc_co80_pf_ScreenUpdate)(const void *_virtual_screen) = ScreenUpdate_setup;
void (*__libc_co80_pf_ScreenUpdateLine)(const void *_virtual_screen_line, int _row) = ScreenUpdateLine_setup;
void (*__libc_co80_pf_ScreenVisualBell)(void) = ScreenVisualBell_setup;

static void _co80_Screen_setup(void)
{
  switch(__crt0_machine_type) {
#ifdef SUPPORT_IBMPC
    case MACHINE_TYPE_IBMPC:
      __libc_co80_pf_ScreenClear = ScreenClear_ibmpc;
      __libc_co80_pf_ScreenCols = ScreenCols_ibmpc;
      __libc_co80_pf_ScreenGetCursor = ScreenGetCursor_ibmpc;
      __libc_co80_pf_ScreenGetChar = ScreenGetChar_ibmpc;
      __libc_co80_pf_ScreenMode = ScreenMode_ibmpc;
      __libc_co80_pf_ScreenRetrieve = ScreenRetrieve_ibmpc;
      __libc_co80_pf_ScreenRows = ScreenRows_ibmpc;
      __libc_co80_pf_ScreenSetCursor = ScreenSetCursor_ibmpc;
      __libc_co80_pf_ScreenUpdate = ScreenUpdate_ibmpc;
      __libc_co80_pf_ScreenUpdateLine = ScreenUpdateLine_ibmpc;
      __libc_co80_pf_ScreenVisualBell = ScreenVisualBell_ibmpc;
      break;
#endif
#ifdef SUPPORT_NEC98
    case MACHINE_TYPE_NEC98:
      __libc_co80_pf_ScreenClear = ScreenClear_nec98;
      __libc_co80_pf_ScreenCols = ScreenCols_nec98;
      __libc_co80_pf_ScreenGetCursor = ScreenGetCursor_nec98;
      __libc_co80_pf_ScreenGetChar = ScreenGetChar_nec98;
      __libc_co80_pf_ScreenMode = ScreenMode_nec98;
      __libc_co80_pf_ScreenRetrieve = ScreenRetrieve_nec98;
      __libc_co80_pf_ScreenRows = ScreenRows_nec98;
      __libc_co80_pf_ScreenSetCursor = ScreenSetCursor_nec98;
      __libc_co80_pf_ScreenUpdate = ScreenUpdate_nec98;
      __libc_co80_pf_ScreenUpdateLine = ScreenUpdateLine_nec98;
      __libc_co80_pf_ScreenVisualBell = ScreenVisualBell_nec98;
      break;
#endif
    default:
      ABORT_UNSUPPORTED;
  }
}


static void ScreenClear_setup(void)
{
  _co80_Screen_setup();
  __libc_co80_pf_ScreenClear();
}

static int ScreenCols_setup(void)
{
  _co80_Screen_setup();
  return __libc_co80_pf_ScreenCols();
}

static void ScreenGetCursor_setup(int *_row, int *_col)
{
  _co80_Screen_setup();
  __libc_co80_pf_ScreenGetCursor(_row, _col);
}

static void ScreenGetChar_setup(int *_ch, int *_attr, int _x, int _y)
{
  _co80_Screen_setup();
  __libc_co80_pf_ScreenGetChar(_ch, _attr, _x, _y);
}

static int ScreenMode_setup(void)
{
  _co80_Screen_setup();
  return __libc_co80_pf_ScreenMode();
}

static void ScreenPutChar_setup(int _ch, int _attr, int _x, int _y)
{
  _co80_Screen_setup();
  __libc_co80_pf_ScreenPutChar(_ch, _attr, _x, _y);
}

static void ScreenPutString_setup(const char *_ch, int _attr, int _x, int _y)
{
  _co80_Screen_setup();
  __libc_co80_pf_ScreenPutString(_ch, _attr, _x, _y);
}


static void ScreenRetrieve_setup(void *_virtual_screen)
{
  _co80_Screen_setup();
  __libc_co80_pf_ScreenRetrieve(_virtual_screen);
}

static int ScreenRows_setup(void)
{
  _co80_Screen_setup();
  return __libc_co80_pf_ScreenRows();
}

static void ScreenSetCursor_setup(int _row, int _col)
{
  _co80_Screen_setup();
  __libc_co80_pf_ScreenSetCursor(_row, _col);
}

static void ScreenUpdate_setup(const void *_virtual_screen)
{
  _co80_Screen_setup();
  __libc_co80_pf_ScreenUpdate(_virtual_screen);
}

static void ScreenUpdateLine_setup(const void *_virtual_screen_line, int _row)
{
  _co80_Screen_setup();
  __libc_co80_pf_ScreenUpdateLine(_virtual_screen_line, _row);
}

static void ScreenVisualBell_setup(void)
{
  _co80_Screen_setup();
  __libc_co80_pf_ScreenVisualBell();
}

