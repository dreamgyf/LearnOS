#ifndef _IDT_H
#define _IDT_H

#include <types.h>

struct idt_entry {
    u16 offset_low;
    u16 selector;
    u8 zero;
    u8 flags;
    u16 offset_high;
} __attribute__((packed));

typedef struct idt_entry idt_entry;

struct idt_ptr {
    u16 limit;
    u32 base;
} __attribute__((packed));

typedef struct idt_ptr idt_ptr;

#define IDT_FLAG_P 0x80
#define IDT_FLAG_DPL_KERNEL 0x00
#define IDT_FLAG_DPL_USER 0x60
#define IDT_TYPE_INT 0x0e
#define IDT_TYPE_TRAP 0x0f
#define IDT_TYPE_TASK 0x05

void flush_idt(u32 ptr);
void open_interrupt();

void init_idt();

#endif