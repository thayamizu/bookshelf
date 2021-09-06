#ifndef MY_TIMER_H_
#define MY_TIMER_H_

#define PIT_CTRL 0x0043
#define PIT_CNT0 0x0040

/**
 * @brief PITを初期化します。
 * 
 */
void init_pit(void);

#endif