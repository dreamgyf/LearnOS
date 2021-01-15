#include <gdt.h>
#include <stdio.h>
#include <video.h>

void main() {
	print("init gdt...\n");
	init_gdt();
	print("init gdt finish\n");

	double i = 2.6;
	printf("i = %f", i);
}
