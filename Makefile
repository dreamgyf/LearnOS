include ./Makefile.header

SUBDIRS = $(BOOT_DIR) $(KERNEL_DIR) $(DRIVERS_DIR) $(LIB_DIR)

SYSTEM_LINK_FILE = $(BOOT_DIR)/$(OUT_DIR)/head.o \
	$(KERNEL_DIR)/$(OUT_DIR)/main_c.o $(KERNEL_DIR)/$(OUT_DIR)/gdt_s.o $(KERNEL_DIR)/$(OUT_DIR)/gdt_c.o $(KERNEL_DIR)/$(OUT_DIR)/io_c.o \
	$(DRIVERS_DIR)/$(OUT_DIR)/video.o \
	$(LIB_DIR)/$(OUT_DIR)/stdio.o

all: ready Image

ready:
	@ mkdir -p $(OUT_DIR)

$(SUBDIRS): echo
	@ make -C $@

system: $(SUBDIRS)
	@ ld -m elf_i386 $(SYSTEM_LINK_FILE) -o $(OUT_DIR)/$@
	@ objcopy -O binary $(OUT_DIR)/$@

Image: system
	@ dd if=$(BOOT_DIR)/$(OUT_DIR)/bootsect of=$(OUT_DIR)/Image bs=512
	@ dd if=$(BOOT_DIR)/$(OUT_DIR)/setup of=$(OUT_DIR)/Image bs=512 count=4 seek=1
	@ dd if=$(OUT_DIR)/system of=$(OUT_DIR)/Image bs=512 seek=5

echo:
	@ echo $(SUBDIRS)

qemu: all
	@ qemu-system-i386 -boot a -fda build/Image

clean:
	@- for dir in $(SUBDIRS); do make -C $$dir clean; done
	@- rm -rf build

.PHONY: all clean