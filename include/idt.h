#ifndef _IDT_H
#define _IDT_H

#include <types.h>

struct idt_entry {
    u16 base_low;
    u16 selector;
    u8 zero;
    u8 access_byte;
    u16 base_high;
} __attribute__((packed));

typedef struct idt_entry idt_entry;

struct idt_ptr {
    u16 limit;
    u32 base;
} __attribute__((packed));

typedef struct idt_ptr idt_ptr;

#endif