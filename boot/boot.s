.code16

.equ BOOTSEG, 0x07c0

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

	jmp .

_loading_string:
	msg : .ascii "Loading System..."
	.byte 13, 10
	len = . - msg
	
.= 510

.word 0xaa55
