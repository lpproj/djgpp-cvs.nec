/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <dos.h>
#include <dpmi.h>
#include <libc/_machine.h>
#include <go32.h>
#include <libc/farptrgs.h>
#include "../common/_dos.h"

void delay_nec98(unsigned msec)
{
  int tmstmp = (__crt0_machine_subtype == MACHINE_SUBTYPE_NEC98_HIRES || _farpeekb(_dos_ds, 0x45B) & 0x04);
  unsigned hscan = 0, msec_this, i;

  if ( !tmstmp ) {
    if ( _farpeekb(_dos_ds, 0x501) & 0x08 ) {
      hscan = 3284; /* 32.86kHz interlace */
      if ( _farpeekb(_dos_ds, 0x54C) & 0x20 )
        if ( _farpeekb(_dos_ds, 0x459) & 0x08 )
          hscan = 5000; /* 50.02kHz non-interlace */
    } else {
      if ( _farpeekb(_dos_ds, 0x54C) & 0x20 ) {
        hscan = 3145;   /* 31.47kHz */
      } else {
        if ( _farpeekb(_dos_ds, 0x53C) & 0x80 )
          hscan = 2481; /* 24.83kHz PC-9800 CRT */
        else
          hscan = 1596; /* 15.98kHz PC-8800 CRT */
      }
    }
  }

  while ( msec ) {
    msec_this = (msec > 8000) ? 8000 : msec;
    if ( tmstmp ) {
      i = msec_this * 6 / 5;
      hscan = inportw(0x5e);
      while ( (inportw(0x5e) - hscan) < i );
    } else {
      i = hscan * msec_this / 100;
      while (i--) {
        while ( !(inportb(0x60) & 0x40) );
        while ( inportb(0x60) & 0x40 );
      }
    }
    msec -= msec_this;
  }
}
