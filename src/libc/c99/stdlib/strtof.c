/* Copyright (C) 2013 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2008 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2003 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2002 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2001 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1997 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1994 DJ Delorie, see COPYING.DJ for details */
#include <libc/stubs.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <libc/unconst.h>
#include <libc/ieee.h>

#define HEX_DIGIT_SIZE    (4)
#define FLOAT_BIAS        (0x7FU)
#define MAX_BIN_EXPONENT  (127)   /*  Max. and min. binary exponent (inclusive) as  */
#define MIN_BIN_EXPONENT  (-126)  /*  defined in Intel manual (253665.pdf, Table 4.2).  */
#define IS_DEC_DIGIT(x)   (((x) >= '0') && ((x) <= '9'))
#define IS_HEX_DIGIT(x)   ((((x) >= 'A') && ((x) <= 'F')) || \
                           (((x) >= 'a') && ((x) <= 'f')) || \
                           IS_DEC_DIGIT(x))
#define IS_EXPONENT(x)    (((x[0]) == 'P' || (x[0]) == 'p') && \
                           (x[1] == '+' || x[1] == '-' || IS_DEC_DIGIT(x[1])))


float
strtof(const char *s, char **sret)
{
  long double r = 0;            /* result */
  int e = 0;                    /* exponent */
  long double d;                /* scale */
  int sign = 1;                 /* +- 1.0 */
  int esign = 1;
  int i;
  int flags = 0;
  int overflow = 0;
  char decimal_point = localeconv()->decimal_point[0];


  while (isspace((unsigned char) *s))
    s++;

  if (*s == '+')
    s++;
  else if (*s == '-')
  {
    sign = -1;
    s++;
  }

  /* Handle INF and INFINITY. */
  if (!strnicmp("INF", s, 3))
  {
    if (sret)
    {
      if (!strnicmp( "INITY", &s[3], 5))
        *sret = unconst((&s[8]), char *);
      else
        *sret = unconst((&s[3]), char *);
    }

    return (0 > sign) ? -INFINITY : INFINITY;
  }

  /* Handle NAN and NAN(<hex-number>). */
  if (!strnicmp("NAN", s, 3))
  {
    _float_union_t t;

    t.f = NAN;

    if (sign < 0)
      t.ft.sign = 1;

    if (s[3] == '(')
    {
      unsigned long mantissa_bits = 0;
      char *endptr = unconst((&s[4]), char *);

      mantissa_bits = strtoul(&s[4], &endptr, 0);
      if (*endptr == ')')
      {
        mantissa_bits = mantissa_bits & 0x7fffff;
        if (mantissa_bits)
          t.ft.mantissa = mantissa_bits;
        if (sret)
          *sret = endptr + 1;

        return t.f;
      }

      /* The subject sequence didn't match NAN(<number>),
         so match only NAN. */
    }

    if (sret)
      *sret = unconst((&s[3]), char *);

    return t.f;
  }

  /* Handle 0xH.HHH[p|P][+|-]DDD. */
  if (!strnicmp("0x", s, 2) && (s[2] == '.' || IS_HEX_DIGIT(s[2])))
  {
    int digits, integer_digits;
    int bin_exponent;
    unsigned long int mantissa;
    _float_union_t ieee754;


    /*
     *  Mantissa.
     *  6 hex digits fit into the mantissa
     *  including the implicit integer bit.
     */
    bin_exponent = 0;
    integer_digits = 0;
    mantissa = 0x00U;
    s += 2;
    while (integer_digits < 8 && IS_HEX_DIGIT(*s))
    {
      flags = 1;
      mantissa <<= HEX_DIGIT_SIZE;
      mantissa += IS_DEC_DIGIT(*s) ? *s - '0' :
                  ((*s >= 'A') && (*s <= 'F')) ? *s - 'A' + 10 : *s - 'a' + 10;
      if (mantissa)        /*  Discarts leading zeros.  */
        integer_digits++;  /*  Counts hex digits.  16**integer_digits.  */
      s++;
    }
    if (integer_digits)
    {
      /*
       *  Compute the binary exponent for a normalized mantissa by
       *  shifting the decimal point inside the most significant hex digit.
       */
      unsigned long bit = 0x01ULL;

      for (digits = 0; IS_HEX_DIGIT(*s); s++)
        digits++;  /*  Counts hex digits.  */
      bin_exponent = integer_digits * HEX_DIGIT_SIZE - 1;  /*  2**bin_exponent.  */
      for (bit <<= bin_exponent; !(mantissa & bit); bin_exponent--)
        bit >>= 1;
      bin_exponent += digits * HEX_DIGIT_SIZE;
    }

    if (*s == decimal_point)
    {
      int fraction_zeros = 0;

      s++;
      digits = integer_digits;
      while ((digits - fraction_zeros) < 8 && IS_HEX_DIGIT(*s))
      {
        flags = 1;
        digits++;  /*  Counts hex digits.  */
        mantissa <<= HEX_DIGIT_SIZE;
        mantissa += IS_DEC_DIGIT(*s) ? *s - '0' :
                    ((*s >= 'A') && (*s <= 'F')) ? *s - 'A' + 10 : *s - 'a' + 10;
        if (mantissa == 0)
          fraction_zeros++;  /*  Counts hex zeros.  16**(-fraction_zeros + 1).  */
        s++;
      }
      if (!integer_digits && mantissa)
      {
        /*
         *  Compute the binary exponent for a normalized mantissa by
         *  shifting the decimal point inside the most significant hex digit.
         */
        unsigned long long bit = 0x01ULL;

        bin_exponent = -fraction_zeros * HEX_DIGIT_SIZE;  /*  2**bin_exponent.  */
        for (bit <<= (digits * HEX_DIGIT_SIZE + bin_exponent); !(mantissa & bit); bin_exponent--)
          bit >>= 1;
      }
    }

    if (!flags)
    {
      if (sret)
        *sret = unconst(s, char *);
      errno = EINVAL;  /*  No valid mantissa, no convertion could be performed.  */
      return 0.0;
    }

    if (mantissa)
    {
      /*
       *  Normalize mantissa.
       */
      while (!(mantissa & 0x80000000ULL))
        mantissa <<= 1;  /*  Shift a binary 1 into the integer part of the mantissa.  */
      mantissa >>= (31 - 23);
      /*  At this point the mantissa is normalized and the exponent has been adjusted accordingly.  */
    }


    /*
     *  After discarting all hex digits left,
     *  if the next character is P or p
     *  continue with the extracting of the
     *  exponent, else any other character
     *  that have appeared terminates the number.
     */
    while (IS_HEX_DIGIT(*s))
      s++;

    /*
     *  Exponent.
     */
    if (IS_EXPONENT(s))
    {
      int exponent = 0.0;
      s++;
      if (*s == '+')
        s++;
      else if (*s == '-')
      {
        esign = -1;
        s++;
      }

      while ((esign * exponent + bin_exponent) < (MAX_BIN_EXPONENT + 1) && IS_DEC_DIGIT(*s))
      {
        exponent *= 10;
        exponent += *s - '0';
        s++;
      }
      bin_exponent += esign * exponent;  /*  2**bin_exponent.  */
      while (IS_DEC_DIGIT(*s))
        s++;  /*  Discart rest of exponent.  */
    }


    if (sret)
      *sret = unconst(s, char *);
    if (mantissa)
    {
      if (bin_exponent > MAX_BIN_EXPONENT)
      {
        errno = ERANGE;
        return sign * HUGE_VALF;
      }
      else if(bin_exponent < MIN_BIN_EXPONENT)
      {
        errno = ERANGE;
        return 0.0;
      }
      ieee754.ft.sign     = (sign == 1) ? 0 : 1;
      ieee754.ft.exponent = 0x07FFU & (bin_exponent + FLOAT_BIAS);
      ieee754.ft.mantissa = 0x007FFFFFU & mantissa;
    }
    else
      ieee754.f = sign * 0.0;

    return ieee754.f;
  }

  /* Handle ordinary numbers. */
  while (IS_DEC_DIGIT(*s))
  {
    flags |= 1;
    r *= 10.0;
    r += *s - '0';
    s++;
  }

  if (*s == decimal_point)
  {
    d = 0.1L;
    s++;
    while ((*s >= '0') && (*s <= '9'))
    {
      flags |= 2;
      r += d * (*s - '0');
      s++;
      d *= 0.1L;
    }
  }
  if (flags == 0)
  {
    if (sret)
      *sret = unconst(s, char *);
    return 0.0;
  }

  if ((*s == 'e') || (*s == 'E'))
  {
    s++;
    if (*s == '+')
      s++;
    else if (*s == '-')
    {
      s++;
      esign = -1;
    }
    while (IS_DEC_DIGIT(*s))
    {
      e *= 10;
      e += *s - '0';
      s++;
    }
  }

  /* Detect overflow.  */
  if (e < 0)
  {
    errno = ERANGE;
    r = 0.0;
    overflow = 1;
  }
  else if (esign < 0)
  {
    const int exp = e + 1;
    for (i = 1; i < exp; i++)
    {
      r *= 0.1L;
      /* Detect underflow below 2^-150, which is half
         the smallest representable float. */
      if (r < 7.00649232162408535461e-46L)
      {
        errno = ERANGE;
        r = 0.0;
        break;
      }
    }
  }
  else
  {
    const int exp = e + 1;
    for (i = 1; i < exp; i++)
    {
      r *= 10.0;
      if (r > FLT_MAX)  /* detect overflow */
      {
        errno = ERANGE;
        r = 0;
        overflow = 1;
        break;
      }
    }
  }

  if (sret)
    *sret = unconst(s, char *);

  if (!overflow)
    return r * sign;
  else
    return HUGE_VALF * sign;
}
