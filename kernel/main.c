#include <gdt.h>
#include <video.h>

void main() {
	init_gdt();
	char text[] = "init gdt finish";
	print(text);
	while(1);
}
