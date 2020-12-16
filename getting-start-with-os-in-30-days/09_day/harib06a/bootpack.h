#ifndef MY_BOOTPACK_H_
#define MY_BOOTPACK_H_

#define PORT_KEYDAT 0x0060
#define PORT_KEYSTA 0x0064
#define PORT_KEYCMD 0x0064
#define KEYSTA_SEND_NOTREADY 0x02
#define KEYCMD_WRITE_MODE 0x60
#define KBC_MODE 0x47
#define KEYCMD_SENDTO_MOUSE 0xd4
#define MOUSECMD_ENABLE 0xf4

#define MOUSE_PHASE 3

/**
 * BootInfo構造体
 */
typedef struct _BootInfo
{
    char cyls, leds, vmode, reserve;
    short scrnx, scrny;
    char *vram;
} BootInfo;

/**
 * ハルトします
 * @return void
 */
extern void io_hlt(void);

extern void io_sti(void);

/**
 * CLI 
 * @return void
 */
extern void io_cli(void);

/**
 * STIHLT
 *  @return void
 */
extern void io_stihlt(void);

/**
 * 
 * @return void
 */
extern void io_out8(int port, int data);

/**
 * eflagsを取得します
 * @return int
 */
extern int io_load_eflags(void);

/**
 * eflagsを保存します
 * @return void
 */
extern void io_store_eflags(int eflags);

/**
 * 
 * @return int
 */
extern int io_in8(char port);

#endif