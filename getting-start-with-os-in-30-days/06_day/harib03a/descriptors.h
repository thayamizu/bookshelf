#ifndef MY_DESCRIPTOR_TABLE_H_
#define MY_DESCRIPTOR_TABLE_H_

/**
 * セグメント記述子
 */
typedef struct _SegmentDescriptor
{
    short limit_low, base_low;
    char base_mid, access_right;
    char limit_high, base_high;
} SegmentDescriptor;

/**
 * 割り込み記述子
 */
typedef struct _GateDescriptor
{
    short offset_low, selector;
    char dw_count, access_right;
    short offset_high;
} GateDescriptor;

/**
 *  GDTとIDTを初期化します。
 * @return void
 */
extern void init_gdtidt(void);

/**
 * セグメント記述子を指定します。
 * @param SegmentDescriptor *sd
 * @param unsigned int limit
 * @param int base
 * @param int ar
 * @return void
 */
extern void set_segmdesc(SegmentDescriptor *sd, unsigned int limit, int base, int ar);

/**
 * 割り込み記述子を指定します。
 * @param GateDescriptor *gd
 * @param int offset
 * @param int selector
 * @param int ar
 * @return void
 */
extern void set_gatedesc(GateDescriptor *gd, int offset, int seletor, int ar);

/**
 * IDTRをロードします。
 * @param int limit
 * @param int address
 * @return void
 */
extern void load_idtr(int limit, int address);

/**
 *  GDTRをロードします。
 *  @param int limit
 *  @param int limit
 *  @return void
 */
extern void load_gdtr(int limit, int address);

#endif