#ifndef MY_GRAPHIC_H_
#define MY_GRAPHIC_H_

/**
 * カラーパレット定数
 */
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

/**
 * 埋め込みフォントデータのエントリ
 */
extern char _binary_build_hankaku_bin_start[];

/**
 * カラーパレットを初期化します。
 * @return void
 */
void init_palette(void);

/**
 *  カラーパレットをセットします。
 * @param int start
 * @param int end
 * @param unsigned char *rgb
 */
extern void set_palette(int start, int end, unsigned char *rgb);

/**
 * スクリーンを初期化します
 * @param char *vram
 * @param int x
 * @param int y
 * @return void
 */
extern void init_screen(char *vram, int x, int y);

/**
 * VRAMに指定されたカラーで四角形を描画します
 * @param char *vram
 * @param int xsize
 * @param unsigned char c
 * @param int x0
 * @param int y0
 * @param int x1
 * @param int y1
 * @return void
 */
extern void boxfill8(char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);

/**
 * 文字を1文字分描画します
 * @param char *vram
 * @param int xsize
 * @param int x
 * @param int y
 * @param char c
 * @param char *font
 * @return void
 */
extern void putfont8(char *vram, int xsize, int x, int y, char c, char *font);

/**
 * 文字を1文字分描画します
 * @param char *vram
 * @param int xsize
 * @param int x
 * @param int y
 * @param char c
 * @param char *s
 * @return void
 */
extern void putfont8_asc(char *vram, int xsize, int x, int y, char c, char *s);

/**
 * マウスカーソルを初期化します
 * @param char *mouse
 * @param char bc
 * @return void
 */
extern void init_mouse_cursor8(char *mouse, char bc);

/**
 * 矩形を描画します
 * @param char *vram
 * @param int vxsize
 * @param int pxsize
 * @param int pysize
 * @param int px0
 * @param int py0
 * @param int px1
 * @param int py1
 * @return void
 */
extern void putblock8_8(char *vram, int vxsize, int pxsize,
                        int pysize, int px0, int py0, char *buf, int bxsize);

#endif