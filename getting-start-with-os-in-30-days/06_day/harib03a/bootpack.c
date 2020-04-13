#include "bootpack.h"
#include "descriptors.h"
#include "graphic.h"
#include "my_sprintf.h"

void HariMain(void)
{
    BootInfo *binfo = (BootInfo *)0x0ff0;
    static char font_A[16] = {
        0x00, 0x18, 0x18, 0x18, 0x18, 0x24, 0x24, 0x24,
        0x24, 0x7e, 0x42, 0x42, 0x42, 0xe7, 0x00, 0x00};

    char s[1024];
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
