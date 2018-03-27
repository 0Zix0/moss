#include <moss.h>
#include <vga.h>

void _start() 
{
    init_vga();

    puts("Hello world.\n");
    puts("Welcome to ");

    set_color(VGA_GREEN, VGA_BLACK);
    puts("Moss");
    set_color(VGA_WHITE, VGA_BLACK);
    puts(".\n");

    for(;;);
}
