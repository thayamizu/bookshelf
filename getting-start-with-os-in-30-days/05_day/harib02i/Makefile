MAKE     = make -r
DEL      = rm -f
MAKEFONT = ../../tools/makefont

# デフォルト動作
default :
	$(MAKE) img

# ファイル生成規則
ipl10.bin : ipl10.nas Makefile
	nasm ipl10.nas -o ipl10.bin -l ipl10.lst

asmhead.bin : asmhead.nas Makefile
	nasm asmhead.nas -o asmhead.bin -l asmhead.lst

hankaku.bin : hankaku.txt Makefile
	$(MAKEFONT) hankaku.txt hankaku.bin

hankaku.o : hankaku.bin Makefile
	/usr/local/opt/binutils/bin/objcopy -I binary -O elf32-i386 -B i386 hankaku.bin hankaku.o 

naskfunc.o : naskfunc.nas Makefile          # naskfunc.nasのバイナリファイル作成
	nasm -g -f elf naskfunc.nas -o naskfunc.o -l naskfunc.lst

my_sprintf.o: my_sprintf.c Makefile
	i386-elf-gcc -march=i486 -m32 -fno-pic -nostdlib -c my_sprintf.c -o my_sprintf.o 

bootpack.hrb : bootpack.c hrb.ld hankaku.o my_sprintf.o naskfunc.o Makefile       # リンク，コンパイル
	i386-elf-gcc -march=i486 -m32 -nostdlib -T hrb.ld -g bootpack.c hankaku.o naskfunc.o my_sprintf.o -o bootpack.hrb

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