TOOLPATH = ../../z_tools/
MAKE     = make
NASK     = $(TOOLPATH)nask
EDIMG    = $(TOOLPATH)edimg
IMGTOL   = $(TOOLPATH)imgtol
COPY     = copy
DEL      = rm

# デフォルト動作
default :
	$(MAKE) img

# Makeルール
ipl.bin : ipl10.nas Makefile
	$(NASK) ipl10.nas ipl.bin ipl.lst

haribote.sys : haribote.nas Makefile
	$(NASK) haribote.nas haribote.sys haribote.lst

haribote.img : ipl.bin haribote.sys Makefile
	$(EDIMG)   imgin:../../z_tools/fdimg0at.tek \
		wbinimg src:ipl.bin len:512 from:0 to:0 \
		copy from:haribote.sys to:@: \
		imgout:haribote.img

# イメージ生成
img :
	$(MAKE) haribote.img

run :
	qemu-system-i386 -fda  ./haribote.img

clean :
	-$(DEL) ipl.bin
	-$(DEL) ipl.lst
	-$(DEL) haribote.sys
	-$(DEL) haribote.lst

src_only :
	$(MAKE) clean
	-$(DEL) haribote.img


