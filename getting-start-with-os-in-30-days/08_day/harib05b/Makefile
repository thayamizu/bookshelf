#コマンド
MAKE     = make -r
DEL      = rm -f
MAKEFONT = ../../tools/makefont
CC = i386-elf-gcc -march=i486 
CFLAGS = -m32 -fno-pic -nostdlib
NASM = nasm
OBJCOPY = /usr/local/opt/binutils/bin/objcopy
# Bootpackのイメージ作成に必要なオブジェクトファイルのリスト
OBJS_BOOTPACK = bootpack.o naskfunc.o hankaku.o graphic.o descriptors.o my_sprintf.o pic.o fifo.o

# デフォルト動作
default :
	$(MAKE) img

# 一般規則
%.o : %.c
	$(CC) $(CFLAGS) -c $*.c -o $*.o

# 生成規則
ipl10.bin : ipl10.nas Makefile
	$(NASM) ipl10.nas -o ipl10.bin -l ipl10.lst

asmhead.bin : asmhead.nas Makefile
	$(NASM) asmhead.nas -o asmhead.bin -l asmhead.lst

hankaku.bin : hankaku.txt Makefile
	$(MAKEFONT) hankaku.txt hankaku.bin

hankaku.o : hankaku.bin Makefile
	$(OBJCOPY) -I binary -O elf32-i386 -B i386 hankaku.bin hankaku.o 

naskfunc.o : naskfunc.nas Makefile              # naskfunc.nasのバイナリファイル作成
	$(NASM) -g -f elf naskfunc.nas -o naskfunc.o -l naskfunc.lst

bootpack.hrb : $(OBJS_BOOTPACK) hrb.ld Makefile # リンク，コンパイル
	$(CC) $(CFLAGS) -T hrb.ld -g $(OBJS_BOOTPACK) -o bootpack.hrb

haribote.sys : asmhead.bin bootpack.hrb Makefile
	cat asmhead.bin bootpack.hrb > haribote.sys

haribote.img : ipl10.bin haribote.sys Makefile
	mformat -f 1440 -C -B ipl10.bin -i haribote.img ::
	mcopy -i haribote.img haribote.sys ::

# コマンド
img :
	$(MAKE) haribote.img

run :
	$(MAKE) img
	qemu-system-i386 -drive file=haribote.img,format=raw,if=floppy -boot a

clean :
	-$(DEL) *.bin
	-$(DEL) *.lst
	-$(DEL) *.o
	-$(DEL) *.sys
	-$(DEL) *.hrb

src_only :
	$(MAKE) clean
	-$(DEL) haribote.img