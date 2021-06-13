#ifndef __dj_include_machine_specific_timer_h_
#define __dj_include_machine_specific_timer_h_

/* src/libc/pc_hw/timer/clock.c */
clock_t clock_ibmpc(void);
clock_t clock_nec98(void);

/* src/libc/pc_hw/timer/uclock.c */
uclock_t uclock_ibmpc(void);
uclock_t uclock_nec98(void);

uclock_t uclock_nec98_pit10ms(void);
uclock_t uclock_nec98_artic(void);
uclock_t uclock_nec98_hitimer(void);


#endif /* !__dj_include_machie_specific_timer_h_ */
