.code16

.equ BOOTSEG, 0x07c0
.equ SETUPSEG, 0x9000

.global _start

.section .text

ljmp $BOOTSEG, $_start

_start:
	mov $0x03, %ah
	mov $0x00, %bh
	int $0x10

	mov $BOOTSEG, %ax
	mov %ax, %es
	mov $msg, %bp
	mov $len, %cx

	mov $0x13, %ah
	mov $0x01, %al
	mov $0x00, %bh
	mov $0x07, %bl
	
	int $0x10

_load_setup:
	mov $0x0002, %cx
	mov $0x0000, %dx
	
	mov $SETUPSEG, %ax
	mov %ax, %es
	mov $0x0200, %bx

	mov $0x02, %ah
	mov $0x04, %al
	int $0x13

	jnc on_load_setup_success
	jmp _load_setup

on_load_setup_success:
	mov $SETUPSEG, %ax
	mov %ax, %ds
	ljmp $SETUPSEG, $0x0200

_loading_string:
	msg : .ascii "Loading System..."
	.byte 13, 10
	len = . - msg
	
.= 510

.word 0xaa55
