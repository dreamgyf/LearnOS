#include <gdt.h>
#include <video.h>

void main() {
	print("init gdt...\n");
	init_gdt();
	print("init gdt finish\n");
}
