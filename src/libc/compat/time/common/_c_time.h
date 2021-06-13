#ifndef __dj_include_machine_specific_compat_time_h_
#define __dj_include_machine_specific_compat_time_h_

unsigned long rawclock_ibmpc(void);
unsigned long rawclock_nec98_hitimer(void);
unsigned long rawclock_nec98_hitimer_raw(void);
unsigned long rawclock_nec98_fallback(void);

#endif /* __dj_include_machine_specific_compat_time_h_ */

