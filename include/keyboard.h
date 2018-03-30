#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <moss.h>
#include <irq.h>
#include <vga.h>

unsigned char kbdus[128];

void init_keyboard();

#endif