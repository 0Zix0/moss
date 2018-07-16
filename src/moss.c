#include <moss.h>
#include <vga.h>
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

    init_memory((uint32_t)&kernel_end);

    init_gdt();
    init_idt();
    init_isrs();
    init_irq();
    init_timer();
    init_keyboard();

    char* str = malloc(6);
    str[0] = 0x48;
    str[1] = 0x65;
    str[2] = 0x6c;
    str[3] = 0x6c;
    str[4] = 0x6f;
    str[5] = '\0';
    printf("%s\n", str);
    //free(str);
    char* str2 = malloc(6);
    printf("%s | %s\n", str2, str);

    init_paging();

    printf("Searching for ACPI signature.\n");
    init_acpi();

    init_pci();
    pci_print_devices();

    puts("Welcome to ");
    set_color(VGA_GREEN, VGA_BLACK);
    puts("Moss");
    set_color(VGA_WHITE, VGA_BLACK);
    puts(".\n");

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
