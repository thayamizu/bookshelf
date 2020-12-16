
#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "bootpack.h"

/**
 * @brief Keyboardコントローラが送信可能状態になるまで待機します。
 * 
 */
void wait_KBC_sendready(void);

/**
 * @brief キーボードを初期化します。
 * 
 */
void init_keyboard(void);

#endif