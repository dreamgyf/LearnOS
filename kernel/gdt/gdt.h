#include <types.h>

struct gdt_entry {
    u16 limit_low;
    u16 base_low;
    u8 base_mid;
    u8 access_byte;
    signed limit_high: 4;
    signed flags: 4;
    u8 base_high;
} __attribute__((packed));

struct gdt_ptr {
    u16 limit;
    u32 base;
} __attribute__((packed));