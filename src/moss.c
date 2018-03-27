#include <moss.h>
#include <vga.h>
#include <gdt.h>

void _start() 
{
    init_vga();
    disable_cursor();
    
    init_gdt();

    puts("Welcome to ");
    set_color(VGA_GREEN, VGA_BLACK);
    puts("Moss");
    set_color(VGA_WHITE, VGA_BLACK);
    puts(".\n");

    puts("Hello world.\n");

    for(;;);
}
