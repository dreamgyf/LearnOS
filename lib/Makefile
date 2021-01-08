include ../Makefile.header

all: ready stdio.o string.o

ready:
	@ mkdir -p $(OUT_DIR)

%.o: %.c
	@ $(CC) $(CFLAGS) -I ../include $< -o $(OUT_DIR)/$@

clean:
	@- rm -rf build

.PHONY: all clean