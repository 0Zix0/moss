#ifndef _VGA_H
#define _VGA_H

#include <moss.h>
#include <ports.h>

#define VGA_BLACK           0x00
#define VGA_BLUE            0x01
#define VGA_GREEN           0x02
#define VGA_CYAN            0x03
#define VGA_RED             0x04
#define VGA_MAGENTA         0x05
#define VGA_BROWN           0x06
#define VGA_LIGHT_GRAY      0x07
#define VGA_DARK_GRAY       0x08
#define VGA_LIGHT_BLUE      0x09
#define VGA_LIGHT_GREEN     0x0A
#define VGA_LIGHT_CYAN      0x0B
#define VGA_LIGHT_RED       0x0C
#define VGA_LIGHT_MAGENTA   0x0D
#define VGA_YELLOW          0x0E
#define VGA_WHITE           0x0F

void init_vga();
void cls();
void putc(char c);
void puts(char* str);
void set_color(uint8_t fg, uint8_t bg);

void enable_cursor_size(uint8_t start, uint8_t end);
void enable_cursor();
void disable_cursor();
void set_cursor_pos(int x, int y);

int get_cursor_x();
int get_cursor_y();

void printf(const char *fmt, ...);

#endif
