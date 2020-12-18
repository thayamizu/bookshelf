#　定数値
PROGNAME := haribote.img
SRCDIR := src/
ASMDIR := $(SRCDIR)asm/
ASSETSDIR := $(SRCDIR)assets/
BUILDDIR := build/
OUTDIR := out/
OBJS_BOOTPACK = \
	$(BUILDDIR)bootpack.o \
	$(BUILDDIR)naskfunc.o \
	$(BUILDDIR)hankaku.o \
	$(BUILDDIR)graphic.o \
	$(BUILDDIR)descriptors.o \
	$(BUILDDIR)my_sprintf.o \
	$(BUILDDIR)pic.o \
	$(BUILDDIR)fifo.o \
	$(BUILDDIR)keyboard.o \
	$(BUILDDIR)mouse.o

# ビルドツール
MAKE := make -r
CC := i386-elf-gcc -march=i486 
CFLAGS := -m32 -fno-pic -nostdlib
DEL  := rm -f
MAKEFONT := ../../tools/makefont
NASM := nasm
OBJCOPY := /usr/local/opt/binutils/bin/objcopy

# デフォルト動作
default :
	$(MAKE) img

# 一般規則
$(BUILDDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c $(SRCDIR)$*.c -o $(BUILDDIR)$*.o


# 生成規則
$(BUILDDIR)ipl10.bin : $(ASMDIR)ipl10.nas
	$(NASM) $(ASMDIR)ipl10.nas -o $(BUILDDIR)ipl10.bin -l $(BUILDDIR)ipl10.lst

$(BUILDDIR)asmhead.bin : $(ASMDIR)asmhead.nas
	$(NASM) $(ASMDIR)asmhead.nas -o $(BUILDDIR)asmhead.bin -l $(BUILDDIR)asmhead.lst

$(BUILDDIR)hankaku.bin : $(ASSETSDIR)hankaku.txt
	$(MAKEFONT) $(ASSETSDIR)hankaku.txt $(BUILDDIR)hankaku.bin

$(BUILDDIR)hankaku.o : $(BUILDDIR)hankaku.bin
	$(OBJCOPY) -I binary -O elf32-i386 -B i386 $(BUILDDIR)hankaku.bin $(BUILDDIR)hankaku.o 

$(BUILDDIR)naskfunc.o : $(ASMDIR)naskfunc.nas
	$(NASM) -g -f elf $(ASMDIR)naskfunc.nas -o $(BUILDDIR)naskfunc.o -l $(BUILDDIR)naskfunc.lst

$(BUILDDIR)bootpack.hrb : $(OBJS_BOOTPACK) $(ASMDIR)hrb.ld # リンク，コンパイル
	$(CC) $(CFLAGS) -T $(ASMDIR)hrb.ld -g $(OBJS_BOOTPACK) -o $(BUILDDIR)bootpack.hrb

$(BUILDDIR)haribote.sys : $(BUILDDIR)asmhead.bin $(BUILDDIR)bootpack.hrb
	cat $(BUILDDIR)asmhead.bin $(BUILDDIR)bootpack.hrb > $(BUILDDIR)haribote.sys

haribote.img : $(BUILDDIR)ipl10.bin $(BUILDDIR)haribote.sys Makefile
	mformat -f 1440 -C -B $(BUILDDIR)ipl10.bin -i $(OUTDIR)haribote.img ::
	mcopy -i $(OUTDIR)haribote.img $(BUILDDIR)haribote.sys ::

# make コマンド
img :
	$(MAKE) haribote.img

run :
	$(MAKE) img
	qemu-system-i386 -drive file=$(OUTDIR)haribote.img,format=raw,if=floppy -boot a -m 32M

clean :
	-$(DEL) $(BUILDDIR)*.o
	-$(DEL) $(BUILDDIR)*.bin
	-$(DEL) $(BUILDDIR)*.hrb
	-$(DEL) $(BUILDDIR)*.lst
	-$(DEL) $(BUILDDIR)*.sys
	-$(DEL) $(OUTDIR)*.img
