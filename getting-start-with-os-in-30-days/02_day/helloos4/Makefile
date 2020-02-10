ipl.bin : ipl.nas Makefile
	../../z_tools/nask ipl.nas ipl.bin ipl.lst

helloos.img : ipl.bin Makefile
	../../z_tools/edimg   imgin:../../z_tools/fdimg0at.tek \
		wbinimg src:ipl.bin len:512 from:0 to:0   imgout:helloos.img

img :
	make -r helloos.img

run :
	make img
	qemu-system-i386 -fda  ./helloos.img
