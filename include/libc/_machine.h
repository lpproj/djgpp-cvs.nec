#ifndef __dj_include_libc__machine_h_
#define __dj_include_libc__machine_h_

#ifndef __dj_ENFORCE_ANSI_FREESTANDING

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) \
  || !defined(__STRICT_ANSI__) || defined(__cplusplus)

#endif /* (__STDC_VERSION__ >= 199901L) || !__STRICT_ANSI__ */

#ifndef __STRICT_ANSI__

#ifndef _POSIX_SOURCE

#if defined SUPPORT_IBMPC || defined SUPPORT_NEC98 || defined SUPPORT_FMR
# include <stdio.h>
# include <stdlib.h>
#endif

#define __crt0_mtype_PCAT   0x00
#define __crt0_mtype_DOSV   0x01
#define __crt0_mtype_PC98   0x10
#define __crt0_mtype_PC98H  0x11

#define MACHINE_TYPE_IBMPC  0
#define MACHINE_TYPE_NEC98  1
#define MACHINE_TYPE_FMR    2   /* reserved (not supported, for now) */

#define MACHINE_SUBTYPE_NEC98_NORMAL    0
#define MACHINE_SUBTYPE_NEC98_HIRES     1

#define MACHINE_SUBTYPE_IBMPC           0x00
#define MACHINE_SUBTYPE_IBMPC_TOPVIEW   0x10
#define MACHINE_SUBTYPE_IBMPC_DOSV      (MACHINE_SUBTYPE_IBMPC_TOPVIEW | 0x01)


#ifdef __cplusplus
extern "C" {
#endif

extern unsigned char __crt0_machine_type;
extern unsigned char __crt0_machine_subtype;

#if defined SUPPORT_IBMPC || defined SUPPORT_NEC98 || defined SUPPORT_FMR
static inline __libc_unsupported_platform(const char *n) {
  fprintf(stderr, "FATAL: unsupported platform in %s\n", n);
  abort();
}
# define ABORT_UNSUPPORTED __libc_unsupported_platform(__func__)
#else
# define ABORT_UNSUPPORTED abort()
#endif

# ifdef SUPPORT_NEC98
#  ifndef __djgpp_nec98_SYSTEMINFO_CONST
#   define __djgpp_nec98_SYSTEMINFO_CONST const
#  endif
typedef struct {
  __djgpp_nec98_SYSTEMINFO_CONST unsigned char s0458;
  __djgpp_nec98_SYSTEMINFO_CONST unsigned char s045b;
  __djgpp_nec98_SYSTEMINFO_CONST unsigned char s0500;
  __djgpp_nec98_SYSTEMINFO_CONST unsigned char s0501;
  __djgpp_nec98_SYSTEMINFO_CONST unsigned char s054d;
  __djgpp_nec98_SYSTEMINFO_CONST unsigned char Ir0Masked;
  __djgpp_nec98_SYSTEMINFO_CONST unsigned short s058a;
  __djgpp_nec98_SYSTEMINFO_CONST volatile unsigned char hasWait5f;
  __djgpp_nec98_SYSTEMINFO_CONST unsigned char hasArtic;
  __djgpp_nec98_SYSTEMINFO_CONST unsigned char has32ndSecTimer;
} __attribute__ ((packed)) __djgpp_nec98_SYSMEMINFO;

extern __djgpp_nec98_SYSMEMINFO __djgpp_nec98_info;

static inline void __djgpp_nec98_iowait(void) { if (__djgpp_nec98_info.hasWait5f) outportb(0x5f, 0); }
# endif

#ifdef __cplusplus
}
#endif


#endif /* !_POSIX_SOURCE */
#endif /* !__STRICT_ANSI__ */
#endif /* !__dj_ENFORCE_ANSI_FREESTANDING */


#endif /* !__dj_include_libc__machine_h_ */

