#ifndef __dj_include_machine_specific_kb_h_
#define __dj_include_machine_specific_kb_h_

/* src/libc/pc_hw/kb/getkey.c */
int getkey_ibmpc(void);
int getkey_nec98(void);
int getkey_nec98_raw(void);
extern int (*__libc_kb_pf_getkey)(void);

#if 1
int __libc_kb_conv_scancode_nec98_to_ibmpc(unsigned char, unsigned char);
#else
int conv_at98_pchwkey(unsigned char ah, unsigned char xflag);
#endif

/* src/libc/pc_hw/kb/getxkey.c */
int getxkey_ibmpc(void);
#if 0
int getxkey_nec98(void);
#endif
extern int (*__libc_kb_pf_getxkey)(void);

/* src/libc/pc_hw/kb/kbhit.c */
int kbhit_ibmpc(void);
int kbhit_nec98(void);
extern int (*__libc_kb_pf_kbhit)(void);

int __libc_kb_kbhit_dos(void);

#endif /* !__dj_include_machie_specific_kb_h_ */
