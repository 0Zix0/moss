#include <idt.h>

struct idt_entry_t
{
    uint16_t base_low;
    uint16_t sel;
    uint8_t zero;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));

struct idt_pointer_t
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

struct idt_entry_t idt[256];
struct idt_pointer_t idtp;

extern void idt_load();

void set_idt_entry(uint8_t num, uint64_t base, uint16_t sel, uint8_t flags)
{
    idt[num].base_low = (base & 0xFFFF);
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].zero =	0;
    idt[num].flags = flags;
}

void init_idt()
{
    idtp.limit = (sizeof(struct idt_entry_t) * 256) - 1;
    idtp.base = (uint32_t)&idt;

    idt_load();
}