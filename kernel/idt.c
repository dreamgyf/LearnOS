#include <idt.h>

#define IDT_NUM 256

extern void flush_idt(u32 ptr);
extern void open_interrupt();

static idt_entry idt[IDT_NUM];
static idt_ptr ptr;

extern u32 ints[];

void init_idt() {
    for (int i = 0; i < IDT_NUM; i++) {
        set_idt(i, 0x08, ints[i], IDT_FLAG_P|IDT_FLAG_DPL_KERNEL|IDT_TYPE_INT);
    }
    set_idt(0x80, 0x08, ints[0x80], IDT_FLAG_P|IDT_FLAG_DPL_USER|IDT_TYPE_TRAP);
    set_idt(0x60, 0x08, ints[0x60], IDT_FLAG_P|IDT_FLAG_DPL_USER|IDT_TYPE_TRAP);

    ptr.limit = sizeof(idt) - 1;
    ptr.base = (u32) idt;
    flush_idt((u32)&ptr);
}

void set_idt(u8 num, u16 selector, u32 offset, u8 flags) {
    idt[num].offset_low = offset & 0xffff;
    idt[num].offset_high = (offset >> 16) & 0xffff;

    idt[num].selector = selector;
    idt[num].zero = 0;
    idt[num].flags = flags;
}