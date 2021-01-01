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

head.o: head.s
	@- as --32 head.s -o head.o

# head: head.o
# 	@- ld -T ld-bootsect.ld head.o -o head
# 	@- objcopy -O binary -j .text head

main.o: main.c
	@- gcc -m32 -c main.c -o main.o

system: head.o main.o
	@- ld -m elf_i386 head.o main.o -o system
	@- objcopy -O binary -j .text system

Image: bootsect setup system
	@- dd if=bootsect of=Image bs=512
	@- dd if=setup of=Image bs=512 count=4 seek=1
	@- dd if=system of=Image bs=512 seek=5

run: Image
	@  qemu-system-i386 -boot a -fda Image

debug: Image
	@  qemu-system-i386 -boot a -fda Image -gdb tcp::1234 -S

clean:
	@- rm -f *.o bootsect setup head Image
