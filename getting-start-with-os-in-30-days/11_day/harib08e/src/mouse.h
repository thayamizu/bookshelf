#ifndef MY_MOUSE_H_
#define MY_MOUSE_H_

#include "bootpack.h"

/**
 * @brief マウスディスクリプタ構造体
 * 
 */
typedef struct _Mouse_DEC
{
    unsigned char buf[MOUSE_PHASE], phase;
    int x, y, btn;
} MouseDesc;

/**
 * @brief マウスの初期化をします。
 * 
 * @param desc 
 */
void init_mouse(MouseDesc *desc);

/**
 * @brief マウスを有効化します。
 * 
 * @param desc 
 */
void enable_mouse(MouseDesc *desc);

/**
 * @brief 割り込みハンドラから受け取ったデータをマウス情報としてデコードします。
 * 
 * @param desc 
 * @param data 
 * @return int 
 */
int decode_mouse(MouseDesc *desc, unsigned char data);

#endif