#ifndef _TIMER_H
#define _TIMER_H

#include <moss.h>
#include <irq.h>
#include <vga.h>

void init_timer();
void timer_set(int hz);

#endif