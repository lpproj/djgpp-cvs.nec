#include "test.h"
 one_line_type log_vec[] = {
{62, 0, 0,__LINE__, {{0xc0126bb1, 0xbbb55515}, {0x3f847ae1, 0x47ae147b}}},	/* -4.6052E+00=F(   +0.01) */
{62, 0, 0,__LINE__, {{0xc00d5041, 0x30d637cc}, {0x3f9a3d70, 0xa3d70a3e}}},	/* -3.6642E+00=F(+0.02563) */
{62, 0, 0,__LINE__, {{0xc009813c, 0xc1d09ccd}, {0x3fa51eb8, 0x51eb851f}}},	/* -3.1881E+00=F(+0.04125) */
{62, 0, 0,__LINE__, {{0xc006ef68, 0xf41a2a9d}, {0x3fad1eb8, 0x51eb851f}}},	/* -2.8669E+00=F(+0.05688) */
{62, 0, 0,__LINE__, {{0xc004fe4c, 0x2b19c904}, {0x3fb28f5c, 0x28f5c290}}},	/* -2.6242E+00=F( +0.0725) */
{62, 0, 0,__LINE__, {{0xc0036e97, 0x097d71de}, {0x3fb68f5c, 0x28f5c290}}},	/* -2.4290E+00=F(+0.08813) */
{62, 0, 0,__LINE__, {{0xc002204c, 0x9be08c9b}, {0x3fba8f5c, 0x28f5c290}}},	/* -2.2658E+00=F( +0.1038) */
{62, 0, 0,__LINE__, {{0xc00100fe, 0x880c02a6}, {0x3fbe8f5c, 0x28f5c290}}},	/* -2.1255E+00=F( +0.1194) */
{62, 0, 0,__LINE__, {{0xc0000514, 0x7f25b417}, {0x3fc147ae, 0x147ae148}}},	/* -2.0025E+00=F(  +0.135) */
{62, 0, 0,__LINE__, {{0xbffe4992, 0x7ee1163b}, {0x3fc347ae, 0x147ae148}}},	/* -1.8930E+00=F( +0.1506) */
{62, 0, 0,__LINE__, {{0xbffcb54c, 0xb310ea8c}, {0x3fc547ae, 0x147ae148}}},	/* -1.7943E+00=F( +0.1663) */
{62, 0, 0,__LINE__, {{0xbffb455e, 0x4e87954a}, {0x3fc747ae, 0x147ae148}}},	/* -1.7044E+00=F( +0.1819) */
{62, 0, 0,__LINE__, {{0xbff9f3c7, 0xc710c879}, {0x3fc947ae, 0x147ae148}}},	/* -1.6220E+00=F( +0.1975) */
{62, 0, 0,__LINE__, {{0xbff8bbe8, 0xeca902e9}, {0x3fcb47ae, 0x147ae148}}},	/* -1.5459E+00=F( +0.2131) */
{62, 0, 0,__LINE__, {{0xbff79a1d, 0x4655f7ff}, {0x3fcd47ae, 0x147ae148}}},	/* -1.4751E+00=F( +0.2288) */
{62, 0, 0,__LINE__, {{0xbff68b79, 0x6d316161}, {0x3fcf47ae, 0x147ae148}}},	/* -1.4091E+00=F( +0.2444) */
{62, 0, 0,__LINE__, {{0xbff58d9d, 0x18f51ebc}, {0x3fd0a3d7, 0x0a3d70a4}}},	/* -1.3471E+00=F(   +0.26) */
{62, 0, 0,__LINE__, {{0xbff49e92, 0x9b0b0d70}, {0x3fd1a3d7, 0x0a3d70a4}}},	/* -1.2887E+00=F( +0.2756) */
{62, 0, 0,__LINE__, {{0xbff3bcb7, 0x5457d1bf}, {0x3fd2a3d7, 0x0a3d70a4}}},	/* -1.2336E+00=F( +0.2913) */
{62, 0, 0,__LINE__, {{0xbff2e6aa, 0x53c3e1f7}, {0x3fd3a3d7, 0x0a3d70a4}}},	/* -1.1813E+00=F( +0.3069) */
{62, 0, 0,__LINE__, {{0xbff21b3f, 0x46f8b318}, {0x3fd4a3d7, 0x0a3d70a4}}},	/* -1.1317E+00=F( +0.3225) */
{62, 0, 0,__LINE__, {{0xbff15974, 0x82df3287}, {0x3fd5a3d7, 0x0a3d70a4}}},	/* -1.0843E+00=F( +0.3381) */
{62, 0, 0,__LINE__, {{0xbff0a06b, 0x4d01c045}, {0x3fd6a3d7, 0x0a3d70a4}}},	/* -1.0392E+00=F( +0.3538) */
{62, 0, 0,__LINE__, {{0xbfefdec3, 0xa0186c4b}, {0x3fd7a3d7, 0x0a3d70a4}}},	/* -9.9594E-01=F( +0.3694) */
{62, 0, 0,__LINE__, {{0xbfee8b5c, 0xa24350be}, {0x3fd8a3d7, 0x0a3d70a4}}},	/* -9.5451E-01=F(  +0.385) */
{62, 0, 0,__LINE__, {{0xbfed4576, 0xb2c1adbf}, {0x3fd9a3d7, 0x0a3d70a4}}},	/* -9.1473E-01=F( +0.4006) */
{62, 0, 0,__LINE__, {{0xbfec0c09, 0x36fa2b5a}, {0x3fdaa3d7, 0x0a3d70a4}}},	/* -8.7647E-01=F( +0.4163) */
{62, 0, 0,__LINE__, {{0xbfeade28, 0xd79b543c}, {0x3fdba3d7, 0x0a3d70a4}}},	/* -8.3962E-01=F( +0.4319) */
{62, 0, 0,__LINE__, {{0xbfe9bb03, 0x5724d9ca}, {0x3fdca3d7, 0x0a3d70a4}}},	/* -8.0408E-01=F( +0.4475) */
{62, 0, 0,__LINE__, {{0xbfe8a1dc, 0x1f608c5e}, {0x3fdda3d7, 0x0a3d70a4}}},	/* -7.6976E-01=F( +0.4631) */
{62, 0, 0,__LINE__, {{0xbfe79209, 0x615982cf}, {0x3fdea3d7, 0x0a3d70a4}}},	/* -7.3658E-01=F( +0.4788) */
{62, 0, 0,__LINE__, {{0xbfe68af1, 0xab92c0dc}, {0x3fdfa3d7, 0x0a3d70a4}}},	/* -7.0446E-01=F( +0.4944) */
{62, 0, 0,__LINE__, {{0xbfe58c09, 0xe066a4b0}, {0x3fe051eb, 0x851eb852}}},	/* -6.7334E-01=F(   +0.51) */
{62, 0, 0,__LINE__, {{0xbfe494d3, 0x7b239f73}, {0x3fe0d1eb, 0x851eb852}}},	/* -6.4317E-01=F( +0.5256) */
{62, 0, 0,__LINE__, {{0xbfe3a4db, 0x160db048}, {0x3fe151eb, 0x851eb852}}},	/* -6.1387E-01=F( +0.5413) */
{62, 0, 0,__LINE__, {{0xbfe2bbb7, 0x262e9ae5}, {0x3fe1d1eb, 0x851eb852}}},	/* -5.8541E-01=F( +0.5569) */
{62, 0, 0,__LINE__, {{0xbfe1d906, 0xe404d675}, {0x3fe251eb, 0x851eb852}}},	/* -5.5774E-01=F( +0.5725) */
{62, 0, 0,__LINE__, {{0xbfe0fc71, 0x59d0a8d5}, {0x3fe2d1eb, 0x851eb852}}},	/* -5.3082E-01=F( +0.5881) */
{62, 0, 0,__LINE__, {{0xbfe025a4, 0x9193cbf6}, {0x3fe351eb, 0x851eb852}}},	/* -5.0460E-01=F( +0.6038) */
{62, 0, 0,__LINE__, {{0xbfdea8a9, 0xbbce5977}, {0x3fe3d1eb, 0x851eb852}}},	/* -4.7904E-01=F( +0.6194) */
{62, 0, 0,__LINE__, {{0xbfdd1078, 0x7346e115}, {0x3fe451eb, 0x851eb852}}},	/* -4.5413E-01=F(  +0.635) */
{62, 0, 0,__LINE__, {{0xbfdb8233, 0x760f9d59}, {0x3fe4d1eb, 0x851eb852}}},	/* -4.2982E-01=F( +0.6506) */
{62, 0, 0,__LINE__, {{0xbfd9fd62, 0x2f30e7fe}, {0x3fe551eb, 0x851eb852}}},	/* -4.0609E-01=F( +0.6663) */
{62, 0, 0,__LINE__, {{0xbfd88194, 0x6cc210ce}, {0x3fe5d1eb, 0x851eb852}}},	/* -3.8291E-01=F( +0.6819) */
{62, 0, 0,__LINE__, {{0xbfd70e61, 0x9d4cc5f1}, {0x3fe651eb, 0x851eb852}}},	/* -3.6025E-01=F( +0.6975) */
{62, 0, 0,__LINE__, {{0xbfd5a368, 0x22c05fc4}, {0x3fe6d1eb, 0x851eb852}}},	/* -3.3810E-01=F( +0.7131) */
{62, 0, 0,__LINE__, {{0xbfd4404c, 0xb8270d40}, {0x3fe751eb, 0x851eb852}}},	/* -3.1642E-01=F( +0.7288) */
{62, 0, 0,__LINE__, {{0xbfd2e4b9, 0xe7b9858d}, {0x3fe7d1eb, 0x851eb852}}},	/* -2.9521E-01=F( +0.7444) */
{62, 0, 0,__LINE__, {{0xbfd1905f, 0x8f46d038}, {0x3fe851eb, 0x851eb852}}},	/* -2.7444E-01=F(   +0.76) */
{62, 0, 0,__LINE__, {{0xbfd042f2, 0x713026a0}, {0x3fe8d1eb, 0x851eb852}}},	/* -2.5409E-01=F( +0.7756) */
{62, 0, 0,__LINE__, {{0xbfcdf857, 0xa0ef0237}, {0x3fe951eb, 0x851eb852}}},	/* -2.3414E-01=F( +0.7913) */
{62, 0, 0,__LINE__, {{0xbfcb7792, 0x2d284f43}, {0x3fe9d1eb, 0x851eb852}}},	/* -2.1459E-01=F( +0.8069) */
{62, 0, 0,__LINE__, {{0xbfc90317, 0x03da9409}, {0x3fea51eb, 0x851eb852}}},	/* -1.9541E-01=F( +0.8225) */
{62, 0, 0,__LINE__, {{0xbfc69a6f, 0xb8012b5c}, {0x3fead1eb, 0x851eb852}}},	/* -1.7659E-01=F( +0.8381) */
{62, 0, 0,__LINE__, {{0xbfc43d2c, 0x6cb629c8}, {0x3feb51eb, 0x851eb852}}},	/* -1.5812E-01=F( +0.8538) */
{62, 0, 0,__LINE__, {{0xbfc1eae3, 0x5b4c9125}, {0x3febd1eb, 0x851eb852}}},	/* -1.3998E-01=F( +0.8694) */
{62, 0, 0,__LINE__, {{0xbfbf4660, 0xc88c8603}, {0x3fec51eb, 0x851eb852}}},	/* -1.2217E-01=F(  +0.885) */
{62, 0, 0,__LINE__, {{0xbfbacb69, 0x54038135}, {0x3fecd1eb, 0x851eb852}}},	/* -1.0467E-01=F( +0.9006) */
{62, 0, 0,__LINE__, {{0xbfb6642c, 0x683dde3e}, {0x3fed51eb, 0x851eb852}}},	/* -8.7466E-02=F( +0.9163) */
{62, 0, 0,__LINE__, {{0xbfb20fff, 0x3570faeb}, {0x3fedd1eb, 0x851eb852}}},	/* -7.0557E-02=F( +0.9319) */
{62, 0, 0,__LINE__, {{0xbfab9c7e, 0xe2a78f20}, {0x3fee51eb, 0x851eb852}}},	/* -5.3928E-02=F( +0.9475) */
{62, 0, 0,__LINE__, {{0xbfa33ca5, 0x90c373db}, {0x3feed1eb, 0x851eb852}}},	/* -3.7572E-02=F( +0.9631) */
{62, 0, 0,__LINE__, {{0xbf95fe99, 0x6a6977e4}, {0x3fef51eb, 0x851eb852}}},	/* -2.1479E-02=F( +0.9788) */
{62, 0, 0,__LINE__, {{0xbf771ae4, 0x2a6097d0}, {0x3fefd1eb, 0x851eb852}}},	/* -5.6409E-03=F( +0.9944) */
{62, 0, 0,__LINE__, {{0x3f8460d6, 0xccca367c}, {0x3ff028f5, 0xc28f5c29}}},	/* +9.9503E-03=F(   +1.01) */
{62, 0, 0,__LINE__, {{0x3f99e8d0, 0xbfa47e9f}, {0x3ff068f5, 0xc28f5c29}}},	/* +2.5302E-02=F(  +1.026) */
{62, 0, 0,__LINE__, {{0x3fe6571e, 0xa0efe6d3}, {0x4000147a, 0xe147ae14}}},	/* +6.9813E-01=F(   +2.01) */
{62, 0, 0,__LINE__, {{0x3fe6d580, 0xbdd42f8d}, {0x4000547a, 0xe147ae14}}},	/* +7.1356E-01=F(  +2.041) */
{62, 0, 0,__LINE__, {{0x3fe751f7, 0x47e81ffb}, {0x4000947a, 0xe147ae14}}},	/* +7.2876E-01=F(  +2.072) */
{62, 0, 0,__LINE__, {{0x3fe7cc90, 0xf60190c6}, {0x4000d47a, 0xe147ae14}}},	/* +7.4372E-01=F(  +2.104) */
{62, 0, 0,__LINE__, {{0x3fe8455b, 0xd853327a}, {0x4001147a, 0xe147ae14}}},	/* +7.5847E-01=F(  +2.135) */
{62, 0, 0,__LINE__, {{0x3fe8bc65, 0x621c3d87}, {0x4001547a, 0xe147ae14}}},	/* +7.7300E-01=F(  +2.166) */
{62, 0, 0,__LINE__, {{0x3fe931ba, 0x72a689af}, {0x4001947a, 0xe147ae14}}},	/* +7.8732E-01=F(  +2.197) */
{62, 0, 0,__LINE__, {{0x3fe9a567, 0x5da21920}, {0x4001d47a, 0xe147ae14}}},	/* +8.0144E-01=F(  +2.229) */
{62, 0, 0,__LINE__, {{0x3fea1777, 0xf2ebac20}, {0x4002147a, 0xe147ae14}}},	/* +8.1536E-01=F(   +2.26) */
{62, 0, 0,__LINE__, {{0x3fea87f7, 0x85caa3b8}, {0x4002547a, 0xe147ae14}}},	/* +8.2910E-01=F(  +2.291) */
{62, 0, 0,__LINE__, {{0x3feaf6f0, 0xf3b14ff0}, {0x4002947a, 0xe147ae14}}},	/* +8.4264E-01=F(  +2.322) */
{62, 0, 0,__LINE__, {{0x3feb646e, 0xaa89bbed}, {0x4002d47a, 0xe147ae14}}},	/* +8.5601E-01=F(  +2.354) */
{62, 0, 0,__LINE__, {{0x3febd07a, 0xae981c39}, {0x4003147a, 0xe147ae14}}},	/* +8.6920E-01=F(  +2.385) */
{62, 0, 0,__LINE__, {{0x3fec3b1e, 0x9ffb2e35}, {0x4003547a, 0xe147ae14}}},	/* +8.8222E-01=F(  +2.416) */
{62, 0, 0,__LINE__, {{0x3feca463, 0xbfd21855}, {0x4003947a, 0xe147ae14}}},	/* +8.9507E-01=F(  +2.447) */
{62, 0, 0,__LINE__, {{0x3fed0c52, 0xf50eaee7}, {0x4003d47a, 0xe147ae14}}},	/* +9.0775E-01=F(  +2.479) */
{62, 0, 0,__LINE__, {{0x3fed72f4, 0xd0fa6667}, {0x4004147a, 0xe147ae14}}},	/* +9.2028E-01=F(   +2.51) */
{62, 0, 0,__LINE__, {{0x3fedd851, 0x9373b113}, {0x4004547a, 0xe147ae14}}},	/* +9.3266E-01=F(  +2.541) */
{62, 0, 0,__LINE__, {{0x3fee3c71, 0x2ee90796}, {0x4004947a, 0xe147ae14}}},	/* +9.4488E-01=F(  +2.572) */
{62, 0, 0,__LINE__, {{0x3fee9f5b, 0x4c166b29}, {0x4004d47a, 0xe147ae14}}},	/* +9.5695E-01=F(  +2.604) */
{62, 0, 0,__LINE__, {{0x3fef0117, 0x4d89c8b3}, {0x4005147a, 0xe147ae14}}},	/* +9.6888E-01=F(  +2.635) */
{62, 0, 0,__LINE__, {{0x3fef61ac, 0x52f2475d}, {0x4005547a, 0xe147ae14}}},	/* +9.8067E-01=F(  +2.666) */
{62, 0, 0,__LINE__, {{0x3fefc121, 0x3c3e38c6}, {0x4005947a, 0xe147ae14}}},	/* +9.9233E-01=F(  +2.697) */
{62, 0, 0,__LINE__, {{0x3ff00fbe, 0x56458a20}, {0x4005d47a, 0xe147ae14}}},	/* +1.0038E+00=F(  +2.729) */
{62, 0, 0,__LINE__, {{0x3ff03e62, 0x86755083}, {0x4006147a, 0xe147ae14}}},	/* +1.0152E+00=F(   +2.76) */
{62, 0, 0,__LINE__, {{0x3ff06c80, 0x478019ef}, {0x4006547a, 0xe147ae14}}},	/* +1.0265E+00=F(  +2.791) */
{62, 0, 0,__LINE__, {{0x3ff09a1a, 0x97bc5578}, {0x4006947a, 0xe147ae14}}},	/* +1.0376E+00=F(  +2.822) */
{62, 0, 0,__LINE__, {{0x3ff0c734, 0x5c2fcf04}, {0x4006d47a, 0xe147ae14}}},	/* +1.0486E+00=F(  +2.854) */
{62, 0, 0,__LINE__, {{0x3ff0f3d0, 0x61aa04ad}, {0x4007147a, 0xe147ae14}}},	/* +1.0595E+00=F(  +2.885) */
{62, 0, 0,__LINE__, {{0x3ff11ff1, 0x5dcf4673}, {0x4007547a, 0xe147ae14}}},	/* +1.0703E+00=F(  +2.916) */
{62, 0, 0,__LINE__, {{0x3ff14b99, 0xf0159959}, {0x4007947a, 0xe147ae14}}},	/* +1.0810E+00=F(  +2.947) */
{62, 0, 0,__LINE__, {{0x3ff176cc, 0xa2b44485}, {0x4007d47a, 0xe147ae14}}},	/* +1.0915E+00=F(  +2.979) */
{62, 0, 0,__LINE__, {{0x3ff1a18b, 0xeb86de23}, {0x4008147a, 0xe147ae14}}},	/* +1.1019E+00=F(   +3.01) */
{62, 0, 0,__LINE__, {{0x3ff1cbda, 0x2ce49e7c}, {0x4008547a, 0xe147ae14}}},	/* +1.1123E+00=F(  +3.041) */
{62, 0, 0,__LINE__, {{0x400275e8, 0xa432c04f}, {0x40241999, 0x9999999a}}},	/* +2.3076E+00=F(  +10.05) */
{62, 0, 0,__LINE__, {{0x4004717a, 0x2b08a431}, {0x4029c0cc, 0xcccccccd}}},	/* +2.5554E+00=F(  +12.88) */
{62, 0, 0,__LINE__, {{0x400607e7, 0x9d261393}, {0x402f6800, 0x00000000}}},	/* +2.7539E+00=F(   +15.7) */
{62, 0, 0,__LINE__, {{0x40075ae0, 0xd9084ad5}, {0x40328799, 0x9999999a}}},	/* +2.9194E+00=F(  +18.53) */
{62, 0, 0,__LINE__, {{0x40087da2, 0x26f19455}, {0x40355b33, 0x33333334}}},	/* +3.0613E+00=F(  +21.36) */
{62, 0, 0,__LINE__, {{0x40097c31, 0xf4125c5c}, {0x40382ecc, 0xccccccce}}},	/* +3.1856E+00=F(  +24.18) */
{62, 0, 0,__LINE__, {{0x400a5e95, 0xbb4d7271}, {0x403b0266, 0x66666668}}},	/* +3.2962E+00=F(  +27.01) */
{62, 0, 0,__LINE__, {{0x400b2a6b, 0xe77571aa}, {0x403dd600, 0x00000002}}},	/* +3.3957E+00=F(  +29.84) */
{62, 0, 0,__LINE__, {{0x400be3cb, 0x4fe72fa9}, {0x404054cc, 0xccccccce}}},	/* +3.4862E+00=F(  +32.66) */
{62, 0, 0,__LINE__, {{0x400c8dc5, 0x99e0fe9c}, {0x4041be99, 0x9999999b}}},	/* +3.5692E+00=F(  +35.49) */
{62, 0, 0,__LINE__, {{0x400d2ab7, 0x7b5d5e7a}, {0x40432866, 0x66666668}}},	/* +3.6459E+00=F(  +38.32) */
{62, 0, 0,__LINE__, {{0x400dbc7c, 0x59bf88a9}, {0x40449233, 0x33333335}}},	/* +3.7170E+00=F(  +41.14) */
{62, 0, 0,__LINE__, {{0x400e4490, 0xb80708a1}, {0x4045fc00, 0x00000002}}},	/* +3.7835E+00=F(  +43.97) */
{62, 0, 0,__LINE__, {{0x400ec429, 0xe5b1c63e}, {0x404765cc, 0xcccccccf}}},	/* +3.8458E+00=F(   +46.8) */
{62, 0, 0,__LINE__, {{0x400f3c46, 0xb897e946}, {0x4048cf99, 0x9999999c}}},	/* +3.9044E+00=F(  +49.62) */
{62, 0, 0,__LINE__, {{0x400fadbb, 0xa2e5a6a2}, {0x404a3966, 0x66666669}}},	/* +3.9598E+00=F(  +52.45) */
{62, 0, 0,__LINE__, {{0x40100c9d, 0xcdf9b490}, {0x404ba333, 0x33333336}}},	/* +4.0123E+00=F(  +55.28) */
{62, 0, 0,__LINE__, {{0x40103faf, 0x67d5c31e}, {0x404d0d00, 0x00000003}}},	/* +4.0622E+00=F(   +58.1) */
{62, 0, 0,__LINE__, {{0x40107053, 0xdb818f28}, {0x404e76cc, 0xccccccd0}}},	/* +4.1097E+00=F(  +60.93) */
{62, 0, 0,__LINE__, {{0x40109ec3, 0x84309197}, {0x404fe099, 0x9999999d}}},	/* +4.1550E+00=F(  +63.75) */
{62, 0, 0,__LINE__, {{0x4010cb2f, 0x668ca8c3}, {0x4050a533, 0x33333335}}},	/* +4.1984E+00=F(  +66.58) */
{62, 0, 0,__LINE__, {{0x4010f5c2, 0x695301d8}, {0x40515a19, 0x9999999b}}},	/* +4.2400E+00=F(  +69.41) */
{62, 0, 0,__LINE__, {{0x40111ea2, 0x4f808075}, {0x40520f00, 0x00000001}}},	/* +4.2799E+00=F(  +72.23) */
{62, 0, 0,__LINE__, {{0x401145f0, 0x82721c8c}, {0x4052c3e6, 0x66666667}}},	/* +4.3183E+00=F(  +75.06) */
{62, 0, 0,__LINE__, {{0x40116bca, 0xb6a36759}, {0x405378cc, 0xcccccccd}}},	/* +4.3553E+00=F(  +77.89) */
{62, 0, 0,__LINE__, {{0x4011904b, 0x730b8c03}, {0x40542db3, 0x33333333}}},	/* +4.3909E+00=F(  +80.71) */
{62, 0, 0,__LINE__, {{0x4011b38a, 0x812b335c}, {0x4054e299, 0x99999999}}},	/* +4.4253E+00=F(  +83.54) */
{62, 0, 0,__LINE__, {{0x4011d59d, 0x4a735e31}, {0x4055977f, 0xffffffff}}},	/* +4.4586E+00=F(  +86.37) */
{62, 0, 0,__LINE__, {{0x4011f697, 0x26a06136}, {0x40564c66, 0x66666665}}},	/* +4.4908E+00=F(  +89.19) */
{62, 0, 0,__LINE__, {{0x40121689, 0x9dda6ff6}, {0x4057014c, 0xcccccccb}}},	/* +4.5220E+00=F(  +92.02) */
{62, 0, 0,__LINE__, {{0x40123584, 0xa0d44382}, {0x4057b633, 0x33333331}}},	/* +4.5523E+00=F(  +94.85) */
{62, 0, 0,__LINE__, {{0x40125396, 0xb8ab794b}, {0x40586b19, 0x99999997}}},	/* +4.5816E+00=F(  +97.67) */
{62, 0, 0,__LINE__, {{0x401270cd, 0x2ff40ab2}, {0x40591fff, 0xfffffffd}}},	/* +4.6102E+00=F(  +100.5) */
{62, 1, 0,__LINE__, {{0xfff00000, 0x00000000}, {0xbff00000, 0x00000000}}},	/* -Inf       =F(      -1) */
{62, 2, 0,__LINE__, {{0xfff00000, 0x00000000}, {0x00000000, 0x00000000}}},	/* -Inf       =F(      +0) */
{62, 0, 0,__LINE__, {{0x00000000, 0x00000000}, {0x3ff00000, 0x00000000}}},	/* +0.0000E+00=F(      +1) */
{62, 0, 0,__LINE__, {{0x40862e42, 0xfefa39ef}, {0x7fefffff, 0xffffffff}}},	/* +7.0978E+02=F(+1.798e+308) */
{62, 0, 0,__LINE__, {{0xc086232b, 0xdd7abcd2}, {0x00100000, 0x00000000}}},	/* -7.0840E+02=F(+2.225e-308) */
{62, 1, 0,__LINE__, {{0xfff00000, 0x00000000}, {0xfff00000, 0x00000000}}},	/* -Inf       =F(    -Inf) */
{62, 0, 0,__LINE__, {{0x7ff00000, 0x00000000}, {0x7ff00000, 0x00000000}}},	/* +Inf       =F(    +Inf) */
{62, 0, 0,__LINE__, {{0x7ff80000, 0x00000000}, {0x7ff80000, 0x00000000}}},	/* +NaN       =F(    +NaN) */
{62, 0, 0,__LINE__, {{0xfff80000, 0x00000000}, {0xfff80000, 0x00000000}}},	/* -NaN       =F(    -NaN) */
{0}};
void
test_log(int m)	{ run_vector_1(m, log_vec,(char *)(log),"log","dd");}
