#ifndef __dj_include_machine_specific_termios_h_
#define __dj_include_machine_specific_termios_h_

/*
include/libc/ttyprvt.h
(src/libc/posix/termios/tminit.c)

extern struct tty __libc_tty_internal;
extern struct tty *__libc_tty_p;
extern int __libc_termios_hook_common_count;
*/

/* src/libc/posix/termios/tcflush.c */
/* void __libc_termios_flush_keybuf(void); */
void (*__libc_termios_pf_flush_keybuf)(void);
void __libc_termios_flush_keybuf_dos(void);
void __libc_termios_flush_keybuf_ibmpc(void);


/* src/libc/posix/termios/tmread.c */
void __libc_termios_init_read_ibmpc(void);
void __libc_termios_init_read_nec98(void);

int __libc_termios_direct_keysense(void);
int (*__libc_pf_termios_direct_keysense)(void);
int __libc_termios_direct_keysense_ibmpc(void);
int __libc_termios_direct_keysense_nec98(void);

unsigned char __libc_termios_direct_keyinput(void);
unsigned char (*__libc_pf_termios_direct_keyinput)(void);
unsigned char __libc_termios_direct_keyinput_nec98(void);
unsigned char __libc_termios_direct_keyinput_ibmpc(void);

#define SENSE_NO_KEY    0
#define SENSE_REG_KEY   1
#define SENSE_EXT_KEY   2

#define _KEY_INS  0x80
#define _KEY_CAPS 0x40
#define _KEY_NUM  0x20
#define _KEY_SCRL 0x10
#define _KEY_ALT  0x08
#define _KEY_CTRL 0x04
#define _KEY_LSFT 0x02
#define _KEY_RSFT 0x01

int __libc_termios_direct_ctrlsense(void);
int (*__libc_pf_termios_direct_ctrlsense)(void);
int __libc_termios_direct_ctrlsense_ibmpc(void);
int __libc_termios_direct_ctrlsense_nec98(void);


/* src/libc/posix/termios/tmwrite.c */
void __libc_termios_init_write_ibmpc(void);
void __libc_termios_init_write_nec98(void);

void __libc_termios_get_cursor(int *col, int *row);
void (*__libc_pf_termios_get_cursor)(int *col, int *row);
void __libc_termios_get_cursor_ibmpc(int *col, int *row);
void __libc_termios_get_cursor_nec98(int *col, int *row);

void __libc_termios_set_cursor(int col, int row);
void (*__libc_pf_termios_set_cursor)(int col, int row);
void __libc_termios_set_cursor_ibmpc(int col, int row);
void __libc_termios_set_cursor_nec98(int col, int row);

void __libc_termios_move_cursor(int x_delta, int y_delta);
void (*__libc_pf_termios_move_cursor)(int x_delta, int y_delta);
void __libc_termios_move_cursor_ibmpc(int x_delta, int y_delta);
void __libc_termios_move_cursor_nec98(int x_delta, int y_delta);

void __libc_termios_set_cursor_shape(int shape);
void (*__libc_termios_pf_set_cursor_shape)(int shape);
void __libc_termios_set_cursor_shape_ibmpc(int shape);
void __libc_termios_set_cursor_shape_nec98(int shape);

void __libc_termios_set_blink_attrib(int enable_blink);
void (*__libc_termios_pf_set_blink_attrib)(int enable_blink);
void __libc_termios_set_blink_attrib_ibmpc(int enable_blink);
void __libc_termios_set_blink_attrib_nec98(int enable_blink);

void __libc_termios_restore_video_state(void);
void (*__libc_termios_pf_restore_video_state)(void);
void __libc_termios_restore_video_state_ibmpc(void);
void __libc_termios_restore_video_state_nec98(void);



#endif /* !__dj_include_machie_specific_termios_h_ */
