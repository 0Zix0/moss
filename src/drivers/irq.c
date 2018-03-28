#include <irq.h>

extern void _irq0();
extern void _irq1();
extern void _irq2();
extern void _irq3();
extern void _irq4();
extern void _irq5();
extern void _irq6();
extern void _irq7();
extern void _irq8();
extern void _irq9();
extern void _irq10();
extern void _irq11();
extern void _irq12();
extern void _irq13();
extern void _irq14();
extern void _irq15();

void* irq_hooks[16] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

void irq_add_hook(int irq, void* handler)
{
    irq_hooks[irq] = handler;
}

void pic_remap()
{
    out8(0x20, 0x11);
    out8(0xA0, 0x11);
    out8(0x21, 0x20);
    out8(0xA1, 0x28);
    out8(0x21, 0x04);
    out8(0xA1, 0x02);
    out8(0x21, 0x01);
    out8(0xA1, 0x01);
    out8(0x21, 0x0);
    out8(0xA1, 0x0);
}

void init_irq()
{
    pic_remap();
    set_idt_entry(32, (unsigned)_irq0, 0x08, 0x8E);
    set_idt_entry(33, (unsigned)_irq1, 0x08, 0x8E);
    set_idt_entry(34, (unsigned)_irq2, 0x08, 0x8E);
    set_idt_entry(35, (unsigned)_irq3, 0x08, 0x8E);
    set_idt_entry(36, (unsigned)_irq4, 0x08, 0x8E);
    set_idt_entry(37, (unsigned)_irq5, 0x08, 0x8E);
    set_idt_entry(38, (unsigned)_irq6, 0x08, 0x8E);
    set_idt_entry(39, (unsigned)_irq7, 0x08, 0x8E);
    set_idt_entry(40, (unsigned)_irq8, 0x08, 0x8E);
    set_idt_entry(41, (unsigned)_irq9, 0x08, 0x8E);
    set_idt_entry(42, (unsigned)_irq10, 0x08, 0x8E);
    set_idt_entry(43, (unsigned)_irq11, 0x08, 0x8E);
    set_idt_entry(44, (unsigned)_irq12, 0x08, 0x8E);
    set_idt_entry(45, (unsigned)_irq13, 0x08, 0x8E);
    set_idt_entry(46, (unsigned)_irq14, 0x08, 0x8E);
    set_idt_entry(47, (unsigned)_irq15, 0x08, 0x8E);
    __asm__ __volatile__("sti");
}

void irq_hook(struct registers_t* r)
{
    void (*handler)(struct registers_t* r);
    handler = irq_hooks[r->int_no - 32];
    if(handler)
    {
        handler(r);
    }
    if(r->int_no >= 40)
    {
        out8(0xA0, 0x20);
    }
    out8(0x20, 0x20);
}
