#include <moss.h>
#include <vga.h>
#include <gdt.h>
#include <idt.h>
#include <isrs.h>
#include <irq.h>
#include <timer.h>
#include <keyboard.h>
#include <memory.h>

extern uint32_t kernel_end;
extern uint32_t kernel_base;

void kmain() 
{
    init_vga();
    disable_cursor();

    printf("Kernel base: %x\n", &kernel_base);
    printf("Kernel end: %x\n", &kernel_end);

    init_gdt();
    init_idt();
    init_isrs();
    init_irq();
    init_timer();
    init_keyboard();

    init_paging();

    puts("Welcome to ");
    set_color(VGA_GREEN, VGA_BLACK);
    puts("Moss");
    set_color(VGA_WHITE, VGA_BLACK);
    puts(".\n");

    // Trigger divide by 0.
    //int a = 10;
    //int b = 0;
    //int c = a / b;

    for(;;);
}
