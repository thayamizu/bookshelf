#include "fifo.h"

/**
 * @brief 
 * 
 * @param fifo 
 * @param size 
 * @param buf 
 */
void init_fifo8(FIFO8 *fifo, int size, unsigned char *buf)
{
    fifo->p = 0;
    fifo->q = 0;
    fifo->flag = 0;
    fifo->size = size;
    fifo->free = size;
    fifo->buf = buf;

    return;
}

/**
 * @brief Construct a new intput fifo8 object
 * 
 * @param fifo 
 * @param data 
 */
int put_fifo8(FIFO8 *fifo, unsigned char data)
{
    if (fifo->free == 0)
    {
        fifo->flag |= FLAGS_OVERUN;

        return -1;
    }

    fifo->buf[fifo->p] = data;
    fifo->p++;
    if (fifo->p == fifo->size)
    {
        fifo->p = 0;
    }
    fifo->free--;

    return 0;
}

/**
 * @brief Get the fifo8 object
 * 
 * @param fifo 
 * @return int 
 */
int get_fifo8(FIFO8 *fifo)
{
    int data = -1;
    if (fifo->free == fifo->size)
    {
        return data;
    }

    data = fifo->buf[fifo->q++];
    if (fifo->q == fifo->size)
    {
        fifo->q = 0;
    }
    fifo->free++;

    return data;
}

int status_fifo8(FIFO8 *fifo)
{
    return fifo->size - fifo->free;
}