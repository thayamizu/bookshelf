#ifndef MY_SHEET_H_
#define MY_SHEET_H_

#define MAX_SHEETS 256
#define USE_SHEET 1

struct MemoryManager;

typedef struct SHEET
{
    unsigned char *buf;
    struct SHTCTL *sheetctl;
    int bxsize, bysize, vx0, vy0, col_inv, height, flags;
} Sheet;

typedef struct SHTCTL
{
    unsigned char *vram, *map;
    int xsize, ysize, top;
    Sheet *sheets[MAX_SHEETS];
    Sheet sheets0[MAX_SHEETS];
} SheetCtl;

/**
 * @brief SheetCtl初期化
 * 
 * @param meman 
 * @param vram 
 * @param xsize 
 * @param ysize 
 * @return SheetCtl* 
 */
SheetCtl *shtctl_init(MemoryManager *meman, unsigned char *vram, int xsize, int ysize);

/**
 * @brief SheetCtlからSheetを1つ確保する関数
 * 
 * @param sheetCtl 
 * @return Sheet* 
 */
Sheet *sheet_alloc(SheetCtl *sheetCtl);

/**
 * @brief Sheetバッファを設定する
 * 
 * @param sheet 
 * @param buffer 
 * @param xsize 
 * @param ysize 
 * @param col_inv 
 */
Sheet *sheet_setbuf(Sheet *sheet, unsigned char *buffer, int xsize, int ysize, int col_inv);

/**
 * @brief 
 * @param sheet 
 * @param height 
 */
void sheet_updown(Sheet *sheet, int height);

/**
 * @brief Sheetを再描画する
 * @param sheet
 * @param bx0 
 * @param by0 
 * @param bx1 
 * @param by1 
 */
void sheet_refresh(Sheet *sheet, int bx0, int by0, int bx1, int by1);

/**
 * @brief mapを更新する
 * @param sheetCtl 
 * @param vx0 
 * @param vy0 
 * @param vx1 
 * @param vy1 
 * @param h0
 */
void sheet_refreshmap(SheetCtl *sheetCtl, int vx0, int vy0, int vx1, int vy1, int h0);

/**
 * @brief 
 * 
 * @param sheetCtl 
 * @param vx0 
 * @param vy0 
 * @param vx1 
 * @param vy1 
 * @param h0
 */
void sheet_refreshsub(SheetCtl *sheetCtl, int vx0, int vy0, int vx1, int vy1, int h0, int h1);

/**
 * @brief Sheetを移動させる
 * @param sheetCtl 
 * @param sheet 
 * @param vx0 
 * @param vy0 
 */
void sheet_slide(Sheet *sheet, int vx0, int vy0);

/**
 * @brief Sheetを開放します
 * @param ctl 
 * @param sheet 
 */
void sheet_free(Sheet *sheet);
#endif