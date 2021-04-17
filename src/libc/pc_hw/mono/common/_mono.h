#ifndef __dj_include_machine_specific_mono_h_
#define __dj_include_machine_specific_mono_h_

/* src/libc/pc_hw/mono/mono.c */

void _mono_clear_ibmpc(void);
void _mono_clear_nec98(void);
extern void (*__libc_mono_pf__mono_clear)(void);
void _mono_putc_ibmpc(int c);
void _mono_putc_nec98(int c);
extern void (*__libc_mono_pf__mono_putc)(int c);

extern int __libc_mono_screen_is_initted;
extern int __libc_mono_screen_ofs;

#endif /* !__dj_include_machie_specific_mono_h_ */
