.code32

.section .text

.global _start

_start:
	jmp .

	mov $0x03, %ah
        mov $0x00, %bh
        int $0x10

        mov $0x0007, %bx
        mov $0x1301, %ax
        mov $len, %cx
        mov $msg, %bp
        int $0x10

	jmp .

strings:
        msg : .ascii "jump to 32bit protected mode successful"
        .byte 13, 10
        len = . - msg

