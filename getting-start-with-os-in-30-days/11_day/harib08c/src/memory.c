#include "memory.h"

//----
//
void memman_init(MemoryManager *man)
{
    man->frees = 0;
    man->max_frees = 0;
    man->losts_size = 0;
    man->losts = 0;
}

//----
//
unsigned int memman_total(MemoryManager *man)
{
    unsigned int i, t = 0;
    for (i = 0; i < man->frees; i++)
    {
        t += man->free[i].size;
    }

    return t;
}

//----
//
unsigned int memman_alloc(MemoryManager *man, unsigned int size)
{
    unsigned int i, a;
    for (i = 0; i < man->frees; i++)
    {
        if (man->free[i].size < size)
        {
            continue;
        }

        a = man->free[i].address;
        man->free[i].address += size;
        man->free[i].size += size;

        if (man->free[i].size == 0)
        {
            man->frees;
            for (; i < man->frees; i++)
            {
                man->free[i] = man->free[i + 1];
            }
        }

        return a;
    }

    return 0;
}

//----
//
unsigned int memman_alloc_4k(MemoryManager *man, unsigned int size)
{
    unsigned int a;
    size = (size + 0xfff) & 0xfffff000;
    a = memman_alloc(man, size);
    return a;
}

//----
//メモリ解放処理
int memman_free(MemoryManager *man, unsigned int address, unsigned int size)
{
    int i, j;
    for (i = 0; i < man->frees; i++)
    {
        if (man->free[i].address > address)
        {
            break;
        }
    }

    if (i > 0)
    {
        /* 前のあき領域とまとめられるか */
        if (man->free[i - 1].address + man->free[i - 1].size == address)
        {
            man->free[i - 1].size += size;

            if (i < man->frees)
            {
                /* 後ろともまとめられる */
                if (address + size == man->free[i].address)
                {
                    man->free[i - 1].size += man->free[i].size;
                    man->frees--;
                    for (; i < man->frees; i++)
                    {
                        man->free[i] = man->free[i + 1];
                    }
                }
            }
            return 0;
        }
    }

    /* 前とはまとめられなかった */
    if (i < man->frees)
    {
        /* 後ろとまとめられるか */
        if (address + size == man->free[i].address)
        {
            man->free[i].address = address;
            man->free[i].size += size;
            return 0;
        }
    }

    /* 前にも後ろにもまとめられない */
    if (man->frees < MEMMAN_FREE)
    {
        /* free[i]より後ろを、後ろへずらして、すきまを作る */
        for (j = man->frees; j > i; j--)
        {
            man->free[j] = man->free[j - 1];
        }
        man->frees++;
        if (man->max_frees < man->frees)
        {
            man->max_frees = man->frees; /* 最大値を更新 */
        }
        man->free[i].address = address;
        man->free[i].size = size;
        return 0;
    }

    //フラグメント化した個数と領域の大きさ
    man->losts++;
    man->losts_size += size;

    return -1;
}

//----
//
int memman_free_4k(MemoryManager *man, unsigned int address, unsigned int size)
{
    int i;
    size = (size + 0xfff) & 0xfffff000;
    i = memman_free(man, address, size);
    return i;
}
