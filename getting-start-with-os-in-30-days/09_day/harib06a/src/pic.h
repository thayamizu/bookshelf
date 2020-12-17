#ifndef MY_PIC_H_
#define MY_PIC_H_

#include "fifo.h"
/**
 * 定数
 */
#define PIC0_ICW1 0x0020
#define PIC0_OCW2 0x0020
#define PIC0_IMR 0x0021
#define PIC0_ICW2 0x0021
#define PIC0_ICW3 0x0021
#define PIC0_ICW4 0x0021
#define PIC1_ICW1 0x00a0
#define PIC1_OCW2 0x00a0
#define PIC1_IMR 0x00a1
#define PIC1_ICW2 0x00a1
#define PIC1_ICW3 0x00a1
#define PIC1_ICW4 0x00a
#define PORT_KEYDAT 0x0060

/**
 * キーバッファ構造体
 */
typedef FIFO8 KeyBuf;
typedef FIFO8 MouseBuf;

KeyBuf keyinfo;
MouseBuf mouseinfo;

/**
 * PICを初期化します。
 */
void init_pic(void);

void inthandler21(int *esp);

void inthandler27(int *esp);

void inthandler2c(int *esp);

extern void asm_inthandler21(void);
extern void asm_inthandler27(void);
extern void asm_inthandler2c(void);

#endif