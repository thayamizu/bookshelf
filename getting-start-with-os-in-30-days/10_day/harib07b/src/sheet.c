#include "memory.h"
#include "sheet.h"

//----
//
SheetCtl *shtctl_init(MemoryManager *memman, unsigned char *vram, int xsize, int ysize)
{
    SheetCtl *ctl;

    int i;
    ctl = (SheetCtl *)memman_alloc_4k(memman, sizeof(SheetCtl));
    if (ctl == 0)
    {
        goto ERR;
    }

    ctl->vram = vram;
    ctl->xsize = xsize;
    ctl->ysize = ysize;

    ctl->top = -1;
    for (i = 0; i < MAX_SHEETS; i++)
    {
        ctl->sheets0[i].flags = 0;
    }

ERR:
    return ctl;
}

//----
//
Sheet *sheet_alloc(SheetCtl *sheetCtl)
{
    Sheet *sheet = 0;
    int i;
    for (i = 0; i < MAX_SHEETS; i++)
    {
        if (sheetCtl->sheets0[i].flags == 0)
        {
            sheet = &sheetCtl->sheets0[i];
            sheet->flags = USE_SHEET;
            sheet->height = -1;
            break;
        }
    }

    return sheet;
}

//----
//
Sheet *sheet_setbuf(Sheet *sheet, unsigned char *buffer, int xsize, int ysize, int col_inv)
{
    sheet->buf = buffer;
    sheet->bxsize = xsize;
    sheet->bysize = ysize;
    sheet->col_inv = col_inv;
    return sheet;
}

//----
//
void sheet_updown(SheetCtl *sheetCtl, Sheet *sheet, int height)
{
    int h, old = sheet->height;

    //入力値の補正
    if (height > sheetCtl->top + 1)
    {
        height = sheetCtl->top + 1;
    }
    if (height < -1)
    {
        height = -1;
    }

    sheet->height = height;
    //sheetsの並べ替え
    if (old > height)
    {
        if (height >= 0)
        {
            for (h = old; h > height; h--)
            {
                sheetCtl->sheets[h] = sheetCtl->sheets[h - 1];
                sheetCtl->sheets[h]->height = h;
            }
            sheetCtl->sheets[height] = sheet;
        }
        else
        {
            if (sheetCtl->top > old)
            {
                for (h = old; h < sheetCtl->top; h++)
                {
                    sheetCtl->sheets[h] = sheetCtl->sheets[h + 1];
                    sheetCtl->sheets[h]->height = h;
                }
            }
            sheetCtl->top--;
        }
        sheet_refresh(sheetCtl);
    }
    else if (old < height)
    {
        if (old >= 0)
        {
            for (h = old; h < height; h++)
            {
                sheetCtl->sheets[h] = sheetCtl->sheets[h + 1];
                sheetCtl->sheets[h]->height = h;
            }
            sheetCtl->sheets[height] = sheet;
        }
        else
        {
            for (h = sheetCtl->top; h >= height; h--)
            {
                sheetCtl->sheets[h + 1] = sheetCtl->sheets[h];
                sheetCtl->sheets[h + 1]->height = h + 1;
            }
            sheetCtl->sheets[height] = sheet;
            sheetCtl->top++;
        }

        sheet_refresh(sheetCtl);
    }

    return;
}

//----
//
void sheet_refresh(SheetCtl *sheetCtl)
{
    int h, bx, by, vx, vy;
    unsigned char *buffer, c, *vram = sheetCtl->vram;

    Sheet *sheet = 0;
    for (h = 0; h <= sheetCtl->top; h++)
    {
        sheet = sheetCtl->sheets[h];
        buffer = sheet->buf;
        for (by = 0; by < sheet->bysize; by++)
        {
            vy = sheet->vy0 + by;
            for (bx = 0; bx < sheet->bxsize; bx++)
            {
                vx = sheet->vx0 + bx;
                c = buffer[by * sheet->bxsize + bx];
                if (c != sheet->col_inv)
                {
                    vram[vy * sheetCtl->xsize + vx] = c;
                }
            }
        }
    }
    return;
}

//----
//
void sheet_slide(SheetCtl *sheetCtl, Sheet *sheet, int vx0, int vy0)
{
    sheet->vx0 = vx0;
    sheet->vy0 = vy0;
    if (sheet->height >= 0)
    {
        sheet_refresh(sheetCtl);
    }

    return;
}

//----
//
void sheet_free(SheetCtl *ctl, Sheet *sheet)
{
    if (sheet->height >= 0)
    {
        sheet_updown(ctl, sheet, -1);
    }

    sheet->flags = 0;
    return;
}