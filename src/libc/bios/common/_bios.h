#ifndef __dj_include_machine_specific_bios_h_
#define __dj_include_machine_specific_bios_h_

/* src/libc/bios/b_time.c */
unsigned _bios_timeofday_ibmpc(unsigned _cmd, unsigned long *_timeval);
unsigned _bios_timeofday_nec98(unsigned _cmd, unsigned long *_timeval);

/* src/libc/bios/biostime.c */
long biostime_ibmpc(int _cmd, long _newtime);
long biostime_nec98(int _cmd, long _newtime);

/* src/libc/bios/bioscom.c */
int bioscom_ibmpc(int cmd, char data, int port);
int bioscom_nec98(int cmd, char data, int port);
#if 0
unsigned char conv_98at_com_mode(int data);
int conv_at98_com_status(int cx);
#endif

/* src/libc/bios/biosdisk.c */
int biosdisk_ibmpc(int _cmd, int _drive, int _head, int _track, int _sector, int _nsects, void *_buffer);
int biosdisk_nec98(int _cmd, int _drive, int _head, int _track, int _sector, int _nsects, void *_buffer);
unsigned _bios_disk_ibmpc(unsigned _cmd, struct _diskinfo_t *_di);
unsigned _bios_disk_nec98(unsigned _cmd, struct _diskinfo_t *_di);

#if 0
int _bios_disk_hd_sector_base(void);
#endif

/* src/libc/bios/biosequi.c */
int biosequip_ibmpc(void);
int biosequip_nec98(void);

/* src/libc/bios/biosmem.c */
int biosmemory_ibmpc(void);
int biosmemory_nec98(void);

/* src/libc/bios/bioskey.c */
int bioskey_ibmpc(int cmd);
int bioskey_nec98(int cmd);
#if 1
int bioskey_nec98_noconv(int cmd);
#endif
#if 0
int conv_at98_bioskey(unsigned char ah);
#endif

/* src/libc/bios/biosprin.c */
int biosprint_ibmpc(int _cmd, int _byte, int _port);
int biosprint_nec98(int _cmd, int _byte, int _port);


#endif /* !__dj_include_machie_specific_bios_h_ */
