include ../Makefile.header

all: ready gdt_s.o gdt_c.o main_c.o io_c.o

ready:
	@ mkdir -p $(OUT_DIR)

%_s.o: %.s
	@ as --32 $< -o $(OUT_DIR)/$@

%_c.o: %.c
	@ $(CC) $(CFLAGS) -I ../include $< -o $(OUT_DIR)/$@

clean:
	@- rm -rf build

.PHONY: all clean