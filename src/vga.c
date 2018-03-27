#include <vga.h>

#define VRAM_ADDRESS 0xB8000
#define VRAM_WIDTH 80
#define VRAM_HEIGHT 25

uint16_t* vmem;
uint16_t cursor_x = 0;
uint16_t cursor_y = 0;
int color = 0x0F;

void init_vga()
{
    vmem = (uint16_t*)VRAM_ADDRESS;
    cls();
}

void cls()
{
    uint16_t empty = (' ' | (color << 8));
    int i;
    for(i = 0; i < VRAM_WIDTH * VRAM_HEIGHT; ++i)
    {
        vmem[i] = empty;
    }
    cursor_x = 0;
    cursor_y = 0;
}

void putc(char c)
{
    if(c == '\n')
    {
        cursor_y++;
        cursor_x = 0;
    }
    else
    {
        vmem[cursor_x + cursor_y * VRAM_WIDTH] = (c | (color << 8));
        cursor_x++;
    }
}

void puts(char* str)
{
    int i = 0;
    while(str[i] != '\0')
    {
        putc(str[i]);
        ++i;
    }
}

void set_color(uint8_t fg, uint8_t bg)
{
    color = (bg << 4) | (fg & 0x0F);
}