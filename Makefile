BOOT_DIR = boot
KERNEL_DIR = kernel

OUT_DIR = build

SUBDIRS = $(BOOT_DIR) $(KERNEL_DIR)

all: ready Image

ready:
	@ mkdir -p $(OUT_DIR)

$(SUBDIRS): echo
	@ make -C $@

system: $(SUBDIRS)
	@ ld -m elf_i386 $(BOOT_DIR)/$(OUT_DIR)/head.o $(KERNEL_DIR)/$(OUT_DIR)/main_c.o $(KERNEL_DIR)/$(OUT_DIR)/gdt_s.o $(KERNEL_DIR)/$(OUT_DIR)/gdt_c.o -o $(OUT_DIR)/$@
	@ objcopy -O binary -j .text $(OUT_DIR)/$@

Image: system
	@ dd if=$(BOOT_DIR)/$(OUT_DIR)/bootsect of=$(OUT_DIR)/Image bs=512
	@ dd if=$(BOOT_DIR)/$(OUT_DIR)/setup of=$(OUT_DIR)/Image bs=512 count=4 seek=1
	@ dd if=$(OUT_DIR)/system of=$(OUT_DIR)/Image bs=512 seek=5

echo:
	@ echo $(SUBDIRS)

clean:
	@- for dir in $(SUBDIRS); do make -C $$dir clean; done
	@- rm -rf build

.PHONY: all clean