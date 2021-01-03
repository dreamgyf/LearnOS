include ../Makefile.header

all: ready video.o

ready:
	@ mkdir -p $(OUT_DIR)

%.o: %.c
	@ gcc -m32 -fno-stack-protector -nostdinc -I ../include -c $< -o $(OUT_DIR)/$@

clean:
	@- rm -rf build

.PHONY: all clean