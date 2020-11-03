#include "bootpack.h"
#include "descriptors.h"
#include "graphic.h"
#include "my_sprintf.h"
#include "pic.h"
#include "fifo.h"

#define PORT_KEYDAT 0x0060
#define PORT_KEYSTA 0x0064
#define PORT_KEYCMD 0x0064
#define KEYSTA_SEND_NOTREADY 0x02
#define KEYCMD_WRITE_MODE 0x60
#define KBC_MODE 0x47
#define KEYCMD_SENDTO_MOUSE 0xd4
#define MOUSECMD_ENABLE 0xf4

void wait_KBC_sendready(void)
{
    for (;;)
    {
        if ((io_in8(PORT_KEYSTA) & KEYSTA_SEND_NOTREADY) == 0)
        {
            break;
        }
    }
    return;
}

void init_keyboard(void)
{
    wait_KBC_sendready();
    io_out8(PORT_KEYCMD, KEYCMD_WRITE_MODE);

    wait_KBC_sendready();
    io_out8(PORT_KEYDAT, KBC_MODE);

    return;
}

#define MOUSE_PHASE 3
typedef struct _Mouse_DEC
{
    unsigned char buf[MOUSE_PHASE], phase;
} MouseDesc;

void init_mouse(MouseDesc *desc)
{
    desc->buf[0] = 0;
    desc->buf[1] = 0;
    desc->buf[2] = 0;
    desc->phase = 0;
}

void enable_mouse(MouseDesc *desc)
{
    wait_KBC_sendready();
    io_out8(PORT_KEYCMD, KEYCMD_SENDTO_MOUSE);

    wait_KBC_sendready();
    io_out8(PORT_KEYDAT, MOUSECMD_ENABLE);

    init_mouse(desc);

    return;
}

int decode_mouse(MouseDesc *desc, unsigned char data)
{
    int result = 0;
    if (desc->phase == 0)
    {
        if (data == 0xfa)
        {
            desc->phase = 1;
        }
    }
    else if (desc->phase == 1)
    {
        desc->buf[0] = data;
        desc->phase++;
    }
    else if (desc->phase == 2)
    {
        desc->buf[1] = data;
        desc->phase++;
    }
    else if (desc->phase == 3)
    {
        desc->buf[2] = data;
        desc->phase = 1;
        result = 1;
    }

    return result;
}

void HariMain(void)
{

    BootInfo *binfo = (BootInfo *)0x00000ff0;
    char s[40], mcursor[256], keybuf[32], mousebuf[128];
    int mx, my, i;
    MouseDesc mouse_desc;
    init_gdtidt();
    init_pic();
    io_sti();

    init_fifo8(&keyinfo, 32, keybuf);
    init_fifo8(&mouseinfo, 128, mousebuf);
    io_out8(PIC0_IMR, 0xf9);
    io_out8(PIC1_IMR, 0xef);

    init_keyboard();
    init_mouse(&mouse_desc);
    init_palette();
    init_screen(binfo->vram, binfo->scrnx, binfo->scrny);
    mx = (binfo->scrnx - 16) / 2;
    my = (binfo->scrny - 28 - 16) / 2;
    init_mouse_cursor8(mcursor, COL8_008484);
    putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);
    my_sprintf(s, "(%d, %d)", mx, my);
    putfont8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s);

    enable_mouse(&mouse_desc);
    for (;;)
    {
        io_cli();
        if (status_fifo8(&mouseinfo) + status_fifo8(&keyinfo) == 0)
        {
            io_stihlt();
        }
        else
        {
            if (status_fifo8(&keyinfo) != 0)
            {
                i = get_fifo8(&keyinfo);
                io_sti();

                //my_sprintf(s, "%x", i);
                //boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 0, 16, 15, 31);
                //putfont8_asc(binfo->vram, binfo->scrnx, 0, 16, COL8_FFFFFF, s);
            }
            else if (status_fifo8(&mouseinfo) != 0)
            {
                i = get_fifo8(&mouseinfo);
                io_sti();

                if (decode_mouse(&mouse_desc, i) != 0)
                {
                    my_sprintf(s, "%x %x %x", mouse_desc.buf[0], mouse_desc.buf[1], mouse_desc.buf[2]);
                    boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 32, 16, 32 + 8 * 8 - 1, 31);
                    putfont8_asc(binfo->vram, binfo->scrnx, 32, 16, COL8_FFFFFF, s);
                }
            }
        }
    }
}
