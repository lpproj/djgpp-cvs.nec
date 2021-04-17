/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <bios.h>
#include <dpmi.h>
#include <go32.h>
#include <libc/farptrgs.h>
#include <libc/_machine.h>
#include "../common/_bios.h"

#define IBM_BUSY        0x00
#define IBM_NOTBUSY     0x80
#define IBM_ACK         0x40
#define IBM_OUTOFPAPER  0x20
#define IBM_SELECTED    0x10
#define IBM_PRNERR      0x08
#define IBM_PRNTIMEOUT  0x01

int biosprint_nec98(int cmd, int byte, int port)
{
  unsigned char mem0458 = _farpeekb(_dos_ds, 0x0458);
  int is_fullcentronics = (mem0458 & 0x82) && (mem0458 & 4);
  int status = 0;
  __dpmi_regs r;

  if ( port )
    return 0;

  r.h.al = byte;
  switch ( cmd )
  {
    case 0: /* send data */
      r.h.ah = 0x11;
      break;
    case 1: /* initialize */
      r.h.ah = 0x10;
      break;
    case 2: /* get status */
      r.h.ah = 0x12;
      break;
    default:
      return 0;
  }

  __dpmi_int(0x1a, &r);

  switch ( r.h.al )
  {
    case 0x00:
      status = (is_fullcentronics ? IBM_NOTBUSY : IBM_BUSY) | IBM_SELECTED;
      break;
    case 0x01:
      status = (is_fullcentronics ? IBM_BUSY : IBM_NOTBUSY) | IBM_SELECTED;
      break;
    case 0x02:
      status = IBM_PRNTIMEOUT | IBM_SELECTED;
      break;
    case 0x03:  /* offline */
      break;
    case 0x04:
      status = IBM_OUTOFPAPER | IBM_SELECTED;
      break;
    case 0x05: /* printer not ready */
      break;
    default: /* unknown */
      status = IBM_PRNERR;
      break;
  }
  return status;
}
