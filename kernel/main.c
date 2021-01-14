#include <gdt.h>
#include <stdio.h>
#include <video.h>

void main() {
	print("init gdt...\n");
	init_gdt();
	print("init gdt finish\n");

	int i = 2;
	printf("i = %d", i);
}
