#ifndef _IRQ_H
#define _IRQ_H

#include <moss.h>
#include <idt.h>
#include <ports.h>

void init_irq();
void irq_add_hook(int irq, void* handler);

#endif