#include "test.h"
 one_line_type floorf_vec[] = {
{34, 0, 0,__LINE__, {{0xc0200000, 0x00000000}, {0xc01c0002, 0x00000000}}},	/* -8.0000E+00=F(      -7) */
{34, 0, 0,__LINE__, {{0xc01c0000, 0x00000000}, {0xc01b0002, 0x00000000}}},	/* -7.0000E+00=F(   -6.75) */
{34, 0, 0,__LINE__, {{0xc01c0000, 0x00000000}, {0xc01a0002, 0x00000000}}},	/* -7.0000E+00=F(    -6.5) */
{34, 0, 0,__LINE__, {{0xc01c0000, 0x00000000}, {0xc0190002, 0x00000000}}},	/* -7.0000E+00=F(   -6.25) */
{34, 0, 0,__LINE__, {{0xc01c0000, 0x00000000}, {0xc0180002, 0x00000000}}},	/* -7.0000E+00=F(      -6) */
{34, 0, 0,__LINE__, {{0xc0180000, 0x00000000}, {0xc0170002, 0x00000000}}},	/* -6.0000E+00=F(   -5.75) */
{34, 0, 0,__LINE__, {{0xc0180000, 0x00000000}, {0xc0160002, 0x00000000}}},	/* -6.0000E+00=F(    -5.5) */
{34, 0, 0,__LINE__, {{0xc0180000, 0x00000000}, {0xc0150002, 0x00000000}}},	/* -6.0000E+00=F(   -5.25) */
{34, 0, 0,__LINE__, {{0xc0180000, 0x00000000}, {0xc0140002, 0x00000000}}},	/* -6.0000E+00=F(      -5) */
{34, 0, 0,__LINE__, {{0xc0140000, 0x00000000}, {0xc0100002, 0x00000000}}},	/* -5.0000E+00=F(      -4) */
{34, 0, 0,__LINE__, {{0xc0100000, 0x00000000}, {0xc00f8004, 0x00000000}}},	/* -4.0000E+00=F(  -3.938) */
{34, 0, 0,__LINE__, {{0xc0100000, 0x00000000}, {0xc00f0004, 0x00000000}}},	/* -4.0000E+00=F(  -3.875) */
{34, 0, 0,__LINE__, {{0xc0100000, 0x00000000}, {0xc00e8004, 0x00000000}}},	/* -4.0000E+00=F(  -3.813) */
{34, 0, 0,__LINE__, {{0xc0100000, 0x00000000}, {0xc00e0004, 0x00000000}}},	/* -4.0000E+00=F(   -3.75) */
{34, 0, 0,__LINE__, {{0xc0100000, 0x00000000}, {0xc00d8004, 0x00000000}}},	/* -4.0000E+00=F(  -3.688) */
{34, 0, 0,__LINE__, {{0xc0100000, 0x00000000}, {0xc00d0004, 0x00000000}}},	/* -4.0000E+00=F(  -3.625) */
{34, 0, 0,__LINE__, {{0xc0100000, 0x00000000}, {0xc00c8004, 0x00000000}}},	/* -4.0000E+00=F(  -3.563) */
{34, 0, 0,__LINE__, {{0xc0100000, 0x00000000}, {0xc00c0004, 0x00000000}}},	/* -4.0000E+00=F(    -3.5) */
{34, 0, 0,__LINE__, {{0xc0100000, 0x00000000}, {0xc00b8004, 0x00000000}}},	/* -4.0000E+00=F(  -3.438) */
{34, 0, 0,__LINE__, {{0xc0100000, 0x00000000}, {0xc00b0004, 0x00000000}}},	/* -4.0000E+00=F(  -3.375) */
{34, 0, 0,__LINE__, {{0xc0100000, 0x00000000}, {0xc00a8004, 0x00000000}}},	/* -4.0000E+00=F(  -3.313) */
{34, 0, 0,__LINE__, {{0xc0100000, 0x00000000}, {0xc00a0004, 0x00000000}}},	/* -4.0000E+00=F(   -3.25) */
{34, 0, 0,__LINE__, {{0xc0100000, 0x00000000}, {0xc0098004, 0x00000000}}},	/* -4.0000E+00=F(  -3.188) */
{34, 0, 0,__LINE__, {{0xc0100000, 0x00000000}, {0xc0090004, 0x00000000}}},	/* -4.0000E+00=F(  -3.125) */
{34, 0, 0,__LINE__, {{0xc0100000, 0x00000000}, {0xc0088004, 0x00000000}}},	/* -4.0000E+00=F(  -3.063) */
{34, 0, 0,__LINE__, {{0xc0100000, 0x00000000}, {0xc0080004, 0x00000000}}},	/* -4.0000E+00=F(      -3) */
{34, 0, 0,__LINE__, {{0xc0080000, 0x00000000}, {0xc0078004, 0x00000000}}},	/* -3.0000E+00=F(  -2.938) */
{34, 0, 0,__LINE__, {{0xc0080000, 0x00000000}, {0xc0070004, 0x00000000}}},	/* -3.0000E+00=F(  -2.875) */
{34, 0, 0,__LINE__, {{0xc0080000, 0x00000000}, {0xc0068004, 0x00000000}}},	/* -3.0000E+00=F(  -2.813) */
{34, 0, 0,__LINE__, {{0xc0080000, 0x00000000}, {0xc0060004, 0x00000000}}},	/* -3.0000E+00=F(   -2.75) */
{34, 0, 0,__LINE__, {{0xc0080000, 0x00000000}, {0xc0058004, 0x00000000}}},	/* -3.0000E+00=F(  -2.688) */
{34, 0, 0,__LINE__, {{0xc0080000, 0x00000000}, {0xc0050004, 0x00000000}}},	/* -3.0000E+00=F(  -2.625) */
{34, 0, 0,__LINE__, {{0xc0080000, 0x00000000}, {0xc0048004, 0x00000000}}},	/* -3.0000E+00=F(  -2.563) */
{34, 0, 0,__LINE__, {{0xc0080000, 0x00000000}, {0xc0040004, 0x00000000}}},	/* -3.0000E+00=F(    -2.5) */
{34, 0, 0,__LINE__, {{0xc0080000, 0x00000000}, {0xc0038004, 0x00000000}}},	/* -3.0000E+00=F(  -2.438) */
{34, 0, 0,__LINE__, {{0xc0080000, 0x00000000}, {0xc0030004, 0x00000000}}},	/* -3.0000E+00=F(  -2.375) */
{34, 0, 0,__LINE__, {{0xc0080000, 0x00000000}, {0xc0028004, 0x00000000}}},	/* -3.0000E+00=F(  -2.313) */
{34, 0, 0,__LINE__, {{0xc0080000, 0x00000000}, {0xc0020004, 0x00000000}}},	/* -3.0000E+00=F(   -2.25) */
{34, 0, 0,__LINE__, {{0xc0080000, 0x00000000}, {0xc0018004, 0x00000000}}},	/* -3.0000E+00=F(  -2.188) */
{34, 0, 0,__LINE__, {{0xc0080000, 0x00000000}, {0xc0010004, 0x00000000}}},	/* -3.0000E+00=F(  -2.125) */
{34, 0, 0,__LINE__, {{0xc0080000, 0x00000000}, {0xc0008004, 0x00000000}}},	/* -3.0000E+00=F(  -2.063) */
{34, 0, 0,__LINE__, {{0xc0080000, 0x00000000}, {0xc0000004, 0x00000000}}},	/* -3.0000E+00=F(      -2) */
{34, 0, 0,__LINE__, {{0xc0000000, 0x00000000}, {0xbfff0008, 0x00000000}}},	/* -2.0000E+00=F(  -1.938) */
{34, 0, 0,__LINE__, {{0xc0000000, 0x00000000}, {0xbffe0008, 0x00000000}}},	/* -2.0000E+00=F(  -1.875) */
{34, 0, 0,__LINE__, {{0xc0000000, 0x00000000}, {0xbffd0008, 0x00000000}}},	/* -2.0000E+00=F(  -1.813) */
{34, 0, 0,__LINE__, {{0xc0000000, 0x00000000}, {0xbffc0008, 0x00000000}}},	/* -2.0000E+00=F(   -1.75) */
{34, 0, 0,__LINE__, {{0xc0000000, 0x00000000}, {0xbffb0008, 0x00000000}}},	/* -2.0000E+00=F(  -1.688) */
{34, 0, 0,__LINE__, {{0xc0000000, 0x00000000}, {0xbffa0008, 0x00000000}}},	/* -2.0000E+00=F(  -1.625) */
{34, 0, 0,__LINE__, {{0xc0000000, 0x00000000}, {0xbff90008, 0x00000000}}},	/* -2.0000E+00=F(  -1.563) */
{34, 0, 0,__LINE__, {{0xc0000000, 0x00000000}, {0xbff80008, 0x00000000}}},	/* -2.0000E+00=F(    -1.5) */
{34, 0, 0,__LINE__, {{0xc0000000, 0x00000000}, {0xbff70008, 0x00000000}}},	/* -2.0000E+00=F(  -1.438) */
{34, 0, 0,__LINE__, {{0xc0000000, 0x00000000}, {0xbff60008, 0x00000000}}},	/* -2.0000E+00=F(  -1.375) */
{34, 0, 0,__LINE__, {{0xc0000000, 0x00000000}, {0xbff50008, 0x00000000}}},	/* -2.0000E+00=F(  -1.313) */
{34, 0, 0,__LINE__, {{0xc0000000, 0x00000000}, {0xbff40008, 0x00000000}}},	/* -2.0000E+00=F(   -1.25) */
{34, 0, 0,__LINE__, {{0xc0000000, 0x00000000}, {0xbff30008, 0x00000000}}},	/* -2.0000E+00=F(  -1.188) */
{34, 0, 0,__LINE__, {{0xc0000000, 0x00000000}, {0xbff20008, 0x00000000}}},	/* -2.0000E+00=F(  -1.125) */
{34, 0, 0,__LINE__, {{0xc0000000, 0x00000000}, {0xbff10008, 0x00000000}}},	/* -2.0000E+00=F(  -1.063) */
{34, 0, 0,__LINE__, {{0xc0000000, 0x00000000}, {0xbff00008, 0x00000000}}},	/* -2.0000E+00=F(      -1) */
{34, 0, 0,__LINE__, {{0xbff00000, 0x00000000}, {0xbfee0010, 0x00000000}}},	/* -1.0000E+00=F( -0.9375) */
{34, 0, 0,__LINE__, {{0xbff00000, 0x00000000}, {0xbfec0010, 0x00000000}}},	/* -1.0000E+00=F(  -0.875) */
{34, 0, 0,__LINE__, {{0xbff00000, 0x00000000}, {0xbfea0010, 0x00000000}}},	/* -1.0000E+00=F( -0.8125) */
{34, 0, 0,__LINE__, {{0xbff00000, 0x00000000}, {0xbfe80010, 0x00000000}}},	/* -1.0000E+00=F(   -0.75) */
{34, 0, 0,__LINE__, {{0xbff00000, 0x00000000}, {0xbfe60010, 0x00000000}}},	/* -1.0000E+00=F( -0.6875) */
{34, 0, 0,__LINE__, {{0xbff00000, 0x00000000}, {0xbfe40010, 0x00000000}}},	/* -1.0000E+00=F(  -0.625) */
{34, 0, 0,__LINE__, {{0xbff00000, 0x00000000}, {0xbfe20010, 0x00000000}}},	/* -1.0000E+00=F( -0.5625) */
{34, 0, 0,__LINE__, {{0xbff00000, 0x00000000}, {0xbfe00010, 0x00000000}}},	/* -1.0000E+00=F(    -0.5) */
{34, 0, 0,__LINE__, {{0xbff00000, 0x00000000}, {0xbfdc0020, 0x00000000}}},	/* -1.0000E+00=F( -0.4375) */
{34, 0, 0,__LINE__, {{0xbff00000, 0x00000000}, {0xbfd80020, 0x00000000}}},	/* -1.0000E+00=F(  -0.375) */
{34, 0, 0,__LINE__, {{0xbff00000, 0x00000000}, {0xbfd40020, 0x00000000}}},	/* -1.0000E+00=F( -0.3125) */
{34, 0, 0,__LINE__, {{0xbff00000, 0x00000000}, {0xbfd00020, 0x00000000}}},	/* -1.0000E+00=F(   -0.25) */
{34, 0, 0,__LINE__, {{0xbff00000, 0x00000000}, {0xbfc80040, 0x00000000}}},	/* -1.0000E+00=F( -0.1875) */
{34, 0, 0,__LINE__, {{0xbff00000, 0x00000000}, {0xbfc00040, 0x00000000}}},	/* -1.0000E+00=F(  -0.125) */
{34, 0, 0,__LINE__, {{0xbff00000, 0x00000000}, {0xbfb00080, 0x00000000}}},	/* -1.0000E+00=F(-0.06251) */
{34, 0, 0,__LINE__, {{0xbff00000, 0x00000000}, {0xbee00000, 0x00000000}}},	/* -1.0000E+00=F(-7.629e-06) */
{34, 0, 0,__LINE__, {{0x00000000, 0x00000000}, {0x3ee00000, 0x00000000}}},	/* +0.0000E+00=F(+7.629e-06) */
{34, 0, 0,__LINE__, {{0x00000000, 0x00000000}, {0x3fb00080, 0x00000000}}},	/* +0.0000E+00=F(+0.06251) */
{34, 0, 0,__LINE__, {{0x00000000, 0x00000000}, {0x3fc00040, 0x00000000}}},	/* +0.0000E+00=F(  +0.125) */
{34, 0, 0,__LINE__, {{0x00000000, 0x00000000}, {0x3fc80040, 0x00000000}}},	/* +0.0000E+00=F( +0.1875) */
{34, 0, 0,__LINE__, {{0x00000000, 0x00000000}, {0x3fd00020, 0x00000000}}},	/* +0.0000E+00=F(   +0.25) */
{34, 0, 0,__LINE__, {{0x00000000, 0x00000000}, {0x3fd40020, 0x00000000}}},	/* +0.0000E+00=F( +0.3125) */
{34, 0, 0,__LINE__, {{0x00000000, 0x00000000}, {0x3fd80020, 0x00000000}}},	/* +0.0000E+00=F(  +0.375) */
{34, 0, 0,__LINE__, {{0x00000000, 0x00000000}, {0x3fdc0020, 0x00000000}}},	/* +0.0000E+00=F( +0.4375) */
{34, 0, 0,__LINE__, {{0x00000000, 0x00000000}, {0x3fe00010, 0x00000000}}},	/* +0.0000E+00=F(    +0.5) */
{34, 0, 0,__LINE__, {{0x00000000, 0x00000000}, {0x3fe20010, 0x00000000}}},	/* +0.0000E+00=F( +0.5625) */
{34, 0, 0,__LINE__, {{0x00000000, 0x00000000}, {0x3fe40010, 0x00000000}}},	/* +0.0000E+00=F(  +0.625) */
{34, 0, 0,__LINE__, {{0x00000000, 0x00000000}, {0x3fe60010, 0x00000000}}},	/* +0.0000E+00=F( +0.6875) */
{34, 0, 0,__LINE__, {{0x00000000, 0x00000000}, {0x3fe80010, 0x00000000}}},	/* +0.0000E+00=F(   +0.75) */
{34, 0, 0,__LINE__, {{0x00000000, 0x00000000}, {0x3fea0010, 0x00000000}}},	/* +0.0000E+00=F( +0.8125) */
{34, 0, 0,__LINE__, {{0x00000000, 0x00000000}, {0x3fec0010, 0x00000000}}},	/* +0.0000E+00=F(  +0.875) */
{34, 0, 0,__LINE__, {{0x00000000, 0x00000000}, {0x3fee0010, 0x00000000}}},	/* +0.0000E+00=F( +0.9375) */
{34, 0, 0,__LINE__, {{0x3ff00000, 0x00000000}, {0x3ff00008, 0x00000000}}},	/* +1.0000E+00=F(      +1) */
{34, 0, 0,__LINE__, {{0x3ff00000, 0x00000000}, {0x3ff10008, 0x00000000}}},	/* +1.0000E+00=F(  +1.063) */
{34, 0, 0,__LINE__, {{0x3ff00000, 0x00000000}, {0x3ff20008, 0x00000000}}},	/* +1.0000E+00=F(  +1.125) */
{34, 0, 0,__LINE__, {{0x3ff00000, 0x00000000}, {0x3ff30008, 0x00000000}}},	/* +1.0000E+00=F(  +1.188) */
{34, 0, 0,__LINE__, {{0x3ff00000, 0x00000000}, {0x3ff40008, 0x00000000}}},	/* +1.0000E+00=F(   +1.25) */
{34, 0, 0,__LINE__, {{0x3ff00000, 0x00000000}, {0x3ff50008, 0x00000000}}},	/* +1.0000E+00=F(  +1.313) */
{34, 0, 0,__LINE__, {{0x3ff00000, 0x00000000}, {0x3ff60008, 0x00000000}}},	/* +1.0000E+00=F(  +1.375) */
{34, 0, 0,__LINE__, {{0x3ff00000, 0x00000000}, {0x3ff70008, 0x00000000}}},	/* +1.0000E+00=F(  +1.438) */
{34, 0, 0,__LINE__, {{0x3ff00000, 0x00000000}, {0x3ff80008, 0x00000000}}},	/* +1.0000E+00=F(    +1.5) */
{34, 0, 0,__LINE__, {{0x3ff00000, 0x00000000}, {0x3ff90008, 0x00000000}}},	/* +1.0000E+00=F(  +1.563) */
{34, 0, 0,__LINE__, {{0x3ff00000, 0x00000000}, {0x3ffa0008, 0x00000000}}},	/* +1.0000E+00=F(  +1.625) */
{34, 0, 0,__LINE__, {{0x3ff00000, 0x00000000}, {0x3ffb0008, 0x00000000}}},	/* +1.0000E+00=F(  +1.688) */
{34, 0, 0,__LINE__, {{0x3ff00000, 0x00000000}, {0x3ffc0008, 0x00000000}}},	/* +1.0000E+00=F(   +1.75) */
{34, 0, 0,__LINE__, {{0x3ff00000, 0x00000000}, {0x3ffd0008, 0x00000000}}},	/* +1.0000E+00=F(  +1.813) */
{34, 0, 0,__LINE__, {{0x3ff00000, 0x00000000}, {0x3ffe0008, 0x00000000}}},	/* +1.0000E+00=F(  +1.875) */
{34, 0, 0,__LINE__, {{0x3ff00000, 0x00000000}, {0x3fff0008, 0x00000000}}},	/* +1.0000E+00=F(  +1.938) */
{34, 0, 0,__LINE__, {{0x40000000, 0x00000000}, {0x40000004, 0x00000000}}},	/* +2.0000E+00=F(      +2) */
{34, 0, 0,__LINE__, {{0x40000000, 0x00000000}, {0x40008004, 0x00000000}}},	/* +2.0000E+00=F(  +2.063) */
{34, 0, 0,__LINE__, {{0x40000000, 0x00000000}, {0x40010004, 0x00000000}}},	/* +2.0000E+00=F(  +2.125) */
{34, 0, 0,__LINE__, {{0x40000000, 0x00000000}, {0x40018004, 0x00000000}}},	/* +2.0000E+00=F(  +2.188) */
{34, 0, 0,__LINE__, {{0x40000000, 0x00000000}, {0x40020004, 0x00000000}}},	/* +2.0000E+00=F(   +2.25) */
{34, 0, 0,__LINE__, {{0x40000000, 0x00000000}, {0x40028004, 0x00000000}}},	/* +2.0000E+00=F(  +2.313) */
{34, 0, 0,__LINE__, {{0x40000000, 0x00000000}, {0x40030004, 0x00000000}}},	/* +2.0000E+00=F(  +2.375) */
{34, 0, 0,__LINE__, {{0x40000000, 0x00000000}, {0x40038004, 0x00000000}}},	/* +2.0000E+00=F(  +2.438) */
{34, 0, 0,__LINE__, {{0x40000000, 0x00000000}, {0x40040004, 0x00000000}}},	/* +2.0000E+00=F(    +2.5) */
{34, 0, 0,__LINE__, {{0x40000000, 0x00000000}, {0x40048004, 0x00000000}}},	/* +2.0000E+00=F(  +2.563) */
{34, 0, 0,__LINE__, {{0x40000000, 0x00000000}, {0x40050004, 0x00000000}}},	/* +2.0000E+00=F(  +2.625) */
{34, 0, 0,__LINE__, {{0x40000000, 0x00000000}, {0x40058004, 0x00000000}}},	/* +2.0000E+00=F(  +2.688) */
{34, 0, 0,__LINE__, {{0x40000000, 0x00000000}, {0x40060004, 0x00000000}}},	/* +2.0000E+00=F(   +2.75) */
{34, 0, 0,__LINE__, {{0x40000000, 0x00000000}, {0x40068004, 0x00000000}}},	/* +2.0000E+00=F(  +2.813) */
{34, 0, 0,__LINE__, {{0x40000000, 0x00000000}, {0x40070004, 0x00000000}}},	/* +2.0000E+00=F(  +2.875) */
{34, 0, 0,__LINE__, {{0x40000000, 0x00000000}, {0x40078004, 0x00000000}}},	/* +2.0000E+00=F(  +2.938) */
{34, 0, 0,__LINE__, {{0x40080000, 0x00000000}, {0x40080004, 0x00000000}}},	/* +3.0000E+00=F(      +3) */
{34, 0, 0,__LINE__, {{0x40080000, 0x00000000}, {0x40088004, 0x00000000}}},	/* +3.0000E+00=F(  +3.063) */
{34, 0, 0,__LINE__, {{0x40080000, 0x00000000}, {0x40090004, 0x00000000}}},	/* +3.0000E+00=F(  +3.125) */
{34, 0, 0,__LINE__, {{0x40080000, 0x00000000}, {0x40098004, 0x00000000}}},	/* +3.0000E+00=F(  +3.188) */
{34, 0, 0,__LINE__, {{0x40080000, 0x00000000}, {0x400a0004, 0x00000000}}},	/* +3.0000E+00=F(   +3.25) */
{34, 0, 0,__LINE__, {{0x40080000, 0x00000000}, {0x400a8004, 0x00000000}}},	/* +3.0000E+00=F(  +3.313) */
{34, 0, 0,__LINE__, {{0x40080000, 0x00000000}, {0x400b0004, 0x00000000}}},	/* +3.0000E+00=F(  +3.375) */
{34, 0, 0,__LINE__, {{0x40080000, 0x00000000}, {0x400b8004, 0x00000000}}},	/* +3.0000E+00=F(  +3.438) */
{34, 0, 0,__LINE__, {{0x40080000, 0x00000000}, {0x400c0004, 0x00000000}}},	/* +3.0000E+00=F(    +3.5) */
{34, 0, 0,__LINE__, {{0x40080000, 0x00000000}, {0x400c8004, 0x00000000}}},	/* +3.0000E+00=F(  +3.563) */
{34, 0, 0,__LINE__, {{0x40080000, 0x00000000}, {0x400d0004, 0x00000000}}},	/* +3.0000E+00=F(  +3.625) */
{34, 0, 0,__LINE__, {{0x40080000, 0x00000000}, {0x400d8004, 0x00000000}}},	/* +3.0000E+00=F(  +3.688) */
{34, 0, 0,__LINE__, {{0x40080000, 0x00000000}, {0x400e0004, 0x00000000}}},	/* +3.0000E+00=F(   +3.75) */
{34, 0, 0,__LINE__, {{0x40080000, 0x00000000}, {0x400e8004, 0x00000000}}},	/* +3.0000E+00=F(  +3.813) */
{34, 0, 0,__LINE__, {{0x40080000, 0x00000000}, {0x400f0004, 0x00000000}}},	/* +3.0000E+00=F(  +3.875) */
{34, 0, 0,__LINE__, {{0x40080000, 0x00000000}, {0x400f8004, 0x00000000}}},	/* +3.0000E+00=F(  +3.938) */
{34, 0, 0,__LINE__, {{0x40100000, 0x00000000}, {0x40100002, 0x00000000}}},	/* +4.0000E+00=F(      +4) */
{34, 0, 0,__LINE__, {{0x40140000, 0x00000000}, {0x40140000, 0x00000000}}},	/* +5.0000E+00=F(      +5) */
{34, 0, 0,__LINE__, {{0x40140000, 0x00000000}, {0x40150000, 0x00000000}}},	/* +5.0000E+00=F(   +5.25) */
{34, 0, 0,__LINE__, {{0x40140000, 0x00000000}, {0x40160000, 0x00000000}}},	/* +5.0000E+00=F(    +5.5) */
{34, 0, 0,__LINE__, {{0x40140000, 0x00000000}, {0x40170000, 0x00000000}}},	/* +5.0000E+00=F(   +5.75) */
{34, 0, 0,__LINE__, {{0x40180000, 0x00000000}, {0x40180000, 0x00000000}}},	/* +6.0000E+00=F(      +6) */
{34, 0, 0,__LINE__, {{0x40180000, 0x00000000}, {0x40190000, 0x00000000}}},	/* +6.0000E+00=F(   +6.25) */
{34, 0, 0,__LINE__, {{0x40180000, 0x00000000}, {0x401a0000, 0x00000000}}},	/* +6.0000E+00=F(    +6.5) */
{34, 0, 0,__LINE__, {{0x40180000, 0x00000000}, {0x401b0000, 0x00000000}}},	/* +6.0000E+00=F(   +6.75) */
{34, 0, 0,__LINE__, {{0x401c0000, 0x00000000}, {0x401c0000, 0x00000000}}},	/* +7.0000E+00=F(      +7) */
{34, 0, 0,__LINE__, {{0x00000000, 0x00000000}, {0x00000000, 0x00000000}}},	/* +0.0000E+00=F(      +0) */
{34, 0, 0,__LINE__, {{0x7ff00000, 0x00000000}, {0x7ff00000, 0x00000000}}},	/* +Inf       =F(    +Inf) */
{34, 0, 0,__LINE__, {{0xfff00000, 0x00000000}, {0xfff00000, 0x00000000}}},	/* -Inf       =F(    -Inf) */
{34, 0, 0,__LINE__, {{0x7ff80000, 0x00000000}, {0x7ff80000, 0x00000000}}},	/* +NaN       =F(    +NaN) */
{34, 0, 0,__LINE__, {{0xfff80000, 0x00000000}, {0xfff80000, 0x00000000}}},	/* -NaN       =F(    -NaN) */
{0}};
void
test_floorf(int m)	{ run_vector_1(m, floorf_vec,(char *)(floorf),"floorf","ff");}
