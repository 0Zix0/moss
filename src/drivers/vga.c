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
    set_cursor_pos(cursor_x, cursor_y);
}

void set_color(uint8_t fg, uint8_t bg)
{
    color = (bg << 4) | (fg & 0x0F);
}

void enable_cursor_size(uint8_t start, uint8_t end)
{
    out8(0x3D4, 0x0A);
	out8(0x3D5, (in8(0x3D5) & 0xC0) | start);
 
	out8(0x3D4, 0x0B);
	out8(0x3D5, (in8(0x3E0) & 0xE0) | end);
}

void enable_cursor()
{
    enable_cursor_size(14, 15);
}

void disable_cursor()
{
    out8(0x3D4, 0x0A);
    out8(0x3D5, 0x20);
}

void set_cursor_pos(int x, int y)
{
    uint16_t pos = y * VRAM_WIDTH + x;
 
    out8(0x3D4, 0x0F);
	out8(0x3D5, (uint8_t) (pos & 0xFF));
	out8(0x3D4, 0x0E);
	out8(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));

    cursor_x = x;
    cursor_y = y;
}

int get_cursor_x()
{
    return cursor_x;
}

int get_cursor_y()
{
    return cursor_y;
}
