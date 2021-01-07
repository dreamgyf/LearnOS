.code16

.equ BOOTSEG, 0x07c0
.equ INITSEG, 0x9000
.equ SETUP_OFFSET, 0x0200
.equ SYSSEG, 0x1000

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

move_me:
	mov $BOOTSEG, %ax
	mov %ax, %ds
	
	mov $INITSEG, %ax
	mov %ax, %es

	mov $0x200, %cx

	sub %si, %si
	sub %di, %di

	rep movsb

	ljmp $INITSEG, $move_finish

move_finish:
	mov %cs, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %ss

load_setup:
	mov $INITSEG, %ax
	mov %ax, %es
	mov $SETUP_OFFSET, %bx

	mov $0x0002, %cx
	mov $0x0000, %dx

	mov $0x02, %ah
	mov $0x04, %al
	int $0x13

	jnc load_system
	jmp load_setup

load_system:
	mov $SYSSEG, %ax
	mov %ax, %es
	mov $0x0000, %bx

	mov $0x0006, %cx
	mov $0x0000, %dx

	mov $0x02, %ah
	mov $0x40, %al
	int $0x13

	jnc on_load_success
	jmp load_system

on_load_success:
	mov $INITSEG, %ax
	mov %ax, %ds
	ljmp $INITSEG, $SETUP_OFFSET

loading_string:
	msg : .ascii "Loading System..."
	.byte 13, 10
	len = . - msg
	
.= 510

.word 0xaa55
