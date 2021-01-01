OUT_DIR = build

all: ready main.o

ready:
	@ mkdir -p $(OUT_DIR)

main.o: main.c
	@ gcc -m32 -c $< -o $(OUT_DIR)/$@

clean:
	@- rm -rf build

.PHONY: all clean