/* Copyright (C) 1994, 1995 Charles Sandmann (sandmann@clio.rice.edu)
   Exception handling and basis for signal support for DJGPP V2.0
   This software may be freely distributed, no warranty. */
/* NEC98 and DOSV port: */
/* base code by takas 1997-2000 for libc(AT/98) */
/* modified by lpproj, 2021 */

#include <libc/stubs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <unistd.h>
#include <io.h>
#include <libc/farptrgs.h>
#include <dpmi.h>
#include <go32.h>
#include <dos.h>
#include <signal.h>
#include <setjmp.h>
#include <errno.h>
#include <crt0.h>
#include <pc.h>
#include <sys/exceptn.h>
#include <sys/nearptr.h>		/* For DS base/limit info */
#include <libc/internal.h>
#include <stubinfo.h>
#if defined SUPPORT_NEC98 || defined SUPPORT_FMR
# include <libc/_machine.h>
#endif

#define err(x) _write(STDERR_FILENO, x, sizeof(x)-1)

extern unsigned end __asm__ ("end");
static unsigned char old_video_mode = 3;
static int cbrk_vect = 0x1b;		/* May be 0x06 for PC98 */
extern unsigned _stklen;
extern unsigned __djgpp_stack_limit;
extern unsigned __djgpp_stack_top;

/* These are all defined in exceptn.S and only used here */
extern int __djgpp_exception_table;
extern int __djgpp_npx_hdlr;
#if defined SUPPORT_NEC98 || defined SUPPORT_FMR || defined SUPPORT_IBMPC
extern int __djgpp_npx_hdlr_native_mode_swint;
extern int __djgpp_timer_hwint;
extern int __djgpp_timer_hwint_reloc;
extern int __djgpp_timer_pic_imr;
extern int __djgpp_timer_pic_ocw2;
extern unsigned char __djgpp_timer_pic_mask;
#endif
extern int __djgpp_kbd_hdlr;
extern int __djgpp_kbd_hdlr_pc98;
extern short __excep_ds_alias;
extern int __djgpp_iret, __djgpp_i24;
extern void __djgpp_cbrk_hdlr(void);
extern int __djgpp_hw_lock_start, __djgpp_hw_lock_end;
extern __dpmi_paddr __djgpp_old_kbd;
extern unsigned djgpp_exception_stack __asm__("exception_stack");
extern __dpmi_paddr __djgpp_old_timer;

#if defined SUPPORT_NEC98
int __djgpp_nec98_timer_rm = 0;
extern void __djgpp_nec98_pmtimer_hdlr(void);
__dpmi_paddr __djgpp_nec98_pmtimer_ori;
extern void __djgpp_nec98_rmtimer_hdlr(void);
__dpmi_raddr __djgpp_nec98_rmtimer_ori;
static __dpmi_raddr __djgpp_nec98_rmtimer_cb;
static __dpmi_regs __djgpp_nec98_rmtimer_regs;

static
void nec98_hook_timer(void)
{
  if (__djgpp_nec98_timer_rm)
  {
    if (__djgpp_nec98_rmtimer_ori.segment == 0 && __djgpp_nec98_rmtimer_ori.offset16 == 0)
    {
      __dpmi_get_real_mode_interrupt_vector(8, &__djgpp_nec98_rmtimer_ori);
      __dpmi_allocate_real_mode_callback(__djgpp_nec98_rmtimer_hdlr, &__djgpp_nec98_rmtimer_regs, &__djgpp_nec98_rmtimer_cb);
      __dpmi_set_real_mode_interrupt_vector(8, &__djgpp_nec98_rmtimer_cb);
    }
  }
  else
  {
    if (__djgpp_nec98_pmtimer_ori.selector == 0 && __djgpp_nec98_pmtimer_ori.offset32 == 0)
    {
      __dpmi_paddr nec98_int8;
      nec98_int8.selector = _my_cs();
      nec98_int8.offset32 = (unsigned)&__djgpp_nec98_pmtimer_hdlr;
      __dpmi_get_protected_mode_interrupt_vector(8, &__djgpp_nec98_pmtimer_ori);
      __dpmi_set_protected_mode_interrupt_vector(8, &nec98_int8);
    }
  }
}

static
void nec98_unhook_timer(void)
{
  if (__djgpp_nec98_timer_rm)
  {
    if (__djgpp_nec98_rmtimer_ori.segment || __djgpp_nec98_rmtimer_ori.offset16)
    {
      __dpmi_set_real_mode_interrupt_vector(8, &__djgpp_nec98_rmtimer_ori);
      __dpmi_free_real_mode_callback(&__djgpp_nec98_rmtimer_cb);
      __djgpp_nec98_rmtimer_ori.offset16 = __djgpp_nec98_rmtimer_ori.segment = 0;
    }
  }
  else
  {
    if (__djgpp_nec98_pmtimer_ori.selector)
    {
      __dpmi_set_protected_mode_interrupt_vector(8, &__djgpp_nec98_pmtimer_ori);
      __djgpp_nec98_pmtimer_ori.offset32 = __djgpp_nec98_pmtimer_ori.selector = 0;
    }
  }
}
#endif /* SUPPORT_NEC98 */

static void
itox(int v, int len)
{
  static char buf[9]; /* startup default to all NULLs */
  char *bp = buf+7;
  while (len)
  {
    int d = v & 15;
    v >>= 4;
    *bp = d + '0';
    if (d > 9)
      *bp += 'a' - '9' - 1;
    bp--;
    len--;
  }
  _write(STDERR_FILENO, bp+1, 7-(bp-buf));
}

static int
except_to_sig(int excep)
{
  switch(excep)
  {
  case 5:
  case 8:
  case 9:
  case 11:
  case 12:
  case 13:
  case 14:
    return SIGSEGV;
  case 0:
  case 4:
  case 16:
    return SIGFPE;
  case 1:
  case 3:
    return SIGTRAP;
  case 7:
    return SIGNOFP;
  default:
#if defined SUPPORT_NEC98 || defined SUPPORT_FMR
    if (__crt0_machine_type == MACHINE_TYPE_NEC98) {
      if(excep == __djgpp_timer_hwint_reloc)
        return SIGTIMR;
      else
        return SIGILL;
    }
    else if (__crt0_machine_type == MACHINE_TYPE_FMR) {
      return SIGILL;
    }
    /* fallthrough (for IBMPC) */
#endif
    if(excep == 0x75)		/* HW int to fake exception values hardcoded in exceptn.S */
      return SIGFPE;
    else if(excep == 0x78)
      return SIGTIMR;
    else if(excep == 0x79 || excep == 0x1b)
      return SIGINT;
    else if(excep == 0x7a)
      return SIGQUIT;
    else
      return SIGILL;
  }
}

static void
show_call_frame(void)
{
  unsigned *vbp, *vbp_new, *tos;
  unsigned veip;
  int max;

  if (isatty(STDERR_FILENO))
  {
#if defined SUPPORT_NEC98 || defined SUPPORT_FMR
    max = 25;
    switch (__crt0_machine_type) {
      case MACHINE_TYPE_IBMPC:
        max =_farpeekb(_dos_ds, 0x484);
        max = (max == 0 || max == 255) ? 25 : max + 1;
        break;
      case MACHINE_TYPE_NEC98:
        max = _farpeekb(_dos_ds, 0x600 + 0x112) + 1;
        break;
    }
#else
    max =_farpeekb(_dos_ds, 0x484) + 1;	/* number of screen lines */
#endif
    if (max < 10 || max > 75)	/* sanity check */
      max = 10;			/* 10 worked for v2.0 and v2.01 */
    else
      max -= 15;		/* 13 lines of preamble + 2 for symify */
  }
  else
    /* This could be MAX_INT.  But the stack can be scrogged, so we
       limit by the maximum that the stack could hold (2 int's per frame).  */
    max = _stklen / (2*sizeof(unsigned));

  tos = (unsigned *)__djgpp_selector_limit;
  vbp = (unsigned *)__djgpp_exception_state->__ebp;
  err("Call frame traceback EIPs:\r\n  0x");
  itox(__djgpp_exception_state->__eip, 8);
  max--;
  while (((unsigned)vbp >= __djgpp_exception_state->__esp) && (vbp >= &end) && (vbp < tos))
  {
    vbp_new = (unsigned *)*vbp;
    if (vbp_new == 0)
      break;
    veip = *(vbp + 1);
    err("\r\n  0x");
    itox(veip, 8);
    vbp = vbp_new;
    if (--max <= 0)
      break;
  } 
  err("\r\n");
}

static const char *exception_names[] = {
  "Division by Zero",
  "Debug",
  "NMI",
  "Breakpoint",
  "Overflow",
  "Bounds Check",
  "Invalid Opcode",
  "Coprocessor not available",
  "Double Fault",
  "Coprocessor overrun",
  "Invalid TSS",
  "Segment Not Present",
  "Stack Fault",
  "General Protection Fault",
  "Page fault",
  0,
  "Coprocessor Error",
  "Alignment Check"
};

static char has_error[] = {0,0,0,0,0,0,0,0 ,1,0,1,1,1,1,1,0 ,0,1 };

#define EXCEPTION_COUNT (sizeof(exception_names)/sizeof(exception_names[0]))

static void
dump_selector(const char *name, int sel)
{
  unsigned long base;
  unsigned limit;
  _write(STDERR_FILENO, name, 2);
  err(": sel="); itox(sel, 4);
  if (sel) {
    if (__dpmi_get_segment_base_address(sel, &base))
    {
      err("  invalid");
    }
    else
    {
      err("  base="); itox(base, 8);
      limit = __dpmi_get_segment_limit(sel);
      err("  limit="); itox(limit, 8);
    }
  }
  err("\r\n");
}

static void
do_faulting_finish_message(int fake_exception)
{
  const char *en;
  unsigned long signum = __djgpp_exception_state->__signum;
  unsigned excpt_stack_addr = (unsigned)&djgpp_exception_stack;
  int i;
  const char *prog_name;
  
  /* check video mode for original here and reset (not if PC98) */
#if defined SUPPORT_NEC98 || defined SUPPORT_FMR
  if(__crt0_machine_type == MACHINE_TYPE_IBMPC && ScreenPrimary != 0xa0000 && _farpeekb(_dos_ds, 0x449) != old_video_mode) {
#else
  if(ScreenPrimary != 0xa0000 && _farpeekb(_dos_ds, 0x449) != old_video_mode) {
#endif
    asm volatile ("pusha;movzbl _old_video_mode,%eax; int $0x10;popa;nop");
  }
  en = (signum >= EXCEPTION_COUNT) ? 0 : 
  exception_names[signum];
  if (signum == 0x75)
    en = "Floating Point exception";
  else if (signum == 0x1b)
    en = "Control-Break Pressed";
  else if (signum == 0x79)
    en = "INTR key Pressed";
  else if (signum == 0x7a)
    en = "QUIT key Pressed";
  if (en == 0)
  {
    if (fake_exception)
      err("Raised");
    else
    {
      err("Exception ");
      itox(signum, 2);
    }
  }
  else
    _write(STDERR_FILENO, en, strlen(en));

  err(" at eip=");
  /* For fake exceptions like SIGABRT report where `raise' was called.  */
  if (fake_exception
      && __djgpp_exception_state->__cs == _my_cs()
      && (unsigned)__djgpp_exception_state->__ebp
		>= __djgpp_exception_state->__esp
      && (unsigned *)__djgpp_exception_state->__ebp >= &end
      && (unsigned *)__djgpp_exception_state->__ebp
		< (unsigned *)__djgpp_selector_limit)
    itox(*((unsigned *)__djgpp_exception_state->__ebp + 1), 8);
  else
    itox(__djgpp_exception_state->__eip, 8);

#if defined SUPPORT_NEC98 || defined SUPPORT_FMR
  if (__crt0_machine_type == MACHINE_TYPE_IBMPC && signum == 0x79)
#else
  if (signum == 0x79)
#endif
  {
    err("\r\n");
    exit(-1); /* note: `exit', not `_exit' as for the rest of signals! */
  }
  if (signum <= EXCEPTION_COUNT && has_error[signum])
  {
    unsigned int errorcode = __djgpp_exception_state->__sigmask & 0xffff;
    if(errorcode)
    {
      err(", error="); itox(errorcode, 4);
    }
  }
  if (except_to_sig(signum) == SIGFPE)
  {
#if defined SUPPORT_NEC98 || defined SUPPORT_FMR
    unsigned sw, cw;

    /* NEC98: avoid re-raising SIGFPE at _status87() */
    asm volatile ("fnstsw %0; fnstcw %1" : "=m"(sw), "=m"(cw));
    if (__crt0_machine_type != MACHINE_TYPE_IBMPC)
    {
      asm volatile ("fnclex");
    }
    err(", x87 status="); itox((sw & 0xffffU), 4);
    err(" control="); itox((cw & 0xffffU), 4);
#else
    err(", x87 status="); itox(_status87(), 4);
#endif
  }
  err("\r\neax="); itox(__djgpp_exception_state->__eax, 8);
  err(" ebx="); itox(__djgpp_exception_state->__ebx, 8);
  err(" ecx="); itox(__djgpp_exception_state->__ecx, 8);
  err(" edx="); itox(__djgpp_exception_state->__edx, 8);
  err(" esi="); itox(__djgpp_exception_state->__esi, 8);
  err(" edi="); itox(__djgpp_exception_state->__edi, 8);
  err("\r\nebp="); itox(__djgpp_exception_state->__ebp, 8);
  err(" esp="); itox(__djgpp_exception_state->__esp, 8);
  err(" program=");
  prog_name = __dos_argv0 ? __dos_argv0 : "<**UNKNOWN**>";
  for (i=0; prog_name[i]; i++);
  _write(STDERR_FILENO, prog_name, i);
  err("\r\n");
  dump_selector("cs", __djgpp_exception_state->__cs);
  dump_selector("ds", __djgpp_exception_state->__ds);
  dump_selector("es", __djgpp_exception_state->__es);
  dump_selector("fs", __djgpp_exception_state->__fs);
  dump_selector("gs", __djgpp_exception_state->__gs);
  dump_selector("ss", __djgpp_exception_state->__ss);
  err("App stack: ["); itox(__djgpp_stack_top, 8);
  err(".."); itox(__djgpp_stack_limit, 8);
  err("]  Exceptn stack: ["); itox(excpt_stack_addr+8000, 8);
  err(".."); itox(excpt_stack_addr, 8); err("]\r\n");
  err("\r\n");
  if (__djgpp_exception_state->__cs == _my_cs())
    show_call_frame();
  _exit(-1);
}

typedef void (*SignalHandler) (int);

static SignalHandler signal_list[SIGMAX];	/* SIG_DFL = 0 */

SignalHandler
signal(int sig, SignalHandler func)
{
  SignalHandler temp;
  if(sig <= 0 || sig > SIGMAX || sig == SIGKILL)
  {
    errno = EINVAL;
    return SIG_ERR;
  }
  temp = signal_list[sig - 1];
  signal_list[sig - 1] = func;
  return temp;
}

static const char signames[] = "ABRTFPE ILL SEGVTERMALRMHUP INT KILLPIPEQUITUSR1USR2NOFPTRAP";

static void print_signal_name(int sig)
{
  err("Exiting due to signal ");
  if (sig >= SIGABRT && sig <= SIGTRAP)
  {
    err("SIG");
    _write(STDERR_FILENO, signames+(sig-SIGABRT)*4, 4);
  }
  else
  {
    err("0x");
    itox(sig, 4);
  }
  err("\r\n");
}
    
void __djgpp_traceback_exit(int);

void __djgpp_traceback_exit(int sig)
{
  jmp_buf fake_exception;

  if (sig >= SIGABRT && sig <= SIGTRAP)
  {
    if (!__djgpp_exception_state_ptr)
    {
      /* This is a software signal, like SIGABRT or SIGKILL.
	 Fill the exception structure, so we get the traceback.  */
      __djgpp_exception_state_ptr = &fake_exception;
      if (setjmp(__djgpp_exception_state))
      {
	err("Bad longjmp to __djgpp_exception_state--aborting\r\n");
	do_faulting_finish_message(0); /* does not return */
      }
      else
	/* Fake the exception number.  7Ah is the last one hardwired
	   inside exceptn.S, for SIGQUIT.  */
	__djgpp_exception_state->__signum = 0x7a + 1 + sig - SIGABRT;
    }
  }
  print_signal_name(sig);
  if(__djgpp_exception_state_ptr)
    /* This exits, does not return.  */
    do_faulting_finish_message(__djgpp_exception_state == fake_exception);
  _exit(-1);
}

int
raise(int sig)
{
  SignalHandler temp;

  if(sig <= 0)
    return -1;
  if(sig > SIGMAX)
    return -1;
  temp = signal_list[sig - 1];
  if(temp == (SignalHandler)SIG_IGN
     || (sig == SIGQUIT && temp == (SignalHandler)SIG_DFL))
    return 0;			/* Ignore it */
  if(temp == (SignalHandler)SIG_DFL)
    __djgpp_traceback_exit(sig); /* this does not return */
  else if((unsigned)temp < 4096)
  {
    err("Bad signal handler, ");
    __djgpp_traceback_exit(sig); /* does not return */
  }
  else
    temp(sig);
  return 0;
}

/* This routine must call exit() or jump changing stacks.  This routine is
   the basis for traceback generation, core creation, signal handling. */
void
__djgpp_exception_processor(void)
{
  int sig;
  
  sig = except_to_sig(__djgpp_exception_state->__signum);
  raise(sig);
#if defined SUPPORT_NEC98 || defined SUPPORT_FMR
  if(__djgpp_exception_state->__signum >= EXCEPTION_COUNT /* Not exception so continue OK */
     || (__crt0_machine_type != MACHINE_TYPE_IBMPC && __djgpp_exception_state->__signum == 16) /* NEC98 (and FMR?): Floating point exception (native mode) */
    )
#else
  if(__djgpp_exception_state->__signum >= EXCEPTION_COUNT) /* Not exception so continue OK */
#endif
    longjmp(__djgpp_exception_state, __djgpp_exception_state->__eax);
  /* User handler did not exit or longjmp, we must exit */
  err("Cannot continue from exception, ");
  print_signal_name(sig);
  do_faulting_finish_message(0);
}

static __dpmi_paddr except_ori[EXCEPTION_COUNT];
static __dpmi_paddr kbd_ori;
static __dpmi_paddr npx_ori;
static __dpmi_paddr timer_ori;
static __dpmi_raddr cbrk_ori,cbrk_rmcb;
static char cbrk_hooked = 0;
static __dpmi_regs cbrk_regs;

/* Routine toggles ALL the exceptions.  Used around system calls, at exit. */

void
__djgpp_exception_toggle(void)
{
#if defined SUPPORT_NEC98 || defined SUPPORT_FMR
  /* NEC98: For Microsoft's DPMI server (DPMI.EXE in NEC DOS 5.0 or "MS-DOS Prompt" in Win3.x/9x), seems to be needed to hook 0x10 as software intrrupt */
  const int npx_int = __crt0_machine_type == MACHINE_TYPE_IBMPC ? 0x75 : 0x10;
#else
  const int npx_int = 0x75;
#endif
  __dpmi_paddr except;
  size_t i;
  
  for(i=0; i < EXCEPTION_COUNT; i++)
  {
    __dpmi_get_processor_exception_handler_vector(i, &except);
    if(i != 2 || (_crt0_startup_flags & _CRT0_FLAG_NMI_SIGNAL))
      __dpmi_set_processor_exception_handler_vector(i, &except_ori[i]);
    except_ori[i] = except;
  }
  __dpmi_get_protected_mode_interrupt_vector(npx_int, &except);
  __dpmi_set_protected_mode_interrupt_vector(npx_int, &npx_ori);
  npx_ori = except;
  __dpmi_get_protected_mode_interrupt_vector(9, &except);
  __dpmi_set_protected_mode_interrupt_vector(9, &kbd_ori);
  kbd_ori = except;
  if(cbrk_hooked) {
    __dpmi_set_real_mode_interrupt_vector(cbrk_vect, &cbrk_ori);
    __dpmi_free_real_mode_callback(&cbrk_rmcb);
    cbrk_hooked = 0;
  } else {
    __dpmi_get_real_mode_interrupt_vector(cbrk_vect, &cbrk_ori);
    __dpmi_allocate_real_mode_callback(__djgpp_cbrk_hdlr, &cbrk_regs, &cbrk_rmcb);
    __dpmi_set_real_mode_interrupt_vector(cbrk_vect, &cbrk_rmcb);
    cbrk_hooked = 1;
  }
  /* If the timer interrupt is hooked, toggle it as well.  This is so
     programs which use SIGALRM or itimer, and don't unhook the timer before
     they exit, won't leave the system with timer pointing into the void.  */
#if defined SUPPORT_NEC98 || defined SUPPORT_IBMPC
  if ((__crt0_machine_type == MACHINE_TYPE_IBMPC /* || __crt0_machine_type == MACHINE_TYPE_NEC98 */) && __djgpp_old_timer.selector != 0 && __djgpp_old_timer.offset32 != 0)
#else
  if (__djgpp_old_timer.selector != 0 && __djgpp_old_timer.offset32 != 0)
#endif
  {
    if (timer_ori.selector == __djgpp_old_timer.selector
	&& timer_ori.offset32 == __djgpp_old_timer.offset32)
    {
      __dpmi_get_protected_mode_interrupt_vector(8, &timer_ori);
      __dpmi_set_protected_mode_interrupt_vector(8, &__djgpp_old_timer);
    }
    else
    {
      __dpmi_set_protected_mode_interrupt_vector(8, &timer_ori);
      timer_ori = __djgpp_old_timer;
    }
  }
}

#define RSHIFT 1
#define LSHIFT 2
#define CTRL   4
#define ALT    8
#define SHIFT  (RSHIFT | LSHIFT)

#define DEFAULT_SIGINT  0x042e /* Ctrl-C: scan code 2Eh, kb status 04h */
#define DEFAULT_SIGQUIT 0x042b /* Ctrl-\: scan code 2Bh, kb status 04h */
#define DEFAULT_SIGINT_98  0x042b /* Ctrl-C: scan code 2Bh, kb status 04h */
#define DEFAULT_SIGQUIT_98 0x040d /* Ctrl-\: scan code 0Dh, kb status 04h */

/* Make it so the key NEW_KEY will generate the signal SIG.
   NEW_KEY must include the keyboard status byte in bits 8-15 and the
   scan code in bits 0-7.  */
static int
set_signal_key(int sig, int new_key)
{
  int old_key;
  unsigned short *mask;
  unsigned short *key;
  unsigned short kb_status;

  if (sig == SIGINT)
  {
    mask = &__djgpp_sigint_mask;
    key  = &__djgpp_sigint_key;
  }
  else if (sig == SIGQUIT)
  {
    mask = &__djgpp_sigquit_mask;
    key  = &__djgpp_sigquit_key;
  }
  else
    return -1;

  old_key = *key;

  *key = new_key & 0xffff;
  kb_status = *key >> 8;

  *mask = 0x000f;	/* Alt, Ctrl and Shift bits only */
  /* Mask off the RShift bit unless they explicitly asked for it.
     Our keyboard handler pretends that LShift is pressed when they
     press RShift.  */
  if ((kb_status & RSHIFT) == 0)
    *mask &= ~RSHIFT;
  /* Mask off the LShift bit if any of the Ctrl or Alt are set,
     since Shift doesn't matter when Ctrl and/or Alt are pressed.  */
  if (kb_status & (CTRL | ALT))
    *mask &= ~LSHIFT;

  return old_key;
}

int
__djgpp_set_sigint_key(int new_key)
{
  return set_signal_key(SIGINT, new_key);
}

int
__djgpp_set_sigquit_key(int new_key)
{
  return set_signal_key(SIGQUIT, new_key);
}

void
__djgpp_exception_setup(void)
{
  __dpmi_paddr except;
  __dpmi_meminfo lockmem;
  size_t i;

  __excep_ds_alias = __djgpp_ds_alias;
#if defined SUPPORT_NEC98 || defined SUPPORT_FMR
  if (__crt0_machine_type == MACHINE_TYPE_IBMPC)
  { /* for IBMPC */
    __djgpp_set_sigint_key(DEFAULT_SIGINT);
    __djgpp_set_sigquit_key(DEFAULT_SIGQUIT);
  }
  else if (__crt0_machine_type == MACHINE_TYPE_NEC98)
  { /* for PC98 */
    __djgpp_set_sigint_key(DEFAULT_SIGINT_98);
    __djgpp_set_sigquit_key(DEFAULT_SIGQUIT_98);
  }
  else if (__crt0_machine_type == MACHINE_TYPE_FMR)
  {
    /* todo: for FMR */
  }
#else
  if (ScreenPrimary != 0xa0000)
    {
      __djgpp_set_sigint_key(DEFAULT_SIGINT);
      __djgpp_set_sigquit_key(DEFAULT_SIGQUIT);
    }
  else
    {				/* for PC98 */
      __djgpp_set_sigint_key(DEFAULT_SIGINT_98);
      __djgpp_set_sigquit_key(DEFAULT_SIGQUIT_98);
    }
#endif

  for (i = 0; i < SIGMAX; i++)
    signal_list[i] = (SignalHandler)SIG_DFL;

  /* app_DS only used when converting HW interrupts to exceptions */
  asm volatile ("mov %ds,___djgpp_app_DS");
  asm volatile ("mov %ds,___djgpp_our_DS");
  __djgpp_dos_sel = _dos_ds;

  /* lock addresses which may see HW interrupts */
  lockmem.address = __djgpp_base_address + (unsigned) &__djgpp_hw_lock_start;
  lockmem.size = ((unsigned) &__djgpp_hw_lock_end
		  - (unsigned) &__djgpp_hw_lock_start);
  __dpmi_lock_linear_region(&lockmem);
  
  asm volatile ("mov %%cs,%0" : "=g" (except.selector) );
  except.offset32 = (unsigned) &__djgpp_exception_table;
  for(i=0; i < EXCEPTION_COUNT; i++)
  {
    except_ori[i] = except;	/* New value to set */
    except.offset32 += 4;	/* This is the size of push n, jmp */
  }
  kbd_ori.selector = npx_ori.selector = except.selector;
  npx_ori.offset32 = (unsigned) &__djgpp_npx_hdlr;
#if defined SUPPORT_NEC98 || defined SUPPORT_FMR
  if (__crt0_machine_type == MACHINE_TYPE_IBMPC)
    kbd_ori.offset32 = (unsigned) &__djgpp_kbd_hdlr;
  else if (__crt0_machine_type == MACHINE_TYPE_NEC98)
  {
    npx_ori.offset32 = (unsigned) &__djgpp_npx_hdlr_native_mode_swint;
    kbd_ori.offset32 = (unsigned) &__djgpp_kbd_hdlr_pc98;
    cbrk_vect = 0x06;
    except.offset32 = (unsigned) &__djgpp_iret;		/* TDPMI98 bug */
    __dpmi_set_protected_mode_interrupt_vector(0x23, &except);
  }
  else if (__crt0_machine_type == MACHINE_TYPE_FMR)
  {
    /* todo: for FMR */
    npx_ori.offset32 = (unsigned) &__djgpp_npx_hdlr_native_mode_swint;
  }
#else
  if(ScreenPrimary != 0xa0000)
    kbd_ori.offset32 = (unsigned) &__djgpp_kbd_hdlr;
  else
  {
    kbd_ori.offset32 = (unsigned) &__djgpp_kbd_hdlr_pc98;
    cbrk_vect = 0x06;
    except.offset32 = (unsigned) &__djgpp_iret;		/* TDPMI98 bug */
    __dpmi_set_protected_mode_interrupt_vector(0x23, &except);
  }
#endif
  except.offset32 = (unsigned) &__djgpp_i24;
  __dpmi_set_protected_mode_interrupt_vector(0x24, &except);

#if defined SUPPORT_NEC98
  if (__crt0_machine_type == MACHINE_TYPE_NEC98)
  {
    int dummy_capflags;
    char hostinfo[128];
    memset(hostinfo, 0, sizeof(hostinfo));
    __dpmi_get_capabilities(&dummy_capflags, hostinfo);
    __djgpp_nec98_timer_rm = *(unsigned *)(hostinfo + 2) == 0x204f2d49U; /* check I-O DATA DPMI */
    nec98_hook_timer();
  }
#endif

  __dpmi_get_protected_mode_interrupt_vector(9, &__djgpp_old_kbd);
  __dpmi_get_protected_mode_interrupt_vector(8, &timer_ori);
  __djgpp_exception_toggle();	/* Set new values & save old values */
#if defined SUPPORT_NEC98
  if (__crt0_machine_type == MACHINE_TYPE_NEC98)
  {
    /* start 10ms interval timer */
    if (__djgpp_nec98_info.Ir0Masked)
    {
# if defined NEC98_MODIFY_PIT
      /* (seems to be needed for some version of T98Next */
      unsigned cnt10ms = (__djgpp_nec98_info.s0501 & 0x80) ? 19968 : 24576;
      unsigned char imr;
      disable();
      outportb(0x77, 0x36);
      imr = inportb(0x02);
      outportb(0x71, cnt10ms & 0xff);
      __djgpp_nec98_iowait();
      outportb(0x71, cnt10ms >> 8);
      __djgpp_nec98_iowait();
      outportb(0x02, imr & 0xfe);
      enable();
# else
      __dpmi_regs r;
      unsigned char imr;
      r.x.ax = 0x3507;
      __dpmi_int(0x21, &r); /* es:bx = vect07 */
      /* set PIT (and unmask IR0) via timer BIOS */
      /* do not modify PIT registers directly (workaround for anex86) */
      r.h.ah = 0x02;
      r.x.cx = 0xffff;
      __dpmi_int(0x1c, &r);
      /* unmask IR0 explicitly (needed for Win3.x DOS prompt) */
      imr = inportb(0x02);
      __djgpp_nec98_iowait();
      outportb(0x02, imr & 0xfe);
# endif /* NEC98_MODIFY_PIT */
    }
  }
#endif

  /* get original video mode and save */
  old_video_mode = _farpeekb(_dos_ds, 0x449);
}

int
__djgpp_set_ctrl_c(int enable_sigs)
{
  int oldenable = !(__djgpp_hwint_flags & 1);
  if (enable_sigs >= 0)
  {
    if (enable_sigs)
      __djgpp_hwint_flags &= ~1;
    else
      __djgpp_hwint_flags |= 1;
  }
  return oldenable;
}

/* A work-around for a bug in W2K's NTVDM, suggested by
   The Owl <theowl@freemail.c3.hu>.

   When a DPMI program exits, NTVDM frees up all memory blocks allocated
   by the program and then it resets its notion of the current program's
   PSP selector to 0.  If that DPMI program was spawned by another DPMI
   program, and the parent program exits while the PSP selector recorded
   by NTVDM is still 0, NTVDM will free up all memory blocks allocated
   by DOSX, the NT DOS extender.  That memory includes the locked PM
   stack used for processing hardware interrupts reflected into protected
   mode.  Thereafter, any hardware interrupt (a timer tick, a keyboard
   keypress, anything) will crash NTVDM because NTVDM will try to use a
   stack which was freed.

   The bug which causes this is that NTVDM resets the PSP to 0,
   instead of setting it to the PSP of the parent program.  (Ironically,
   DOSX does pass the parent PSP selector to NTVDM when it notifies it
   about a DPMI program exit, but NTVDM does not use this information.)

   To work around that, we ask NTVDM to record a valid PSP before we
   exit.  We do that by invoking a PM Int 21h, function 50h, which sets
   the PM selector for the PSP (which triggers NTVDM to record the
   correct internal value).  We do that just before exiting, to make 
   sure that even an application which crashes (e.g., due to SIGSEGV 
   or Ctrl-BREAK) immediately after its child returns will always leave 
   its valid PSP recorded by NTVDM before it exits.

   (To play it safe in the face of non-DJGPP DPMI programs and old
   DJGPP programs, we also restore the PSP in dosexec.c, which see.)

   Note that we invoke here a PM Int 21, which sets the PM selector of
   our PSP.  This is _not_ a call to __dpmi_int ! */

void
__maybe_fix_w2k_ntvdm_bug(void)
{
  if (_os_trueversion == 0x532) /* Windows NT, 2000 or XP? */
  {
   if(_stubinfo->size < STUBINFO_END)	/* V2load'ed image, stubinfo PSP bad */

    /* Protected mode call to SetPSP - uses BX from GetPSP (0x51) */
    asm volatile("movb $0x51, %%ah                        \n\
                  int  $0x21                              \n\
                  movb $0x50, %%ah                        \n\
                  int  $0x21                              "
                  : : : "ax", "bx" );             /* output, input, regs */
   else

    /* Protected mode call to SetPSP - may destroy RM PSP if not extended */
    asm volatile("movw %0, %%bx                           \n\
                  movb $0x50, %%ah                        \n\
                  int  $0x21                              "
                  :                               /* output */
                  : "g" (_stubinfo->psp_selector) /* input */
                  : "ax", "bx" );                 /* regs */
  }
}

void __attribute__((noreturn))
_exit(int status)
{
  __maybe_fix_w2k_ntvdm_bug();
  /* If we are exiting due to an FP exception, the next program run in the
     same DOS box on Windows crashes during startup.  Clearing the 80x87
     seems to prevent this, at least in some cases.  We only do that if a
     coprocessor is actually present.  */
  if (_8087)
    _clear87();
#if defined SUPPORT_NEC98
  if (__crt0_machine_type == MACHINE_TYPE_NEC98)
  {
    _farpokew(_dos_ds, 0x58a, __djgpp_nec98_info.s058a);
    if (__djgpp_nec98_info.Ir0Masked)
    {
      unsigned char imr;
      disable();
      imr = inportb(0x02);
      __djgpp_nec98_iowait();
      outportb(0x02, imr | 1); /* mask IR0 */
      enable();
    }
  }
#endif
  /* We need to restore hardware interrupt handlers even if somebody calls
     `_exit' directly, or else we crash the machine in nested programs.
     We only toggle the handlers if the original keyboard handler is intact
     (otherwise, they might have already toggled them).  */
  if (__djgpp_old_kbd.offset32 == kbd_ori.offset32
      && __djgpp_old_kbd.selector == kbd_ori.selector)
    __djgpp_exception_toggle ();
#if defined SUPPORT_NEC98
  if (__crt0_machine_type == MACHINE_TYPE_NEC98)
    nec98_unhook_timer();
#endif
  __exit (status);
}

#ifdef TEST

#include <string.h>

int
main(void)
{
  volatile int count = 0;	/* don't let gcc optimize it away */

  __djgpp_set_sigint_key (0x0522); /* Ctrl-RShift-G */
  signal (SIGQUIT, __djgpp_traceback_exit);

  while (1)
  {
    char buf[30];

    count++;
    if (count % 100000 == 0)
    {
      sprintf (buf, "counted to %d\r\n", count);
      _write(STDERR_FILENO, buf, strlen (buf));
    }
    if (count >= 1000000000L)
      count = 0;
  }

  return 0;
}

#endif
