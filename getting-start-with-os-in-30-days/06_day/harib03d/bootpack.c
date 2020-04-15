#include "bootpack.h"
#include "descriptors.h"
#include "graphic.h"
#include "my_sprintf.h"
#include "pic.h"

void HariMain(void)
{
    BootInfo *binfo = (BootInfo *)0x0ff0;

    init_gdtidt();
    init_pic();

    init_palette();
    init_screen(binfo->vram, binfo->scrnx, binfo->scrny);

    char *mouse = 0;
    int mx = 32, my = 32;
    init_mouse_cursor8(mouse, COL8_008484);
    putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mouse, 16);
    for (;;)
    {
        io_hlt();
    }

    return;
}
