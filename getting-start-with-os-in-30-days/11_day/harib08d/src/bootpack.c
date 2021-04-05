#include "bootpack.h"
#include "descriptors.h"
#include "graphic.h"
#include "sprintf.h"
#include "pic.h"
#include "fifo.h"
#include "keyboard.h"
#include "mouse.h"
#include "memory.h"
#include "sheet.h"

void HariMain(void)
{
    BootInfo *binfo = (BootInfo *)0x00000ff0;
    char s[40], keybuf[32], mousebuf[128];
    int mx, my, i;
    unsigned int mem_total;
    MouseDesc mouse_desc;
    MemoryManager *mem = (MemoryManager *)0x003c0000;
    SheetCtl *sheetCtl;
    Sheet *sheet_back, *sheet_mouse, *sheet_window;
    unsigned char *back_buf, mouse_buf[256], *window_buf;

    init_gdtidt();
    init_pic();
    io_sti();

    init_fifo8(&keyinfo, 32, keybuf);
    init_fifo8(&mouseinfo, 128, mousebuf);
    io_out8(PIC0_IMR, 0xf9);
    io_out8(PIC1_IMR, 0xef);

    init_keyboard();
    enable_mouse(&mouse_desc);

    mem_total = memtest(0x00400000, 0xbfffffff);
    memman_init(mem);
    memman_free(mem, 0x00001000, 0x0009e000);
    memman_free(mem, 0x00400000, mem_total - 0x00400000);

    init_palette();
    sheetCtl = shtctl_init(mem, binfo->vram, binfo->scrnx, binfo->scrny);
    sheet_back = sheet_alloc(sheetCtl);
    sheet_mouse = sheet_alloc(sheetCtl);
    sheet_window = sheet_alloc(sheetCtl);
    back_buf = (unsigned char *)memman_alloc_4k(mem, binfo->scrnx * binfo->scrny);
    window_buf = (unsigned char *)memman_alloc_4k(mem, 160 * 68);
    sheet_setbuf(sheet_back, back_buf, binfo->scrnx, binfo->scrny, COL8_000000);
    sheet_setbuf(sheet_mouse, mouse_buf, 16, 16, 99);
    sheet_setbuf(sheet_window, window_buf, 160, 68, -1);

    init_screen(back_buf, binfo->scrnx, binfo->scrny);
    init_mouse_cursor8(mouse_buf, 99);
    make_window8(window_buf, 160, 68, "Window");
    putfont8_asc(window_buf, 160, 24, 28, COL8_000000, "Welcome to");
    putfont8_asc(window_buf, 160, 24, 44, COL8_000000, "Haribote-OS!");

    sheet_slide(sheet_back, 0, 0);
    mx = (binfo->scrnx - 16) / 2;
    my = (binfo->scrny - 28 - 16) / 2;
    sheet_slide(sheet_mouse, mx, my);
    sheet_slide(sheet_window, 80, 72);
    sheet_updown(sheet_back, 0);
    sheet_updown(sheet_window, 1);
    sheet_updown(sheet_mouse, 2);

    sprintf(s, "(%d, %d)", mx, my);
    putfont8_asc(back_buf, binfo->scrnx, 0, 0, COL8_FFFFFF, s);

    sprintf(s, "memory:%dMB free:%dKB", mem_total / (1024 * 1024), memman_total(mem) / 1024);
    putfont8_asc(back_buf, binfo->scrnx, 0, 32, COL8_FFFFFF, s);
    sheet_refresh(sheet_back, 0, 0, binfo->scrnx, 48);
    sheet_refresh(sheet_window, 0, 0, 160, 68);

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
                sprintf(s, "%x", i);
                boxfill8(back_buf, binfo->scrnx, COL8_008484, 0, 16, 15, 31);
                putfont8_asc(back_buf, binfo->scrnx, 0, 16, COL8_FFFFFF, s);
                sheet_refresh(sheet_back, 0, 16, 16, 32);
            }
            else if (status_fifo8(&mouseinfo) != 0)
            {
                i = get_fifo8(&mouseinfo);
                io_sti();

                if (decode_mouse(&mouse_desc, i) != 0)
                {
                    sprintf(s, "[lcr %d %d]", (int)mouse_desc.x, (int)mouse_desc.y);

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
                    boxfill8(back_buf, binfo->scrnx, COL8_008484, 32, 16, 32 + 15 * 8 - 1, 31);
                    putfont8_asc(back_buf, binfo->scrnx, 32, 16, COL8_FFFFFF, s);
                    sheet_refresh(sheet_back, 32, 16, 32 * 15 * 8, 32);

                    //マウスカーソルの移動
                    mx += mouse_desc.x;
                    if (mx < 0)
                    {
                        mx = 0;
                    }
                    if (mx > binfo->scrnx - 1)
                    {
                        mx = binfo->scrnx - 1;
                    }
                    my += mouse_desc.y;
                    if (my < 0)
                    {
                        my = 0;
                    }
                    if (my > binfo->scrny - 1)
                    {
                        my = binfo->scrny - 1;
                    }
                    sprintf(s, "(%d %d)", mx, my);
                    boxfill8(back_buf, binfo->scrnx, COL8_008484, 0, 0, 79, 15);
                    putfont8_asc(back_buf, binfo->scrnx, 0, 0, COL8_FFFFFF, s);
                    sheet_refresh(sheet_back, 0, 0, 80, 16);
                    sheet_slide(sheet_mouse, mx, my);
                }
            }
        }
    }
}

//----
//
unsigned int memtest(unsigned int start, unsigned int end)
{
    char flag486 = 0;
    unsigned int eflag, i, cr0;

    eflag = io_load_eflags();
    eflag |= EFLAGS_AC_BIT;

    io_store_eflags(eflag);
    eflag = io_load_eflags();

    if ((eflag & EFLAGS_AC_BIT) != 0)
    {
        flag486 = 1;
    }

    eflag &= ~EFLAGS_AC_BIT;
    io_store_eflags(eflag);
    if (flag486 != 0)
    {
        cr0 = load_cr0();
        cr0 |= CR0_CACHE_DISABLE;
        store_cr0(cr0);
    }

    i = memtest_sub(start, end);
    if (flag486 != 0)
    {
        cr0 = load_cr0();
        cr0 &= ~CR0_CACHE_DISABLE;
        store_cr0(cr0);
    }

    return i;
}

//----
//
void make_window8(unsigned char *buf, int xsize, int ysize, char *title)
{
    static char closebtn[14][16] = {
        "OOOOOOOOOOOOOOO@",
        "OQQQQQQQQQQQQQ$@",
        "OQQQQQQQQQQQQQ$@",
        "OQQQ@@QQQQ@@QQ$@",
        "OQQQQ@@QQ@@QQQ$@",
        "OQQQQQ@@@@QQQQ$@",
        "OQQQQQQ@@QQQQQ$@",
        "OQQQQQ@@@@QQQQ$@",
        "OQQQQ@@QQ@@QQQ$@",
        "OQQQ@@QQQQ@@QQ$@",
        "OQQQQQQQQQQQQQ$@",
        "OQQQQQQQQQQQQQ$@",
        "O$$$$$$$$$$$$$$@",
        "@@@@@@@@@@@@@@@@"};
    int x, y;
    char c;
    boxfill8(buf, xsize, COL8_C6C6C6, 0, 0, xsize - 1, 0);
    boxfill8(buf, xsize, COL8_FFFFFF, 1, 1, xsize - 2, 1);
    boxfill8(buf, xsize, COL8_C6C6C6, 0, 0, 0, ysize - 1);
    boxfill8(buf, xsize, COL8_FFFFFF, 1, 1, 1, ysize - 2);
    boxfill8(buf, xsize, COL8_848484, xsize - 2, 1, xsize - 2, ysize - 2);
    boxfill8(buf, xsize, COL8_000000, xsize - 1, 0, xsize - 1, ysize - 1);
    boxfill8(buf, xsize, COL8_C6C6C6, 2, 2, xsize - 3, ysize - 3);
    boxfill8(buf, xsize, COL8_000084, 3, 3, xsize - 4, 20);
    boxfill8(buf, xsize, COL8_848484, 1, ysize - 2, xsize - 2, ysize - 2);
    boxfill8(buf, xsize, COL8_000000, 0, ysize - 1, xsize - 1, ysize - 1);
    putfont8_asc(buf, xsize, 24, 4, COL8_FFFFFF, title);
    for (y = 0; y < 14; y++)
    {
        for (x = 0; x < 16; x++)
        {
            c = closebtn[y][x];
            if (c == '@')
            {
                c = COL8_000000;
            }
            else if (c == '$')
            {
                c = COL8_848484;
            }
            else if (c == 'Q')
            {
                c = COL8_C6C6C6;
            }
            else
            {
                c = COL8_FFFFFF;
            }
            buf[(5 + y) * xsize + (xsize - 21 + x)] = c;
        }
    }
    return;
}