.code16

.equ SETUPSEG, 0x9000

.section .text

_start:
	mov $SETUPSEG, %ax
	add $0x20, %ax
	mov %ax, %es
	mov $0x03, %ah
	mov $0x00, %bh
	int $0x10

	mov $0x0007, %bx
	mov $0x1301, %ax
	mov $len, %cx
	mov $msg, %bp
	int $0x10

_move_image:
	mov $0x0000, %ax

do_move:
	mov %ax, %es
	add $0x1000, %ax
	cmp $SETUPSEG, %ax
	jz end_move
	mov %ax, %ds
	sub %di, %di
	sub %si, %si
	mov $0x8000, %cx
	rep movsw
	jmp do_move

end_move:
	mov $SETUPSEG, %ax
	add $0x20, %ax
	mov %ax, %ds

_setup_gdt:
	cli
	lgdt gdt_48

_setup_idt:
	lidt idt_48

_enable_a20:
	in $0x92, %al
	or $0x02, %al
	out %al, $0x92

_enable_protected_mode:
	mov %cr0, %eax
	bts $0, %eax
	mov %eax, %cr0

_jump:
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs	
	ljmp $0x0008, $0

gdt_48:
	.word (gdt_end - gdt) - 1
	.long 0x90200 + gdt

gdt:
	gdt_black: 
	.word 0, 0, 0, 0
	gdt_code:
	.word 0x7ff
	.word 0x0000
	.word 0x9a00
	.word 0x00c0
	gdt_data:
	.word 0x7ff
	.word 0x0000
	.word 0x9200
	.word 0x00c0
gdt_end:

idt_48:
	.word 0
	.word 0, 0

strings:
	msg : .ascii "Load setup successful"
	.byte 13, 10
	len = . - msg
