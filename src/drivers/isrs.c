#include <isrs.h>

extern void _isr0();
extern void _isr1();
extern void _isr2();
extern void _isr3();
extern void _isr4();
extern void _isr5();
extern void _isr6();
extern void _isr7();
extern void _isr8();
extern void _isr9();
extern void _isr10();
extern void _isr11();
extern void _isr12();
extern void _isr13();
extern void _isr14();
extern void _isr15();
extern void _isr16();
extern void _isr17();
extern void _isr18();
extern void _isr19();
extern void _isr20();
extern void _isr21();
extern void _isr22();
extern void _isr23();
extern void _isr24();
extern void _isr25();
extern void _isr26();
extern void _isr27();
extern void _isr28();
extern void _isr29();
extern void _isr30();
extern void _isr31();

void init_isrs()
{
    set_idt_entry(0, (unsigned)_isr0, 0x08, 0x8E);
    set_idt_entry(1, (unsigned)_isr1, 0x08, 0x8E);
    set_idt_entry(2, (unsigned)_isr2, 0x08, 0x8E);
    set_idt_entry(3, (unsigned)_isr3, 0x08, 0x8E);
    set_idt_entry(4, (unsigned)_isr4, 0x08, 0x8E);
    set_idt_entry(5, (unsigned)_isr5, 0x08, 0x8E);
    set_idt_entry(6, (unsigned)_isr6, 0x08, 0x8E);
    set_idt_entry(7, (unsigned)_isr7, 0x08, 0x8E);
    set_idt_entry(8, (unsigned)_isr8, 0x08, 0x8E);
    set_idt_entry(9, (unsigned)_isr9, 0x08, 0x8E);
    set_idt_entry(10, (unsigned)_isr10, 0x08, 0x8E);
    set_idt_entry(11, (unsigned)_isr11, 0x08, 0x8E);
    set_idt_entry(12, (unsigned)_isr12, 0x08, 0x8E);
    set_idt_entry(13, (unsigned)_isr13, 0x08, 0x8E);
    set_idt_entry(14, (unsigned)_isr14, 0x08, 0x8E);
    set_idt_entry(15, (unsigned)_isr15, 0x08, 0x8E);
    set_idt_entry(16, (unsigned)_isr16, 0x08, 0x8E);
    set_idt_entry(17, (unsigned)_isr17, 0x08, 0x8E);
    set_idt_entry(18, (unsigned)_isr18, 0x08, 0x8E);
    set_idt_entry(19, (unsigned)_isr19, 0x08, 0x8E);
    set_idt_entry(20, (unsigned)_isr20, 0x08, 0x8E);
    set_idt_entry(21, (unsigned)_isr21, 0x08, 0x8E);
    set_idt_entry(22, (unsigned)_isr22, 0x08, 0x8E);
    set_idt_entry(23, (unsigned)_isr23, 0x08, 0x8E);
    set_idt_entry(24, (unsigned)_isr24, 0x08, 0x8E);
    set_idt_entry(25, (unsigned)_isr25, 0x08, 0x8E);
    set_idt_entry(26, (unsigned)_isr26, 0x08, 0x8E);
    set_idt_entry(27, (unsigned)_isr27, 0x08, 0x8E);
    set_idt_entry(28, (unsigned)_isr28, 0x08, 0x8E);
    set_idt_entry(29, (unsigned)_isr29, 0x08, 0x8E);
    set_idt_entry(30, (unsigned)_isr30, 0x08, 0x8E);
    set_idt_entry(31, (unsigned)_isr31, 0x08, 0x8E);
}

char* exceptions[32] = {
    "DIVIDE BY ZERO",
    "DEBUG",
    "NON-MASKABLE INTERRUPT",
    "BREAKPOINT",
    "OVERFLOW",
    "BOUND RANGE EXCEEDED",
    "INVALID OPCODE",
    "DEVICE NOT AVAILABLE",
    "DOUBLE FAULT",
    "COPROCESSOR SEGMENT OVERRUN",
    "INVALID TSS",
    "SEGMENT NOT PRESENT",
    "STACK-SEGMENT FAULT",
    "GENERAL PROTECTION FAULT",
    "PAGE FAULT",
    "RESERVED",
    "FLOATING-POINT EXCEPTION (x87)",
    "ALIGNMENT CHECK",
    "FLOATING-POINT EXCEPTION (SIMD)",
    "VIRTUALIZATION EXCEPTION",
    "RESERVED",
    "SECURITY EXCEPTION",
    "RESERVED"
};

void fault_handler(struct registers_t* r)
{
    if(r->int_no < 32) 
    {
        system_exception(exceptions[r->int_no], r);
        system_catch_fire();
    }
}
