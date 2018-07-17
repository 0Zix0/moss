#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <moss.h>
#include <irq.h>
#include <vga.h>
#include <memory.h>

struct key_t
{
    // This keys scancode.
    uint8_t scancode;
    // 1 if the key is pressed or 0 if it was released.
    uint8_t pressed;
    // The ascii code of the key pressed, or zero if not applicable.
    uint8_t ascii;
};

uint8_t kbdus[128];
uint8_t kbdus_mod[128];

void init_keyboard();
//void keyboard_add_handler(int id, void* handler);

#endif