#ifndef __dj_include_machine_specific_itimer_h_
#define __dj_include_machine_specific_itimer_h_

/* src/libc/go32/exceptn.S */
/* src/libc/crt0/crt1.c */
extern long __djgpp_timer_countdown;
extern uclock_t __djgpp_timer_tick; /* uclock_t == long long */
extern int __djgpp_timer_hwint;
extern int __djgpp_timer_hwint_reloc;
extern int __djgpp_timer_pic_imr;
extern int __djgpp_timer_pic_ocw2;
extern unsigned char __djgpp_timer_pic_mask;

extern __dpmi_paddr __djgpp_old_timer;
extern int __djgpp_timer_hdlr;

/* src/libc/posix/signal/itimer.c */
extern long __djgpp_clock_tick_interval;

void __libc_itimer_handle_itimer_ibmpc(void);
void __libc_itimer_handle_itimer_nec98(void);
extern void (*__libc_itimer_pf_handle_itimer)(void);
void __libc_itimer_unhandle_itimer_ibmpc(void);
void __libc_itimer_unhandle_itimer_nec98(void);
extern void (*__libc_itimer_pf_unhandle_itimer)(void);

static inline void handle_itimer(void) { __libc_itimer_pf_handle_itimer(); }
static inline void unhandle_itimer(void) { __libc_itimer_pf_unhandle_itimer(); }

#endif /* __dj_include_machine_specific_itimer_h_ */

