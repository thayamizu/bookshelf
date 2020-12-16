#include "bootpack.h"
#include "descriptors.h"
#include "graphic.h"
#include "my_sprintf.h"
#include "pic.h"
#include "fifo.h"
#include "keyboard.h"
#include "mouse.h"

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
            }
            else if (status_fifo8(&mouseinfo) != 0)
            {
                i = get_fifo8(&mouseinfo);
                io_sti();

                if (decode_mouse(&mouse_desc, i) != 0)
                {
                    my_sprintf(s, "[lcr %d %d]", (int)mouse_desc.x, (int)mouse_desc.y);

                    if ((mouse_desc.btn & 0x01) != 0)
                    {
                        s[1] = 'L';
                    }
                    else if ((mouse_desc.btn & 0x02) != 0)
                    {
                        s[3] = 'R';
                    }
                    else if ((mouse_desc.btn & 0x03) != 0)
                    {
                        s[2] = 'C';
                    }
                    boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 32, 16, 32 + 15 * 8 - 1, 31);
                    putfont8_asc(binfo->vram, binfo->scrnx, 32, 16, COL8_FFFFFF, s);

                    //マウスカーソルの移動
                    boxfill8(binfo->vram, binfo->scrnx, COL8_008484, mx, my, mx + 15, my + 15);
                    mx += mouse_desc.x;
                    if (mx < 0)
                    {
                        mx = 0;
                    }
                    if (mx > binfo->scrnx - 16)
                    {
                        mx = binfo->scrnx - 16;
                    }
                    my += mouse_desc.y;
                    if (my < 0)
                    {
                        my = 0;
                    }
                    if (my > binfo->scrny - 16)
                    {
                        my = binfo->scrny - 16;
                    }
                    my_sprintf(s, "(%d %d)", mx, my);
                    boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 0, 0, 79, 15);
                    putfont8_asc(binfo->vram, binfo->scrnx, 0, 0, COL8_FFFFFF, s);
                    putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);
                }
            }
        }
    }
}
