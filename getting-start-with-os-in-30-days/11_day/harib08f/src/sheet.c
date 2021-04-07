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
        ctl->sheets0[i].sheetctl = ctl;
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
void sheet_updown(Sheet *sheet, int height)
{
    int h, old = sheet->height;

    //入力値の補正
    if (height > sheet->sheetctl->top + 1)
    {
        height = sheet->sheetctl->top + 1;
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
                sheet->sheetctl->sheets[h] = sheet->sheetctl->sheets[h - 1];
                sheet->sheetctl->sheets[h]->height = h;
            }
            sheet->sheetctl->sheets[height] = sheet;
        }
        else
        {
            if (sheet->sheetctl->top > old)
            {
                for (h = old; h < sheet->sheetctl->top; h++)
                {
                    sheet->sheetctl->sheets[h] = sheet->sheetctl->sheets[h + 1];
                    sheet->sheetctl->sheets[h]->height = h;
                }
            }
            sheet->sheetctl->top--;
        }
        sheet_refreshsub(sheet->sheetctl, sheet->vx0, sheet->vy0, sheet->vx0 + sheet->bxsize, sheet->vy0 + sheet->bysize);
    }
    else if (old < height)
    {
        if (old >= 0)
        {
            for (h = old; h < height; h++)
            {
                sheet->sheetctl->sheets[h] = sheet->sheetctl->sheets[h + 1];
                sheet->sheetctl->sheets[h]->height = h;
            }
            sheet->sheetctl->sheets[height] = sheet;
        }
        else
        {
            for (h = sheet->sheetctl->top; h >= height; h--)
            {
                sheet->sheetctl->sheets[h + 1] = sheet->sheetctl->sheets[h];
                sheet->sheetctl->sheets[h + 1]->height = h + 1;
            }
            sheet->sheetctl->sheets[height] = sheet;
            sheet->sheetctl->top++;
        }

        sheet_refreshsub(sheet->sheetctl, sheet->vx0, sheet->vy0, sheet->vx0 + sheet->bxsize, sheet->vy0 + sheet->bysize);
    }

    return;
}

//----
//
void sheet_refresh(Sheet *sheet, int bx0, int by0, int bx1, int by1)
{
    if (sheet->height >= 0)
    {
        sheet_refreshsub(sheet->sheetctl, sheet->vx0 + bx0, sheet->vy0 + by0, sheet->vx0 + bx1, sheet->vy0 + by1);
    }
    return;
}

//----
//
void sheet_refreshsub(SheetCtl *sheetCtl, int vx0, int vy0, int vx1, int vy1)
{
    int h, bx, by, vx, vy;
    int bx0, by0, bx1, by1;
    unsigned char *buffer, c, *vram = sheetCtl->vram;
    if (vx0 < 0)
    {
        vx0 = 0;
    }
    if (vy0 < 0)
    {
        vy = 0;
    }
    if (vx1 > sheetCtl->xsize)
    {
        vx1 = sheetCtl->xsize;
    }
    if (vy1 > sheetCtl->ysize)
    {
        vy1 = sheetCtl->ysize;
    }
    Sheet *sheet = 0;
    for (h = 0; h <= sheetCtl->top; h++)
    {
        sheet = sheetCtl->sheets[h];
        buffer = sheet->buf;
        bx0 = vx0 - sheet->vx0;
        by0 = vy0 - sheet->vy0;
        bx1 = vx1 - sheet->vx0;
        by1 = vy1 - sheet->vy0;
        if (bx0 < 0)
        {
            bx0 = 0;
        }
        if (by0 < 0)
        {
            by0 = 0;
        }
        if (bx1 > sheet->bxsize)
        {
            bx1 = sheet->bxsize;
        }
        if (by1 > sheet->bysize)
        {
            by1 = sheet->bysize;
        }
        for (by = by0; by < by1; by++)
        {
            vy = sheet->vy0 + by;
            for (bx = bx0; bx < bx1; bx++)
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
void sheet_slide(Sheet *sheet, int vx0, int vy0)
{
    int old_vx0 = sheet->vx0, old_vy0 = sheet->vy0;
    sheet->vx0 = vx0;
    sheet->vy0 = vy0;
    if (sheet->height >= 0)
    {
        sheet_refreshsub(sheet->sheetctl, old_vx0, old_vy0, old_vx0 + sheet->bxsize, old_vy0 + sheet->bysize);
        sheet_refreshsub(sheet->sheetctl, vx0, vy0, vx0 + sheet->bxsize, vy0 + sheet->bysize);
    }

    return;
}

//----
//
void sheet_free(Sheet *sheet)
{
    if (sheet->height >= 0)
    {
        sheet_updown(sheet, -1);
    }

    sheet->flags = 0;
    return;
}