.PHONY=clean, run

all: Image

bootsect.o: bootsect.s
	@- as --32 bootsect.s -o bootsect.o

bootsect: bootsect.o ld-bootsect.ld
	@- ld -T ld-bootsect.ld bootsect.o -o bootsect
	@- objcopy -O binary -j .text bootsect

setup.o: setup.s
	@- as --32 setup.s -o setup.o

setup: setup.o ld-bootsect.ld
	@- ld -T ld-bootsect.ld setup.o -o setup
	@- objcopy -O binary -j .text setup

boothead.o: boothead.s
	@- as --32 boothead.s -o boothead.o

boothead: boothead.o
	@- ld -T ld-bootsect.ld boothead.o -o boothead
	@- objcopy -O binary -j .text boothead

Image: bootsect setup boothead
	@- dd if=bootsect of=Image bs=512
	@- dd if=setup of=Image bs=512 count=4 seek=1
	@- dd if=boothead of=Image bs=512 seek=5

run: Image
	@  qemu-system-i386 -boot a -fda Image

debug: Image
	@  qemu-system-i386 -boot a -fda Image -gdb tcp::1234 -S

clean:
	@- rm -f *.o bootsect setup boothead Image
