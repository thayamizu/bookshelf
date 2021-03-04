#ifndef MY_DESCRIPTOR_TABLE_H_
#define MY_DESCRIPTOR_TABLE_H_

/**
 * 定数
 */
#define ADR_IDT 0x0026f800
#define LIMIT_IDT 0x000007ff
#define ADR_GDT 0x00270000
#define LIMIT_GDT 0x0000ffff
#define ADR_BOTPAK 0x00280000
#define LIMIT_BOTPAK 0x0007ffff
#define AR_DATA32_RW 0x4092
#define AR_CODE32_ER 0x409a
#define AR_INTGATE32 0x008e

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