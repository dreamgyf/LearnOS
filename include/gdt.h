#ifndef _GDT_H
#define _GDT_H

#include <types.h>

struct gdt_entry {
    u16 limit_low;
    u16 base_low;
    u8 base_mid;
    u8 access_byte;
    unsigned limit_high: 4;
    unsigned flags: 4;
    u8 base_high;
} __attribute__((packed));

typedef struct gdt_entry gdt_entry;

//段存在标志P,用于指出一个段是在内存中(P=1)还是不在内存中(P=0): 10000000b
#define GDT_AC_P 0x80

//特权位： 01100000b
#define GDT_AC_DPL_KERN 0x00 // RING 0 kernel level
#define GDT_AC_DPL_SYST 0x20 // RING 1 systask level
#define GDT_AC_DPL_USER 0x60 // RING 3 user level

//描述符类型标志S, S=0：表示存储段描述符,S=1：表示系统描述符。
//00010000b
#define GDT_AC_SYS 0x10

//段类型字段TYPE: 00001111b
#define GDT_AC_CODE 0x08
#define GDT_AC_DATA 0x00

//C=0：表示非一致性代码段。这样的代码段可以被同级代码段调用，或者通过门调用；
//C=1：表示一致性代码段。可以从低特权级的程序转移到该段执行（但是低特权级的程序仍然保持自身的特权级）。

//E=0：表示向上扩展的段（简称上扩段），逻辑地址中的偏移值范围可以从0到Limit；
//E=1：表示向下扩展的段（简称下扩段，通常是栈段），逻辑地址中的偏移范围可以从Limit到0xFFFF（当B=0时）或者0xFFFF_FFFF（当B=1时）。
#define GDT_AC_C_E 0x04

//R=0：代码段不可读，只能执行。
//R=1：代码段可读，可执行。

//W=0：段不允许写入，否则会引发处理器异常中断
//W=1：允许写入
#define GDT_AC_R_W 0x02

//A位, 用于表示一个段最近是否被访问过
#define GDT_AC_A 0x01

//FLAGS 标志位

//颗粒度标志G标志
//如果G=0，则Limit值的单位是B
//如果G=1，则Limit值的单位是4KB
#define GDT_FLAG_G 0x08

#define GDT_FLAG_16_BIT 0x00
#define GDT_FLAG_32_BIT 0x04
#define GDT_FLAG_64_BIT 0x01

struct gdt_ptr {
    u16 limit;
    u32 base;
} __attribute__((packed));

typedef struct gdt_ptr gdt_ptr;

void flush_gdt(u32 ptr);

void init_gdt();
void set_gdt(u8 num, u32 base, u32 limit, u8 access, u8 flags);

#endif