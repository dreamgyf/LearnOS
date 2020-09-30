.code16

.equ SETUPSEG, 0xf000

.section .text

_start:
	mov $SETUPSEG, %ax
	mov %ax, %es
	mov $0x03, %ah
	mov $0x00, %bh
	int $0x10

	mov $0x0007, %bx
	mov $0x1301, %ax
	mov $len, %cx
	mov $msg, %bp
	int $0x10

	jmp .

_loading_string:
	msg : .ascii "Load setup successful"
	.byte 13, 10
	len = . - msg
