#include "bootpack.h"
#include "pic.h"
#include "graphic.h"
#include "fifo.h"

KeyBuf keyinfo;
MouseBuf mouseinfo;

//-----------------------------------------------------------------------------
//
void init_pic(void)
{
    io_out8(PIC0_IMR, 0xff); /* 全ての割り込みを受け付けない */
    io_out8(PIC1_IMR, 0xff); /* 全ての割り込みを受け付けない */

    io_out8(PIC0_ICW1, 0x11);   /* エッジトリガモード */
    io_out8(PIC0_ICW2, 0x20);   /* IRQ0-7は、INT20-27で受ける */
    io_out8(PIC0_ICW3, 1 << 2); /* PIC1はIRQ2にて接続 */
    io_out8(PIC0_ICW4, 0x01);   /* ノンバッファモード */

    io_out8(PIC1_ICW1, 0x11); /* エッジトリガモード */
    io_out8(PIC1_ICW2, 0x28); /* IRQ8-15は、INT28-2fで受ける */
    io_out8(PIC1_ICW3, 2);    /* PIC1はIRQ2にて接続 */
    io_out8(PIC1_ICW4, 0x01); /* ノンバッファモード */

    io_out8(PIC0_IMR, 0xfb); /* 11111011 PIC1以外は全て禁止 */
    io_out8(PIC1_IMR, 0xff); /* 11111111 全ての割り込みを受け付けない */
    return;
}

void inthandler20(int *esp)
{
    io_out8(PIC0_OCW2, 0x60);
    return;
}

void inthandler21(int *esp)
{
    unsigned char data;
    io_out8(PIC0_OCW2, 0x61);
    data = io_in8(PORT_KEYDAT);

    put_fifo8(&keyinfo, data);

    return;
}

void inthandler2c(int *esp)
{
    unsigned char data;
    io_out8(PIC0_OCW2, 0x64);
    io_out8(PIC0_OCW2, 0x62);
    data = io_in8(PORT_KEYDAT);

    put_fifo8(&mouseinfo, data);

    return;
}

void inthandler27(int *esp)
{
    io_out8(PIC0_OCW2, 0x67);
    return;
}