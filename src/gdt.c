#include <gdt.h>

struct gdt_entry_t
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));

struct gdt_ptr_t
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct gdt_entry_t gdt[3];
struct gdt_ptr_t gdtp;

extern void gdt_flush();

void set_gdt_entry(int num, uint64_t base, uint64_t limit, uint8_t access, uint8_t granularity)
{
    gdt[num].base_low =  (base & 0xFFFF);
    gdt[num].base_mid =  (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low =   (limit & 0xFFFF);
    gdt[num].granularity = (limit >> 16) & 0x0F;

    gdt[num].granularity |= (granularity & 0xF0);

    gdt[num].access = access;
}

void init_gdt()
{
    gdtp.limit = (sizeof(struct gdt_entry_t) * 3) - 1;
    gdtp.base = (uint32_t)&gdt;

    set_gdt_entry(0, 0, 0, 0, 0);
    set_gdt_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    set_gdt_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    gdt_flush();
}
