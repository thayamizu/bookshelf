#define COL8_000000 0
#define COL8_FF0000 1
#define COL8_00FF00 2
#define COL8_FFFF00 3
#define COL8_0000FF 4
#define COL8_FF00FF 5
#define COL8_00FFFF 6
#define COL8_FFFFFF 7
#define COL8_C6C6C6 8
#define COL8_840000 9
#define COL8_008400 10
#define COL8_848400 11
#define COL8_000084 12
#define COL8_840084 13
#define COL8_008484 14
#define COL8_848484 15

void io_hlt(void);
void io_cli(void);
void io_out8(int port, int data);
int io_load_eflags(void);
void io_store_eflags(int eflags);

void init_palette(void);
void set_palette(int start, int end, unsigned char *rgb);

void boxfill(char *vram, int xsize, unsigned char, int x0, int y0, int x1, int y1);

typedef struct _BootInfo
{
    char cyls, leds, vmode, reserve;
    short scrnx, scrny;
    char *vram;
} BootInfo;

void HariMain(void)
{
    int xsize, ysize;
    char *vram;
    BootInfo *binfo = (BootInfo *)0x0ff0;

    init_palette();
    xsize = binfo->scrnx;
    ysize = binfo->scrny;
    vram = binfo->vram;

    boxfill(vram, xsize, COL8_008484, 0, 0, xsize - 1, ysize - 29);
    boxfill(vram, xsize, COL8_C6C6C6, 0, ysize - 28, xsize - 1, ysize - 28);
    boxfill(vram, xsize, COL8_FFFFFF, 0, ysize - 27, xsize - 1, ysize - 27);
    boxfill(vram, xsize, COL8_C6C6C6, 0, ysize - 26, xsize - 1, ysize - 1);

    boxfill(vram, xsize, COL8_FFFFFF, 3, ysize - 24, 59, ysize - 24);
    boxfill(vram, xsize, COL8_FFFFFF, 2, ysize - 24, 2, ysize - 4);
    boxfill(vram, xsize, COL8_848484, 3, ysize - 4, 59, ysize - 4);
    boxfill(vram, xsize, COL8_848484, 59, ysize - 23, 59, ysize - 5);
    boxfill(vram, xsize, COL8_000000, 2, ysize - 3, 59, ysize - 3);
    boxfill(vram, xsize, COL8_000000, 60, ysize - 24, 60, ysize - 3);

    boxfill(vram, xsize, COL8_848484, xsize - 47, ysize - 24, xsize - 4, ysize - 24);
    boxfill(vram, xsize, COL8_848484, xsize - 47, ysize - 23, xsize - 47, ysize - 4);
    boxfill(vram, xsize, COL8_FFFFFF, xsize - 47, ysize - 3, xsize - 4, ysize - 3);
    boxfill(vram, xsize, COL8_FFFFFF, xsize - 47, ysize - 24, xsize - 3, ysize - 3);

    for (;;)
    {
        io_hlt();
    }
}

void init_palette()
{
    static unsigned char table_rgb[16 * 3] = {
        0x00, 0x00, 0x00,
        0xff, 0x00, 0x00,
        0x00, 0xff, 0x00,
        0xff, 0xff, 0x00,
        0x00, 0x00, 0xff,
        0xff, 0x00, 0xff,
        0x00, 0xff, 0xff,
        0xff, 0xff, 0xff,
        0xc6, 0xc6, 0xc6,
        0x84, 0x00, 0x00,
        0x84, 0x84, 0x00,
        0x00, 0x00, 0x84,
        0x84, 0x00, 0x84,
        0x00, 0x84, 0x84,
        0x00, 0x84, 0x84};

    set_palette(0, 15, table_rgb);
    return;
}

void set_palette(int start, int end, unsigned char *rgb)
{
    int i, eflags;
    eflags = io_load_eflags();
    io_cli();
    io_out8(0x03c8, start);
    for (i = start; i <= end; i++)
    {
        io_out8(0x03c9, rgb[0] / 4);
        io_out8(0x03c9, rgb[1] / 4);
        io_out8(0x03c9, rgb[2] / 4);
        rgb += 3;
    }

    io_store_eflags(eflags);
    return;
}

void boxfill(char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1)
{

    int x, y;
    for (y = y0; y <= y1; y++)
    {
        for (x = x0; x <= x1; x++)
        {
            vram[y * xsize + x] = c;
        }
    }
    return;
}