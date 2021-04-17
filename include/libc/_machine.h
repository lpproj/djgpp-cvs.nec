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

#ifdef __cplusplus
}
#endif


#endif /* !_POSIX_SOURCE */
#endif /* !__STRICT_ANSI__ */
#endif /* !__dj_ENFORCE_ANSI_FREESTANDING */


#endif /* !__dj_include_libc__machine_h_ */

