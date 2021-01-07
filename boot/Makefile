OUT_DIR = build

all: ready bootsect setup head.o

ready:
	@ mkdir -p $(OUT_DIR)

%.o: %.s
	@ as --32 $< -o $(OUT_DIR)/$@

bootsect: bootsect.o ld-bootsect.ld
	@ ld -T ld-bootsect.ld $(OUT_DIR)/$< -o $(OUT_DIR)/$@
	@ objcopy -O binary -j .text $(OUT_DIR)/$@

setup: setup.o ld-bootsect.ld
	@ ld -T ld-bootsect.ld $(OUT_DIR)/$< -o $(OUT_DIR)/$@
	@ objcopy -O binary -j .text $(OUT_DIR)/$@

clean:
	@- rm -rf build

.PHONY=clean, ready