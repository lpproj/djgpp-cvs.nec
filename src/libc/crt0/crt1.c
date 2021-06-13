/* Copyright (C) 2015 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2004 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2003 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 2002 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1999 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1998 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1997 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1996 DJ Delorie, see COPYING.DJ for details */
/* Copyright (C) 1995 DJ Delorie, see COPYING.DJ for details */
/* NEC98 and DOSV port: */
/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */
#include <libc/stubs.h>
#include <crt0.h>
#include <string.h>
#include <libc/internal.h>
#include <stdlib.h>
#include <errno.h>
#include <go32.h>
#include <stubinfo.h>
#include <dpmi.h>
#include <libc/farptrgs.h>
#include <pc.h>
#include <libc/bss.h>
#include <fcntl.h>
#include <unistd.h>
#include <libc/environ.h>
#include <dos.h> /* for _osmajor/_osminor */
#include <libc/unconst.h>

/* Global variables */

#define ds _my_ds()

/* This gets incremented each time the program is started.
   Programs (such as Emacs) which dump their code to create
   a new executable, cause this to be larger than 2.  Library
   functions that cache info in static variables should check
   the value of `__bss_count' if they need to reinitialize
   the static storage.  */
int __bss_count = 1;

#if defined SUPPORT_NEC98 || defined SUPPORT_FMR
# define __djgpp_nec98_SYSTEMINFO_CONST
# include <libc/_machine.h>
extern int __djgpp_timer_hwint;
extern int __djgpp_timer_hwint_reloc;
extern int __djgpp_timer_pic_imr;
extern int __djgpp_timer_pic_ocw2;
extern unsigned char __djgpp_timer_pic_mask;

int __crt0_mtype = 0;
unsigned char __crt0_machine_type = 0;
unsigned char __crt0_machine_subtype = 0;
# ifdef SUPPORT_NEC98
__djgpp_nec98_SYSMEMINFO __djgpp_nec98_info;
int __djgpp_nec98_test_artic(void);
unsigned __djgpp_nec98_artic_org24, __djgpp_nec98_artic_prev24;
unsigned long long __djgpp_nec98_get_artic64(void);
# endif
#endif

extern char **_environ;

int __crt0_argc;
char **__crt0_argv;

/* Local variables */

static void
setup_core_selector(void)
{
  int c = __dpmi_allocate_ldt_descriptors(1);
  if (c == -1)
  {
    /* We cannot continue without a valid _dos_ds selector, since
       setup_screens, called next, already uses it, and will crash
       unless we do something.

       The failure to allocate a descriptor is known to happen on
       Windows, when a long nested job (e.g., large recursive
       Makefile) is in progress, due to the fact that the Windows DPMI
       host leaks descriptors.

       So we want to print an error message and exit; but the tricky
       part is that we cannot use the transfer buffer or any other
       buffer in conventional memory, because we don't have a selector
       for DOS memory.  That's why we use function 02 of Int 21h.
       (The idea is due to Morten Welinder.)  */
    static const char no_dos_ds_msg[] =
      "Cannot allocate selector for conventional memory; exiting\r\n";
    const char *p = no_dos_ds_msg;
    __dpmi_regs r;

    while (*p)
    {
      r.h.ah = 2;  /* in case DOS clobbers it */
      r.h.dl = *p & 0xff;
      __dpmi_int(0x21, &r);
      p++;
    }
    __exit(107);  /* the same error code stub.asm uses for no selectors */
  }
  _dos_ds = c;

  /* This was -1, but DPMI doesn't guarantee more than 1M + 64K */
  __dpmi_set_segment_limit(_dos_ds, 0x10ffff);
}

static void
setup_screens(void)
{
#if defined SUPPORT_NEC98 || defined SUPPORT_FMR
  /* todo: FMR */
  if (__crt0_machine_type == MACHINE_TYPE_NEC98) {
    unsigned s = (unsigned)(_farpeekw(_dos_ds, 0x600 + 0x32)) * 16U;
    if (s == 0) {
      s = __crt0_machine_subtype == MACHINE_SUBTYPE_NEC98_HIRES ? 0xe0000 : 0xa0000;
    }
    ScreenPrimary = ScreenSecondary = s;
  }
  else if (__crt0_machine_type == MACHINE_TYPE_IBMPC && (__crt0_machine_subtype & 0xf0) == MACHINE_SUBTYPE_IBMPC_TOPVIEW) {
    ScreenSecondary = ScreenPrimary;
  }
#else
  if(_farpeekw(_dos_ds, 0xffff3) == 0xfd80)	/* NEC PC98 ? */
  {
    ScreenPrimary = ScreenSecondary = 0xa0000;
  }
#endif
  else if (_farpeekb(_dos_ds, 0x449) == 7)
  {
    ScreenPrimary = 0xb0000;
    ScreenSecondary = 0xb8000;
  }
  else
  {
    ScreenPrimary = 0xb8000;
    ScreenSecondary = 0xb0000;
  }
}

static void
setup_go32_info_block(void)
{
  __dpmi_version_ret ver;

  __dpmi_get_version(&ver);

  _go32_info_block.size_of_this_structure_in_bytes = sizeof(_go32_info_block);
  __tb = _stubinfo->ds_segment * 16;
  __tb_size = _stubinfo->minkeep;
  _go32_info_block.pid = _stubinfo->psp_selector;
  _go32_info_block.master_interrupt_controller_base = ver.master_pic;
  _go32_info_block.slave_interrupt_controller_base = ver.slave_pic;
  _go32_info_block.linear_address_of_stub_info_structure = 0xffffffffU; /* force error */
  __dpmi_get_segment_base_address(_stubinfo->psp_selector,
    &_go32_info_block.linear_address_of_original_psp);
  _go32_info_block.run_mode = _GO32_RUN_MODE_DPMI;
  _go32_info_block.run_mode_info = (ver.major << 8) | (ver.minor);
}

char *__dos_argv0;

static void
setup_environment(void)
{
  char *dos_environ = alloca(_stubinfo->env_size), *cp;
  short env_selector;
  int env_count=0;
  movedata(_stubinfo->psp_selector, 0x2c, ds, (int)&env_selector, 2);
  movedata(env_selector, 0, ds, (int)dos_environ, _stubinfo->env_size);
  cp = dos_environ;
  do {
    env_count++;
    while (*cp) cp++; /* skip to NUL */
    cp++; /* skip to next character */
  } while (*cp); /* repeat until two NULs */
  _environ = (char **)malloc((env_count+1) * sizeof(char *));
  if (_environ == 0)
    return;

  cp = dos_environ;
  env_count = 0;
  do {
    /* putenv assumes each string is malloc'd */
    _environ[env_count] = (char *)malloc(strlen(cp)+1);
    strcpy(_environ[env_count], cp);
    env_count++;
    while (*cp) cp++; /* skip to NUL */
    cp++; /* skip to next character */
  } while (*cp); /* repeat until two NULs */
  _environ[env_count] = 0;

  /*
   * Call putenv so that its static counters are computed. If this
   * is not done, programs that manipulate `_environ' directly will crash,
   * when `DJGPP' is not set in the environment.
   */
  putenv(unconst("", char *));
  
  __dos_argv0 = (char *)malloc(strlen(cp + 3)+1);
  if (__dos_argv0 == 0)
    abort();
  strcpy(__dos_argv0, cp+3);
}

static char *prog_name;

static void
setup_pname(void)
{
  char *ap, *fc;

  fc = __dos_argv0;
  for(ap = __dos_argv0; *ap; ap++)
    if(*ap == ':' || *ap == '\\' || *ap == '/')
      fc = ap + 1;

  if(_stubinfo->argv0[0])
    {
      fc = _stubinfo->argv0;
    }

  prog_name = (char *)calloc(1, strlen(fc) + 1);
  strcpy(prog_name, fc);
}

extern void __main(void);
extern int  main(int, char **, char **);
extern void _crt0_init_mcount(void);	/* For profiling */
extern void __setup_file_rec_list(void);

char __PROXY[] = " !proxy";
size_t __PROXY_LEN = sizeof(__PROXY)-1;
unsigned short _os_trueversion;

static void
setup_os_version(void)
{
  unsigned short v;
  _os_trueversion = _get_dos_version(1);
  v = _get_dos_version(0); /* Get the reported version */
  _osmajor = (v >> 8) & 0xff; /* paranoia */
  _osminor = v & 0xff;
}

#if defined SUPPORT_NEC98 || defined SUPPORT_FMR
static void
setup_machine_type(void)
{
  __dpmi_regs regs;

  /* todo: check FMR at first (for MACHINE_TYPE_FMR */
  if (_farpeekw(_dos_ds, 0xffff3) == 0xfd80) {
    __crt0_machine_type = MACHINE_TYPE_NEC98;
    /* __crt0_machine_subtype = MACHINE_SUBTYPE_NEC98_NORMAL */
  }
  else {
    regs.x.ax = 0x0f07;
    __dpmi_int(0x10, &regs);
    if (regs.h.ah == 0x0f) __crt0_machine_type = MACHINE_TYPE_NEC98;
    else __crt0_machine_type = MACHINE_TYPE_IBMPC;
  }

  switch(__crt0_machine_type) {
    case MACHINE_TYPE_IBMPC: {
      __djgpp_timer_pic_imr = 0x21;
      __djgpp_timer_pic_ocw2 = 0x20;
      regs.h.ah = 0xfe;
      regs.x.di = 0;
      regs.x.es = 0xb800;
      __dpmi_int(0x10, &regs);
      if (regs.x.di == 0 || regs.x.es == 0xb800) {
        __crt0_machine_subtype = MACHINE_SUBTYPE_IBMPC;
      }
      else {
        __crt0_machine_subtype = MACHINE_SUBTYPE_IBMPC_TOPVIEW;
        ScreenPrimary = (unsigned)(regs.x.es) * 16U + regs.x.di;
        regs.x.ax = 0x4900;
        regs.x.bx = 0;
        __dpmi_int(0x15, &regs);
        if (regs.h.ah == 0 && regs.h.bl < 15) {
          __crt0_machine_subtype += (regs.h.bl + 1);
          __crt0_mtype = __crt0_mtype_DOSV;
        }
      }
      break;
    }
# if defined SUPPORT_NEC98
    case MACHINE_TYPE_NEC98: {
      __djgpp_timer_pic_imr = 0x02;
      __djgpp_timer_pic_ocw2 = 0x00;
      __djgpp_nec98_info.s0458 = _farpeekb(_dos_ds, 0x458);
      __djgpp_nec98_info.s045b = _farpeekb(_dos_ds, 0x45b);
      __djgpp_nec98_info.s0500 = _farpeekb(_dos_ds, 0x500);
      __djgpp_nec98_info.s0501 = _farpeekb(_dos_ds, 0x501);
      __djgpp_nec98_info.s054d = _farpeekb(_dos_ds, 0x54d);
      __djgpp_nec98_info.s058a = _farpeekw(_dos_ds, 0x58a);
      __djgpp_nec98_info.Ir0Masked = inportb(0x02) & 1;
      if (__djgpp_nec98_info.s0458 & 0x80) {
        __djgpp_nec98_info.hasWait5f = 1;
        __djgpp_nec98_info.hasArtic = 1;
      }
      else {
        __djgpp_nec98_info.hasWait5f = (__djgpp_nec98_info.s045b & 0x80) != 0;
        __djgpp_nec98_info.hasArtic = (__djgpp_nec98_info.s045b & 0x04) != 0;
      }
      if ((__djgpp_nec98_info.s0501 & 0x08) == 0x08) {
        __crt0_machine_subtype = MACHINE_SUBTYPE_NEC98_HIRES;
        __crt0_mtype = __crt0_mtype_PC98H;
      }
      else {
        __crt0_machine_subtype = MACHINE_SUBTYPE_NEC98_NORMAL;
        __crt0_mtype = __crt0_mtype_PC98;
      }
      if (!__djgpp_nec98_info.hasArtic) {
        /* workaround for some emulators (anex86/t98next) */
        __djgpp_nec98_info.hasArtic = (__djgpp_nec98_test_artic() != 0);
      }
      regs.d.eax = 0x80ff;
      regs.d.ecx = 0xffff;
      __dpmi_int(0x1c, &regs);
      __djgpp_nec98_info.has32ndSecTimer = (regs.h.al <= 3 && regs.x.cx < 0xffff);
      break;
    }
# endif /* SUPPORT_NEC98 */
  }
}
#endif /* SUPPORT_NEC98 || SUPPORT_FMR */


void
__crt1_startup(void)
{
  __bss_count ++;
  __crt0_argv = 0;
  setup_os_version();
  setup_core_selector();
#if defined SUPPORT_NEC98 || defined SUPPORT_FMR
  setup_machine_type();
#endif
  setup_screens();
  setup_go32_info_block();
  __djgpp_exception_setup();
  setup_environment();
  __environ_changed++;
  __setup_file_rec_list();
  /* Make so rest of startup could use LFN.  */
  (void)_USE_LFN;
  setup_pname();
  __crt0_load_environment_file(prog_name);
  (void)_USE_LFN;	/* DJGPP.ENV might have set $LFN */
  free(prog_name);
  __crt0_setup_arguments();
  _npxsetup(__crt0_argv ? __crt0_argv[0] : __dos_argv0);
  _crt0_init_mcount();
  __main();
  errno = 0;	/* ANSI says errno should be zero at program startup */
  exit(main(__crt0_argc, __crt0_argv, _environ));
}

