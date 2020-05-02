#ifndef MY_BOOTPACK_H_
#define MY_BOOTPACK_H_

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