.PHONY=clean

all:
	@- as --32 boot.s -o boot.o
	@- ld -T ld-boot.ld boot.o -o boot
	@- objcopy -O binary -j .text boot

run:
	@  qemu-system-i386 -boot a -fda boot

clean:
	@- rm -f *.o boot
