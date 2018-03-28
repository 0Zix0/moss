#ifndef _IDT_H
#define _IDT_H

#include <moss.h>
#include <string.h>

void init_idt();
void set_idt_entry(uint8_t num, uint64_t base, uint16_t sel, uint8_t flags);

#endif
