#ifndef _FIFO_H_
#define _FIFO_H_

#define FLAGS_OVERUN 0x0001

/**
 * @brief _FIFO8 構造体
 * 
 */
typedef struct _FIFO8
{
    unsigned char *buf;
    int p, q, size, free, flag;
} FIFO8;

/**
 * @brief 
 * 
 * @param fifo 
 * @param size 
 * @param buf 
 */
void init_fifo8(FIFO8 *fifo, int size, unsigned char *buf);

/**
 * @brief Put the fifo8 object
 * 
 * @param fifo 
 * @param data 
 */
int put_fifo8(FIFO8 *fifo, unsigned char data);

/**
 * @brief Get the fifo8 object
 * 
 * @param fifo 
 * @return int 
 */
int get_fifo8(FIFO8 *fifo);

/**
 * @brief Get Status of FIFO8
 * 
 * @param fifo 
 * @return int 
 */
int status_fifo8(FIFO8 *fifo);
#endif