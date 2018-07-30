#include <moss.h>
#include <vga.h>
#include <shell.h>
#include <gdt.h>
#include <idt.h>
#include <isrs.h>
#include <irq.h>
#include <timer.h>
#include <keyboard.h>
#include <memory.h>
#include <pci.h>
#include <acpi.h>
#include <assert.h>

extern uint32_t kernel_end;
extern uint32_t kernel_base;

void kmain() 
{
    init_vga();
    disable_cursor();

    printf("Kernel base: %x\n", &kernel_base);
    printf("Kernel end: %x\n", &kernel_end);

    uint8_t* b = (uint8_t*)0x0600;
    printf("test: %x\n", b[0]);

    init_memory((uint32_t)&kernel_end);

    init_gdt();
    init_idt();
    init_isrs();
    init_irq();
    init_timer();
    init_keyboard();

    init_acpi(); 

    init_paging();

    init_pci();
    pci_print_devices();

    // shell_start();

    // Trigger a page fault.
    // uint32_t *ptr = (uint32_t *)0xA0000000;
    // uint32_t pf = *ptr;

    // Trigger an assertion error.
    // assert(1 == 2);

    // Trigger divide by 0.
    // int a = 10;
    // int b = 0;
    // int c = a / b;

    for(;;);
}
