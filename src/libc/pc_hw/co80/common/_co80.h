#ifndef __dj_include_machine_specific_co80_h_
#define __dj_include_machine_specific_co80_h_

#if 1
# define PLINE {fprintf(stderr, "%s line %u\n", __FILE__, (unsigned)(__LINE__));}
#else
# define PLINE
#endif

/* todo: DBCS_compliant putch, cgets */
/* src/libc/pc_hw/co80/conio.c */

extern unsigned __libc_conio_ScreenAddress;
extern unsigned short __libc_conio_ScreenVirtualSegment;
extern unsigned short __libc_conio_ScreenVirtualOffset;
#if 0
extern unsigned _conio_ScreenAddress;
extern unsigned short _conio_ScreenVirtualSegment;
extern unsigned short _conio_ScreenVirtualOffset;
#endif
extern int __libc_conio_adapter_type;
extern int _wscroll;
extern int directvideo;

int puttext_ibmpc(int c, int r, int c2, int r2, void *buf);
int puttext_nec98(int c, int r, int c2, int r2, void *buf);
int _conio_gettext_ibmpc(int c, int r, int c2, int r2, void *buf);
int _conio_gettext_nec98(int c, int r, int c2, int r2, void *buf);
void textmode_ibmpc(int mode);
void textmode_nec98(int mode);
void _setcursortype_ibmpc(int type);
void _setcursortype_nec98(int type);
void clrscr_ibmpc(void);
void clrscr_nec98(void);
void insline_ibmpc(void);
void insline_nec98(void);
void insline_dv(void);
void delline_ibmpc(void);
void delline_nec98(void);
void delline_dv(void);
int cputs_ibmpc(const char *s);
int cputs_nec98(const char *s);
int cputs_dv(const char *s);
void _set_screen_lines_ibmpc(int nlines);
void _set_screen_lines_nec98(int nlines);
void blinkvideo_ibmpc(void);
void blinkvideo_nec98(void);
void intensevideo_ibmpc(void);
void intensevideo_nec98(void);

void _conio_refreshvirtualscreen_ibmpc(int c, int r, int count);
void _conio_refreshvirtualscreen_nec98(int c, int r, int count);
unsigned __libc_conio_VIDADDR_common(int r, int c);
unsigned __libc_conio_VOFFSET_common(int r, int c);
#if 0
unsigned __libc_conio_VIDADDR_ibmpc(int r, int c);
unsigned __libc_conio_VIDADDR_nec98(int r, int c);
unsigned __libc_conio_VOFFSET_ibmpc(int r, int c);
unsigned __libc_conio_VOFFSET_nec98(int r, int c);
#endif

unsigned __libc_conio_VIDADDR(int r, int c);
unsigned __libc_conio_VOFFSET(int r, int c);

#define VIDADDR(r,c)  __libc_conio_VIDADDR_common(r,c)
#define VOFFSET(r,c)  __libc_conio_VOFFSET_common(r,c)

int __libc_conio_getvideomode(void);

void _conio_bell(void);
void _conio_gettextinfo(struct text_info *t);

int __libc_conio_get_screenattrib(void);
int __libc_conio_get_screenattrib_ibmpc(void);
int __libc_conio_get_screenattrib_nec98(void);


#if 0
/* refreshvirtualscreen */
void UpdateDOSV(int row, int col, int chars);
#endif

/* src/libc/pc_hw/co80/scattrib.c */
#if 1
extern unsigned char _conio_conv_txatbl_ibmpc_to_nec98[]; /* ibmpc to nec98 */
extern unsigned char _conio_conv_txatbl_nec98_to_ibmpc[]; /* nec98 to ibmpc */
# define _conio_attr_ibmpc_to_nec98(a)   (_conio_conv_txatbl_ibmpc_to_nec98[(unsigned char)(a)])
# define _conio_attr_nec98_to_ibmpc(a)   (_conio_conv_txatbl_nec98_to_ibmpc[(unsigned char)(a)])
#else
extern unsigned char conv_98at_txatbl[]; /* at to 98 */
extern unsigned char conv_at98_txatbl[]; /* 98 to at */
#define TXA_98AT(txa)	conv_98at_txatbl[(unsigned char)(txa)] /* at to 98 */
#define TXA_AT98(txa)	conv_at98_txatbl[(unsigned char)(txa)] /* 98 to at */
#endif

/* src/libc/pc_hw/co80/scclear.c */
void ScreenClear_ibmpc(void);
void ScreenClear_nec98(void);
extern void (*__libc_co80_pf_ScreenClear)(void);

/* src/libc/pc_hw/co80/sccols.c */
int ScreenCols_ibmpc(void);
int ScreenCols_nec98(void);
extern int (*__libc_co80_pf_ScreenCols)(void);

/* src/libc/pc_hw/co80/scgetc.c */
void ScreenGetCursor_ibmpc(int *_row, int *_col);
void ScreenGetCursor_nec98(int *_row, int *_col);
extern void (*__libc_co80_pf_ScreenGetCursor)(int *_row, int *_col);

/* src/libc/pc_hw/co80/scgetch.c */
void ScreenGetChar_ibmpc(int *_ch, int *_attr, int _x, int _y);
void ScreenGetChar_nec98(int *_ch, int *_attr, int _x, int _y);
void ScreenGetChar_nec98_raw(int *_ch, int *_attr, int _x, int _y);
extern void (*__libc_co80_pf_ScreenGetChar)(int *_ch, int *_attr, int _x, int _y);

/* src/libc/pc_hw/co80/scmode.c */
int ScreenMode_ibmpc(void);
int ScreenMode_nec98(void);
extern int (*__libc_co80_pf_ScreenMode)(void);

/* src/libc/pc_hw/co80/scputc.c */
void ScreenPutChar_ibmpc(int _ch, int _attr, int _x, int _y);
void ScreenPutChar_nec98(int _ch, int _attr, int _x, int _y);
void ScreenPutChar_nec98_raw(int _ch, int _attr, int _x, int _y);
extern void (*__libc_co80_pf_ScreenPutChar)(int _ch, int _attr, int _x, int _y);

/* src/libc/pc_hw/co80/scputs.c */
void ScreenPutString_ibmpc(const char *_ch, int _attr, int _x, int _y);
void ScreenPutString_nec98(const char *_ch, int _attr, int _x, int _y);
extern void (*__libc_co80_pf_ScreenPutString)(const char *_ch, int _attr, int _x, int _y);

/* src/libc/pc_hw/co80/scretr.c */
void ScreenRetrieve_ibmpc(void *_virtual_screen);
void ScreenRetrieve_nec98(void *_virtual_screen);
extern void (*__libc_co80_pf_ScreenRetrieve)(void *_virtual_screen);

/* src/libc/pc_hw/co80/scrows.c */
int ScreenRows_ibmpc(void);
int ScreenRows_nec98(void);
extern int (*__libc_co80_pf_ScreenRows)(void);

/* src/libc/pc_hw/co80/scsetc.c */
void ScreenSetCursor_ibmpc(int _row, int _col);
void ScreenSetCursor_nec98(int _row, int _col);
extern void (*__libc_co80_pf_ScreenSetCursor)(int _row, int _col);

/* src/libc/pc_hw/co80/scupdate.c */
void ScreenUpdate_ibmpc(const void *_virtual_screen);
void ScreenUpdate_nec98(const void *_virtual_screen);
extern void (*__libc_co80_pf_ScreenUpdate)(const void *_virtual_screen);

/* src/libc/pc_hw/co80/scupdl.c */
void ScreenUpdateLine_ibmpc(const void *_virtual_screen_line, int _row);
void ScreenUpdateLine_nec98(const void *_virtual_screen_line, int _row);
extern void (*__libc_co80_pf_ScreenUpdateLine)(const void *_virtual_screen_line, int _row);

/* src/libc/pc_hw/co80/scvbell.c */
void ScreenVisualBell_ibmpc(void);
void ScreenVisualBell_nec98(void);
extern void (*__libc_co80_pf_ScreenVisualBell)(void);


#if 1
void _conio_bell_dos(void);
void _conio_bell_ibmpc(void);
void _conio_bell_nec98(void);
#endif

#if 1
void __libc_conio_init_sub_ibmpc(void);
void __libc_conio_init_sub_nec98(void);

# define ScreenAddress           __libc_conio_ScreenAddress
# define ScreenVirtualSegment    __libc_conio_ScreenVirtualSegment
# define ScreenVirtualOffset     __libc_conio_ScreenVirtualOffset
extern struct text_info __libc_conio_txinfo;
extern int __libc_conio_ungot_char;
extern int __libc_conio_char_avail;
extern int __libc_conio_adapter_type;
extern int __libc_conio_font_seg;
extern unsigned __libc_conio_last_mode;
extern int __libc_conio_oldattrib;
extern int __libc_conio_intense_bg_mode;
extern int __libc_conio_conio_count;
# define txinfo          __libc_conio_txinfo
# define ungot_char      __libc_conio_ungot_char
# define char_avail      __libc_conio_char_avail
# define adapter_type    __libc_conio_adapter_type
# define font_seg        __libc_conio_font_seg
# define last_mode       __libc_conio_last_mode
# define oldattrib       __libc_conio_oldattrib
# define intense_bg_mode __libc_conio_intense_bg_mode
# define conio_count     __libc_conio_conio_count
#endif

#endif /* !__dj_include_machie_specific_co80_h_ */
