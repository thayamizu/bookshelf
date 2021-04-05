#ifndef MY_MEMORY_H_
#define MY_MEMORY_H_

#define MEMMAN_FREE 4096

typedef struct FREEINFO
{
    unsigned int address, size;
} FreeInfo;

typedef struct MEMAN
{
    int frees, max_frees, losts_size, losts;
    FreeInfo free[MEMMAN_FREE];
} MemoryManager;

/**
 * @brief メモリマネージャ初期化
 * 
 * @param man 
 */
void memman_init(MemoryManager *man);

/**
 * @brief 空き容量のサイズを取得
 * 
 * @param MemoryManager* man 
 * @return unsigned int 
 */
unsigned int memman_total(MemoryManager *man);

/**
 * @brief メモリ確保
 * 
 * @param MemoryManager *man
 * @param unsinged int size 確保したいサイズ 
 * @return unsigned int 
 */
unsigned int memman_alloc(MemoryManager *man, unsigned int size);

/**
 * @brief 4KB単位でメモリ確保をする
 * 
 * @param MemoryManager *man
 * @param unsinged int size 確保したいサイズ 
 * @return unsigned int 
 */
unsigned int memman_alloc_4k(MemoryManager *man, unsigned int size);

/**
 * @brief メモリ解放
 * @param MemoryManager　メモリマネージャのポインタ
 * @param unsinged int メモリアドレス
 * @param unsigned int　確保したいサイズ
 * @return int
 */
int memman_free(MemoryManager *man, unsigned int address, unsigned int size);

/**
 * @brief 4KB単位でメモリ解放をする
 * @param MemoryManager　メモリマネージャのポインタ
 * @param unsinged int メモリアドレス
 * @param unsigned int　確保したいサイズ
 * @return int
 */
int memman_free_4k(MemoryManager *man, unsigned int address, unsigned int size);

#endif
