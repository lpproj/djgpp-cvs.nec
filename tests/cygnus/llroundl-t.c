/* Copyright (C) 2013 DJ Delorie, see COPYING.DJ for details */


#include "main-t.h"

typedef struct {
  const _longdouble_union_t value;  /* test value */
  const long long int should_be;    /* result */
} entry_t;


static const entry_t tests_long_double[] =
{
  /* test value */
  /*     value           should be   */

  /* Zeros. */
  {{.ldt = {0x0U, 0x0U, 0x0U, 0}},  0}, /* 0.0 */
  {{.ldt = {0x0U, 0x0U, 0x0U, 1}},  0}, /* -0.0 */

  /* Subnormals aka denormals. */
  {{.ldt = {0x1U, 0x0U, 0x0U, 0}},  0}, /* Very small number. */
  {{.ldt = {0x1U, 0x0U, 0x0U, 1}},  0}, /* Very small -number. */

  /* Normals. */
  {{.ldt = {0x0U, 0x80000000U, 0x1U, 0}},  0}, /* Small number. */
  {{.ldt = {0x0U, 0x80000000U, 0x1U, 1}},  0}, /* Small -number. */
  {{.ldt = {0xFFFFFFFFU, 0xFFFFFFFFU, 0x7FFEU, 0}},  -9.223372036854775808E+18}, /* Big number. */
  {{.ldt = {0xFFFFFFFFU, 0xFFFFFFFFU, 0x7FFEU, 1}},  -9.223372036854775808E+18}, /* Big -number. */

  /* Infs. */
  {{.ldt = {0x0U, 0x80000000U, 0x7FFFU, 0}},  -9.223372036854775808E+18}, /* Inf */
  {{.ldt = {0x0U, 0x80000000U, 0x7FFFU, 1}},  -9.223372036854775808E+18}, /* -Inf */

  /* NaNs. */
  {{.ldt = {0x1U, 0x80000000U, 0x7FFFU, 0}},  -9.223372036854775808E+18}, /* SNaN */
  {{.ldt = {0x1U, 0x80000000U, 0x7FFFU, 1}},  -9.223372036854775808E+18}, /* -SNaN */
  {{.ldt = {0x0U, 0xFFFFFFFFU, 0x7FFFU, 0}},  -9.223372036854775808E+18}, /* QNaN */
  {{.ldt = {0x0U, 0xFFFFFFFFU, 0x7FFFU, 1}},  -9.223372036854775808E+18}, /* -QNaN */


  /* Number. */
  {{.ldt = {0x2168C000U, 0xC90FDAA2U, 0x3FFFU + 0x0001U, 0}},   +3}, /* PI */
  {{.ldt = {0x2168C000U, 0xC90FDAA2U, 0x3FFFU + 0x0001U, 1}},   -3}, /* -PI */

  {{.ldt = {0x00000000U, 0xF0000000U, 0x3FFFU + 0x0U, 0}},   +2}, /* 1.875000 */
  {{.ldt = {0x00000000U, 0xF0000000U, 0x3FFFU + 0x0U, 1}},   -2}, /* -1.875000 */
  {{.ldt = {0x00000000U, 0xD0000000U, 0x3FFFU + 0x0U, 0}},   +2}, /* 1.625000 */
  {{.ldt = {0x00000000U, 0xD0000000U, 0x3FFFU + 0x0U, 1}},   -2}, /* -1.625000 */
  {{.ldt = {0xF7A0B800U, 0xC00010C6U, 0x3FFFU + 0x0U, 0}},   +2}, /* 1.500002 */
  {{.ldt = {0xF7A0B800U, 0xC00010C6U, 0x3FFFU + 0x0U, 1}},   -2}, /* -1.500002 */
  {{.ldt = {0x00000000U, 0xC0000000U, 0x3FFFU + 0x0U, 0}},   +2}, /* 1.500000 */
  {{.ldt = {0x00000000U, 0xC0000000U, 0x3FFFU + 0x0U, 1}},   -2}, /* -1.500000 */
  {{.ldt = {0x085F4800U, 0xBFFFEF39U, 0x3FFFU + 0x0U, 0}},   +1}, /* 1.499998 */
  {{.ldt = {0x085F4800U, 0xBFFFEF39U, 0x3FFFU + 0x0U, 1}},   -1}, /* -1.499998 */
  {{.ldt = {0x00000000U, 0xB0000000U, 0x3FFFU + 0x0U, 0}},   +1}, /* 1.375000 */
  {{.ldt = {0x00000000U, 0xB0000000U, 0x3FFFU + 0x0U, 1}},   -1}, /* -1.375000 */
  {{.ldt = {0x00000000U, 0x90000000U, 0x3FFFU + 0x0U, 0}},   +1}, /* 1.125000 */
  {{.ldt = {0x00000000U, 0x90000000U, 0x3FFFU + 0x0U, 1}},   -1}, /* -1.125000 */

  {{.ldt = {0x00000000U, 0x80000000U, 0x3FFFU + 0x0016U, 0}},   +4194304}, /* 4194304.000000 */
  {{.ldt = {0x00000000U, 0x80000000U, 0x3FFFU + 0x0016U, 1}},   -4194304}, /* -4194304.000000 */ 
  {{.ldt = {0x00000000U, 0x80000000U, 0x3FFFU + 0x0017U, 0}},   +8388608}, /* 8388608.000000 */
  {{.ldt = {0x00000000U, 0x80000000U, 0x3FFFU + 0x0017U, 1}},   -8388608}, /* -8388608.000000 */
  {{.ldt = {0x00000000U, 0x80000000U, 0x3FFFU + 0x0018U, 0}},   +16777216}, /* 16777216.000000 */
  {{.ldt = {0x00000000U, 0x80000000U, 0x3FFFU + 0x0018U, 1}},   -16777216}, /* -16777216.000000 */
  {{.ldt = {0x00000000U, 0x80000000U, 0x3FFFU + 0x001EU, 0}},   +1073741824}, /* 1073741824.000000 */
  {{.ldt = {0x00000000U, 0x80000000U, 0x3FFFU + 0x001EU, 1}},   -1073741824}, /* -1073741824.000000 */
  {{.ldt = {0x00000000U, 0xFFFFFFFEU, 0x3FFFU + 0x001EU, 0}},   +2147483647LL}, /* 2147483647.000000 */
  {{.ldt = {0x00000000U, 0x80000000U, 0x3FFFU + 0x001FU, 1}},   -2147483648LL}, /* -2147483648.000000 */
  {{.ldt = {0x00000000U, 0x80000000U, 0x3FFFU + 0x0020U, 0}},   +4294967296}, /* 4294967296.000000 */
  {{.ldt = {0x00000000U, 0x80000000U, 0x3FFFU + 0x0020U, 1}},   -4294967296}, /* -4294967296.000000 */

  /*  Number greater than 2**63 exceeds long long int size and will be casted in an implementation defined manner.  */
  {{.ldt = {0x00000000U, 0x80000000U, 0x3FFFU + 0x003FU, 0}},  -9.223372036854775808E18}, /* 9223372036854775808.000000 */
  {{.ldt = {0x00000000U, 0x80000000U, 0x3FFFU + 0x003FU, 1}},  -9.223372036854775808E18}, /* -9223372036854775808.000000 */

  /*  Number less than 0.5 will be truncated to 0.  */
  {{.ldt = {0xC42F9800U, 0xFFBC98FFU, 0x3FFFU + 0xFFFFFFFEU, 0}},   0}, /* 0.4994857609 */
  {{.ldt = {0xC42F9800U, 0xFFBC98FFU, 0x3FFFU + 0xFFFFFFFEU, 1}},   -0}, /* -0.4994857609 */
  {{.ldt = {0x8D4FE000U, 0x83126E97U, 0x3FFFU + 0xFFFFFFF6U, 0}},   0}, /* 0.0010000000 */
  {{.ldt = {0x8D4FE000U, 0x83126E97U, 0x3FFFU + 0xFFFFFFF6U, 1}},   -0}, /* -0.0010000000 */

  /*  Number greater than 0.5 and less than 1 will be rounded to 1.  */
  {{.ldt = {0xC37A4000U, 0xFCD6E47DU, 0x3FFFU + 0xFFFFFFFFU, 0}},   1}, /* 0.9876540000 */
  {{.ldt = {0xC37A4000U, 0xFCD6E47DU, 0x3FFFU + 0xFFFFFFFFU, 1}},   -1}, /* -0.9876540000 */
  {{.ldt = {0xB2B29800U, 0x80000101U, 0x3FFFU + 0xFFFFFFFFU, 0}},   1}, /* 0.5000000600 */
  {{.ldt = {0xB2B29800U, 0x80000101U, 0x3FFFU + 0xFFFFFFFFU, 1}},   -1}, /* -0.5000000600 */
  {{.ldt = {0x00000000U, 0x80000000U, 0x3FFFU + 0xFFFFFFFFU, 0}},   1}, /* 0.5000000000 */
  {{.ldt = {0x00000000U, 0x80000000U, 0x3FFFU + 0xFFFFFFFFU, 1}},   -1}, /* -0.5000000000 */

  /*  Number greather than 1 and less than 2**31 will be rounded accordingly.  */
  {{.ldt = {0x00000000U, 0x80000000U, 0x3FFFU + 0x0000U, 0}},   1}, /* 1.0000000000 */
  {{.ldt = {0x00000000U, 0x80000000U, 0x3FFFU + 0x0000U, 1}},   -1}, /* -1.0000000000 */
  {{.ldt = {0xF7A0B800U, 0x800010C6U, 0x3FFFU + 0x0000U, 0}},   1}, /* 1.0000020000 */
  {{.ldt = {0xF7A0B800U, 0x800010C6U, 0x3FFFU + 0x0000U, 1}},   -1}, /* -1.0000020000 */
  {{.ldt = {0x00000000U, 0x80001800U, 0x3FFFU + 0x0010U, 0}},   65536}, /* 65536.1875000000 */
  {{.ldt = {0x00000000U, 0x80001800U, 0x3FFFU + 0x0010U, 1}},   -65536}, /* -65536.1875000000 */
  {{.ldt = {0x00000000U, 0x80004000U, 0x3FFFU + 0x0010U, 0}},   65537}, /* 65536.5000000000 */
  {{.ldt = {0x00000000U, 0x80004000U, 0x3FFFU + 0x0010U, 1}},   -65537}, /* -65536.5000000000 */
  {{.ldt = {0x00000000U, 0x80004D00U, 0x3FFFU + 0x0010U, 0}},   65537}, /* 65536.6015625000 */
  {{.ldt = {0x00000000U, 0x80004D00U, 0x3FFFU + 0x0010U, 1}},   -65537}, /* -65536.6015625000 */
  {{.ldt = {0x00000000U, 0xFFFFFF00U, 0x3FFFU + 0x0016U, 0}},   8388608}, /* 8388607.5000000000 */
  {{.ldt = {0x00000000U, 0xFFFFFF00U, 0x3FFFU + 0x0016U, 1}},   -8388608}, /* -8388607.5000000000 */
  {{.ldt = {0x00000000U, 0x80000500U, 0x3FFFU + 0x0014U, 0}},   1048577}, /* 1048576.6250000000 */
  {{.ldt = {0x00000000U, 0x80000500U, 0x3FFFU + 0x0014U, 1}},   -1048577}, /* -1048576.6250000000 */
  {{.ldt = {0x00000000U, 0xFFFFFFFEU, 0x3FFFU + 0x001EU, 0}},   2147483647}, /* 2147483647.0000000000 */
  {{.ldt = {0x00000000U, 0xFFFFFFFEU, 0x3FFFU + 0x001EU, 1}},   -2147483647}, /* -2147483647.0000000000 */

  /*  Number greather than 2**31 and less than 2**63 will be rounded accordingly.  */
  {{.ldt = {0x00000000U, 0x80000000U, 0x3FFFU + 0x001FU, 0}},   2147483648LL}, /* 2147483648.0000000000 */
  {{.ldt = {0x00000000U, 0x80000000U, 0x3FFFU + 0x001FU, 1}},   -2147483648LL}, /* -2147483648.0000000000 */
  {{.ldt = {0xFFFFFFFEU, 0xFFFFFFFFU, 0x3FFFU + 0x003EU, 0}},   9223372036854775807}, /* 9223372036854775807.0000000000 */
  {{.ldt = {0xFFFFFFFEU, 0xFFFFFFFFU, 0x3FFFU + 0x003EU, 1}},   -9223372036854775807}, /* -9223372036854775807.0000000000 */
  {{.ldt = {0x00000067U, 0x80000000U, 0x3FFFU + 0x0037U, 0}},   36028797018963968}, /* 36028797018963968.4023437500 */
  {{.ldt = {0x00000067U, 0x80000000U, 0x3FFFU + 0x0037U, 1}},   -36028797018963968}, /* -36028797018963968.4023437500 */
  {{.ldt = {0x00000080U, 0x80000000U, 0x3FFFU + 0x0037U, 0}},   36028797018963969}, /* 36028797018963968.5000000000000000 */
  {{.ldt = {0x00000080U, 0x80000000U, 0x3FFFU + 0x0037U, 1}},   -36028797018963969}, /* -36028797018963968.5000000000000000 */
  {{.ldt = {0x00000083U, 0x80000000U, 0x3FFFU + 0x0037U, 0}},   36028797018963969}, /* 36028797018963968.5117187500000000 */
  {{.ldt = {0x00000083U, 0x80000000U, 0x3FFFU + 0x0037U, 1}},   -36028797018963969}, /* -36028797018963968.5117187500000000 */

  {{.ldt = {0x00000000U, 0x80000000U, 0x3FFFU + 0x003FU, 0}},   -9223372036854775808ULL}, /* 9223372036854775808.0000000000000000 */
  {{.ldt = {0x00000000U, 0x80000000U, 0x3FFFU + 0x003FU, 1}},   -9223372036854775808ULL}, /* 9223372036854775808.0000000000000000 */
};

static const size_t n_tests_long_double = sizeof(tests_long_double) / sizeof(tests_long_double[0]);


int llroundl_test(void)
{
  unsigned int i, counter;

  for (counter = i = 0; i < n_tests_long_double; i++)
  {
    long long int result = llroundl(tests_long_double[i].value.ld);

    if (tests_long_double[i].should_be == result)
      counter++;
    else
      printf("llroundl test failed:  value to round = %.12Lg  result = %lld  should be = %lld\n", tests_long_double[i].value.ld, result, tests_long_double[i].should_be);
  }
  printf("%s\n", (counter < n_tests_long_double) ? "llroundl test failed." : "llroundl test succeded.");

  return (counter < n_tests_long_double) ? 1 : 0;
}
