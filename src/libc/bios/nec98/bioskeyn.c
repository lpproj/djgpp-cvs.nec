/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <bios.h>
#include <dpmi.h>
#include <libc/_machine.h>
#include "../common/_bios.h"

#define PC98_KEYS   0x6C

static unsigned short conv_at98_bioskeytbl[PC98_KEYS][4] = {
/*          shift    ctrl    grph   */
/* 0x00 */
  { 0x011B, 0x011B, 0x011B, 0x0100 },	/* ESC	: ESC	ESC		*/
  { 0x0231, 0x0221, 0x0231, 0x7800 },	/* 1	: 1	!		*/
  { 0x0332, 0x2822, 0x0300, 0x7900 },	/* 2	: 2	"		*/
  { 0x0433, 0x0423, 0x0433, 0x7B00 },	/* 3	: 3	#		*/
  { 0x0534, 0x0524, 0x0534, 0x7B00 },	/* 4	: 4	$		*/
  { 0x0635, 0x0625, 0x0635, 0x7C00 },	/* 5	: 5	%		*/
  { 0x0736, 0x0826, 0x071E, 0x7D00 },	/* 6	: 6	&		*/
  { 0x0837, 0x2827, 0x0837, 0x7e00 },	/* 7	: 7	'		*/
  { 0x0938, 0x0A28, 0x0938, 0x7f00 },	/* 8	: 8	(		*/
  { 0x0A39, 0x0B29, 0x0A39, 0x8000 },	/* 9	: 9	)		*/
  { 0x0B30, 0x0B00, 0x0B30, 0x8100 },	/* 0	: 0			*/
  { 0x0C2D, 0x0D3D, 0x0C1F, 0x8200 },	/* -	: -	=		*/
  { 0x075E, 0x2960, 0x075E, 0x8300 },	/* ^	: ^	`		*/
  { 0x7D5C, 0x7D7C, 0x7D1C, 0x2B00 },	/* \	: \	|		*/
  { 0x0E08, 0x0E08, 0x0E7F, 0x0E00 },	/* BS	: BS			*/
  { 0x0F09, 0x0F00, 0x9400, 0xA500 },	/* TAB	: TAB			*/
/* 0x10 */
  { 0x1071, 0x1051, 0x1011, 0x1000 },	/* Q	: q	Q		*/
  { 0x1177, 0x1157, 0x1117, 0x1100 },	/* W	: w	W		*/
  { 0x1265, 0x1245, 0x1205, 0x1200 },	/* E	: e	E		*/
  { 0x1372, 0x1352, 0x1312, 0x1300 },	/* R	: r	R		*/
  { 0x1474, 0x1454, 0x1414, 0x1400 },	/* T	: t	T		*/
  { 0x1579, 0x1559, 0x1519, 0x1500 },	/* Y	: y	Y		*/
  { 0x1675, 0x1655, 0x1615, 0x1600 },	/* U	: u	U		*/
  { 0x1769, 0x1749, 0x1709, 0x1700 },	/* I	: i	I		*/
  { 0x186F, 0x184F, 0x180F, 0x1800 },	/* O	: o	O		*/
  { 0x1970, 0x1950, 0x1910, 0x1900 },	/* P	: p	P		*/
  { 0x0340, 0x297E, 0x0340, 0x0300 },	/* @	: @	~		*/
  { 0x1A5B, 0x1A7B, 0x1A1B, 0x1A00 },	/* [	: [	{		*/
  { 0x1C0D, 0x1C0D, 0x1C0A, 0x1C00 },	/* CR	: CR			*/
  { 0x1E61, 0x1E41, 0x1E01, 0x1E00 },	/* A	: a	A		*/
  { 0x1F73, 0x1F53, 0x1F13, 0x1F00 },	/* S	: s	S		*/
  { 0x2064, 0x2044, 0x2004, 0x2000 },	/* D	: d	D		*/
/* 0x20 */
  { 0x2166, 0x2146, 0x2106, 0x2100 },	/* F	: f	F		*/
  { 0x2267, 0x2247, 0x2207, 0x2200 },	/* G	: g	G		*/
  { 0x2368, 0x2348, 0x2308, 0x2300 },	/* H	: h	H		*/
  { 0x246A, 0x244A, 0x240A, 0x2400 },	/* J	: j	J		*/
  { 0x256B, 0x254B, 0x250B, 0x2500 },	/* K	: k	K		*/
  { 0x266C, 0x264C, 0x260C, 0x2600 },	/* L	: l	L		*/
  { 0x273B, 0x0D2B, 0x273B, 0x2700 },	/* ;	: ;	+		*/
  { 0x273A, 0x092A, 0x273A, 0x2700 },	/* :	: :	*		*/
  { 0x1B5D, 0x1B7D, 0x1B1D, 0x1B00 },	/* ]	: ]	}		*/
  { 0x2C7A, 0x2C5A, 0x2C1A, 0x2C00 },	/* Z	: z	Z		*/
  { 0x2D78, 0x2D58, 0x2D18, 0x2D00 },	/* X	: x	X		*/
  { 0x2E63, 0x2E43, 0x2E03, 0x2E00 },	/* C	: c	C		*/
  { 0x2F76, 0x2F56, 0x2F16, 0x2F00 },	/* V	: v	V		*/
  { 0x3262, 0x3242, 0x3002, 0x3000 },	/* B	: b	B		*/
  { 0x316E, 0x314E, 0x310E, 0x3100 },	/* N	: n	N		*/
  { 0x326D, 0x324D, 0x320D, 0x3200 },	/* M	: m	M		*/
/* 0x30 */
  { 0x332C, 0x333C, 0x332C, 0x3300 },	/* ,	: ,	<	,	*/
  { 0x342E, 0x343E, 0x342E, 0x3400 },	/* .	: .	>	.	*/
  { 0x352F, 0x353F, 0x352F, 0x3500 },	/* /	: /	?	/	*/
  { 0x0C5F, 0x0C5F, 0x0C5F, 0x0C00 },	/* _	: _	_	_	*/
  { 0x3920, 0x3920, 0x3920, 0x3920 },	/* SPC	: SPC	SPC	SPC	*/
  { 0x3A00, 0x3A00, 0x3A00, 0x3A00 },	/* XFER	: 漢字			*/
  { 0x51E0, 0x51E0, 0x76E0, 0xA100 },	/* RUP	: PDN			*/
  { 0x49E0, 0x49E0, 0x84E0, 0x9900 },	/* RDN	: PUP			*/
  { 0x52E0, 0x52E0, 0x92E0, 0xA200 },	/* INS	: INS			*/
  { 0x53E0, 0x53E0, 0x93E0, 0xA300 },	/* DEL	: DEL			*/
  { 0x48E0, 0x48E0, 0x8DE0, 0x9800 },	/* 上	: 上			*/
  { 0x4BE0, 0x4BE0, 0x73E0, 0x9B00 },	/* 左	: 左			*/
  { 0x4DE0, 0x4DE0, 0x74E0, 0x9D00 },	/* 右	: 右			*/
  { 0x50E0, 0x50E0, 0x91E0, 0xA000 },	/* 下	: 下			*/
  { 0x47E0, 0x47E0, 0x77E0, 0x9700 },	/* HOME	: HOME			*/
  { 0x4FE0, 0x4FE0, 0x75E0, 0x9F00 },	/* HELP	: END			*/
/* 0x40 */
  { 0x4A2D, 0x4A2D, 0x8E00, 0x4A00 },	/* -	: -			*/
  { 0xE02F, 0xE02F, 0x9500, 0xA400 },	/* /	: /			*/
  { 0x4737, 0x4737, 0x7700, 0x4737 },	/* 7	: 7			*/
  { 0x4838, 0x4838, 0x8D00, 0x4838 },	/* 8	: 8			*/
  { 0x4939, 0x4939, 0x8400, 0x4939 },	/* 9	: 9			*/
  { 0x372A, 0x372A, 0x9600, 0x3700 },	/* *	: *			*/
  { 0x4B34, 0x4B34, 0x7300, 0x4B34 },	/* 4	: 4			*/
  { 0x4C35, 0x4C35, 0x8F00, 0x4C35 },	/* 5	: 5			*/
  { 0x4D36, 0x4D36, 0x7400, 0x4D36 },	/* 6	: 6			*/
  { 0x4E2B, 0x4E2B, 0x9000, 0x4E00 },	/* +	: +			*/
  { 0x4F31, 0x4F31, 0x7500, 0x4F31 },	/* 1	: 1			*/
  { 0x5032, 0x5032, 0x9100, 0x5032 },	/* 2	: 2			*/
  { 0x5133, 0x5133, 0x7600, 0x5133 },	/* 3	: 3			*/
  { 0x0D3D, 0x0D3D, 0x0D3D, 0x0D3D },	/* =	: =			*/
  { 0x5230, 0x5230, 0x9200, 0x5230 },	/* 0	: 0			*/
  { 0x332C, 0x332C, 0x332C, 0x332C },	/* ,	: ,			*/
/* 0x50 */
  { 0x532E, 0x532E, 0x9300, 0x532E },	/* .	: .			*/
  { 0xA700, 0xA800, 0xA900, 0xAA00 },	/* NFER	: 変換			*/
  { 0x8500, 0x8700, 0x8900, 0x8B00 },	/* vf1	: f11			*/
  { 0x8600, 0x8800, 0x8A00, 0x8C00 },	/* vf2	: f12			*/
  { 0xAB00, 0xAC00, 0xAD00, 0xAE00 },	/* vf3	: 無変換		*/
  { 0xA700, 0xA800, 0xA900, 0xAA00 },	/* vf4	: 変換			*/
  { 0xB600, 0xB700, 0xB800, 0xB900 },	/* vf5	: かな			*/
  { 0x0000, 0x0000, 0x0000, 0x0000 },	/*	:			*/
  { 0x0000, 0x0000, 0x0000, 0x0000 },	/*	:			*/
  { 0x0000, 0x0000, 0x0000, 0x0000 },	/*	:			*/
  { 0x0000, 0x0000, 0x0000, 0x0000 },	/*	:			*/
  { 0x0000, 0x0000, 0x0000, 0x0000 },	/*	:			*/
  { 0x0000, 0x0000, 0x0000, 0x0000 },	/*	:			*/
  { 0x0000, 0x0000, 0x0000, 0x0000 },	/*	:			*/
  { 0x0000, 0x0000, 0x0000, 0x0000 },	/*	:			*/
  { 0x0000, 0x0000, 0x0000, 0x0000 },	/*	:			*/
/* 0x60 */
  { 0x0000, 0x0000, 0x0000, 0x0000 },	/* STOP	:			*/
  { 0x0000, 0x0000, 0x0000, 0x0000 },	/* COPY	:			*/
  { 0x3B00, 0x5400, 0x5E00, 0x6800 },	/* f01	: f01			*/
  { 0x3C00, 0x5500, 0x5F00, 0x6900 },	/* f02	: f02			*/
  { 0x3D00, 0x5600, 0x6000, 0x6A00 },	/* f03	: f03			*/
  { 0x3E00, 0x5700, 0x6100, 0x6B00 },	/* f04	: f04			*/
  { 0x3F00, 0x5800, 0x6200, 0x6C00 },	/* f05	: f05			*/
  { 0x4000, 0x5900, 0x6300, 0x6D00 },	/* f06	: f06			*/
  { 0x4100, 0x5A00, 0x6400, 0x6E00 },	/* f07	: f07			*/
  { 0x4200, 0x5B00, 0x6500, 0x6F00 },	/* f08	: f08			*/
  { 0x4300, 0x5C00, 0x6600, 0x7000 },	/* f09	: f09			*/
  { 0x4400, 0x5D00, 0x6700, 0x7100 }	/* f10	: f10			*/
};

static int conv_at98_bioskey(unsigned char ah)
{
  int shift = 0, keycode;
  __dpmi_regs r;

  if ( ah >= 0x80 ) {
    if ( ah == 0xA1 || ah == 0xB1 ) {		/* NFER  : 0xA1 0xB1 */
      ah = 0x51;
    } else if ( ah == 0xA5 || ah == 0xB5 ) {	/* XFER  : 0xA5 0xB5 */
      ah = 0x35;
    } else if ( ah == 0xAE ) {			/* HOME  : 0xAE */
      ah = 0x3E;
    } else if ( ah >= 0xC0 ) {			/* VF1-5 : 0xC2-C6 */
      ah &= 0x0f;
      ah |= 0x50;
    } else {					/* F1-10 : 0x82-8B 0x92-9B */
      ah &= 0x0f;
      ah |= 0x60;
    }
  }

  if ( ah >= PC98_KEYS )
    return 0;

  r.h.ah = 2;
  __dpmi_int(0x18, &r);
  if ( r.h.al & 0x08 )		/* GRPH */
    shift = 0x03;
  else if ( r.h.al & 0x10 )	/* CTRL */
    shift = 0x02;
  else if ( r.h.al & 0x01 )	/* SHIFT */
    shift = 0x01;

  keycode = conv_at98_bioskeytbl[ah][shift];

  if ( r.h.al & 0x02 ) {	/* CAPS */
    if ( 'a' <= (keycode & 0xff) && (keycode & 0xff) <= 'z' )
      keycode &= 0xffdf;
    else if ( 'A' <= (keycode & 0xff) && (keycode & 0xff) <= 'Z' )
      keycode |= 0x0020;
  }

  return keycode;
}

int bioskey_nec98_noconv(int cmd)
{
  unsigned val = 0;
  __dpmi_regs r;

  if (cmd < 9)
  {
    r.d.eax = r.d.ebx = 0;
    r.h.ah = cmd;
    __dpmi_int(0x18, &r);
    switch( cmd )
    {
      case 0x00:
        val = r.x.ax;
        break;
      case 0x01:
      case 0x05:
        if (r.h.bl) val = r.x.ax;
        break;
      case 0x02:
        val = r.h.al;
        break;
      case 0x07:
      case 0x08:
        val = ((unsigned)(r.x.bx) << 16) | r.x.ax;
        break;
    }
  }
  return (int)val;
}


int bioskey_nec98(int cmd)
{
  int shift = 0;
  __dpmi_regs r;

  r.d.eax = r.d.ebx = 0;
  r.h.ah = cmd & 0x0f;
  if (((unsigned)cmd & ~0x10U) <= 0x02)
  {
    __dpmi_int(0x18, &r);
  }
  switch ( cmd ) {
  case 0x00:
  case 0x10:
    return conv_at98_bioskey(r.h.ah);
  case 0x01:
  case 0x11:
    if ( !r.h.bh )
      return 0;
    else
      r.x.ax = conv_at98_bioskey(r.h.ah);
    return (!r.x.ax) ? -1 : r.x.ax;
  case 0x12:
    if ( r.h.al & 0x10 )
      shift |= 0x0500;
    if ( r.h.al & 0x08 )
      shift |= 0x0A00;
    if ( r.h.al & 0x04 )
      shift |= 0x1000;
    if ( r.h.al & 0x02 )
      shift |= 0x4000;
  case 0x02:
    if ( r.h.al & 0x01 )
      shift |= 0x03;
    if ( r.h.al & 0x10 )
      shift |= 0x04;
    if ( r.h.al & 0x08 )
      shift |= 0x08;
    if ( r.h.al & 0x04 )
      shift |= 0x10;
    if ( r.h.al & 0x02 )
      shift |= 0x40;
    return shift;
  }
  return 0;
}
