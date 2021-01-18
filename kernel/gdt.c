#include <gdt.h>

#define GDT_NUM 7

#define SEL_BLANK 0
#define SEL_KCODE 1 // 内核代码段
#define SEL_KDATA 2 // 内核数据段
#define SEL_SCODE 3 // 系统代码段
#define SEL_SDATA 4 // 系统数据段
#define SEL_UCODE 5 // 用户代码段
#define SEL_UDATA 6 // 用户数据段

extern void flush_gdt(u32 ptr);

static gdt_entry gdt[GDT_NUM];
static gdt_ptr ptr;

void init_gdt() {
    set_gdt(SEL_BLANK, 0, 0, 0, 0);

    set_gdt(SEL_KCODE, 0, 0xfffff, GDT_AC_P|GDT_AC_DPL_KERN|GDT_AC_SYS|GDT_AC_CODE|GDT_AC_R_W, GDT_FLAG_G|GDT_FLAG_32_BIT);
    set_gdt(SEL_KDATA, 0, 0xfffff, GDT_AC_P|GDT_AC_DPL_KERN|GDT_AC_SYS|GDT_AC_DATA|GDT_AC_R_W, GDT_FLAG_G|GDT_FLAG_32_BIT);

    set_gdt(SEL_SCODE, 0, 0xfffff, GDT_AC_P|GDT_AC_DPL_SYST|GDT_AC_SYS|GDT_AC_CODE|GDT_AC_R_W, GDT_FLAG_G|GDT_FLAG_32_BIT);
    set_gdt(SEL_SDATA, 0, 0xfffff, GDT_AC_P|GDT_AC_DPL_SYST|GDT_AC_SYS|GDT_AC_DATA|GDT_AC_R_W, GDT_FLAG_G|GDT_FLAG_32_BIT);

    set_gdt(SEL_UCODE, 0, 0xfffff, GDT_AC_P|GDT_AC_DPL_USER|GDT_AC_SYS|GDT_AC_CODE|GDT_AC_R_W, GDT_FLAG_G|GDT_FLAG_32_BIT);
    set_gdt(SEL_UDATA, 0, 0xfffff, GDT_AC_P|GDT_AC_DPL_USER|GDT_AC_SYS|GDT_AC_DATA|GDT_AC_R_W, GDT_FLAG_G|GDT_FLAG_32_BIT);

    ptr.limit = sizeof(gdt) - 1;
    ptr.base = (u32) &gdt;

    flush_gdt((u32) &ptr);
}

void set_gdt(u8 num, u32 base, u32 limit, u8 access, u8 flags) {
    gdt[num].base_low = base & 0xffff;
    gdt[num].base_mid = (base >> 16) & 0xff;
    gdt[num].base_high = (base >> 24) & 0xff;

    gdt[num].limit_low = limit & 0xffff;
    gdt[num].limit_high = (limit >> 16) & 0xf;

    gdt[num].access_byte = access;
    gdt[num].flags = flags & 0xff;
}