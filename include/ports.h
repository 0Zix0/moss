#ifndef _PORTS_H
#define _PORTS_H

#include <moss.h>

uint8_t in8(int port);
uint16_t in16(int port);

void out8(int port, uint8_t val);
void out16(int port, uint16_t val);

#endif
