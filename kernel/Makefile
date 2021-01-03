OUT_DIR = build

all: ready gdt_s.o gdt_c.o main_c.o io_c.o

ready:
	@ mkdir -p $(OUT_DIR)

%_s.o: %.s
	@ as --32 $< -o $(OUT_DIR)/$@

%_c.o: %.c
	@ gcc -m32 -fno-stack-protector -nostdinc -I ../include -c $< -o $(OUT_DIR)/$@

clean:
	@- rm -rf build

.PHONY: all clean