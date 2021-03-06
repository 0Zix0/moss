#include <ports.h>

uint8_t in8(int port)
{
	uint8_t result;
	asm("inb %w1, %b0" : "=a" (result) : "Nd" (port) );
	return result;
}

uint16_t in16(int port)
{
	uint16_t result;
	asm("inw %w1, %w0" : "=a" (result) : "Nd" (port) );
	return result;
}

uint32_t in32(int port)
{
	uint32_t result;
	asm volatile ("inl %%dx, %%eax" : "=a" (result) : "dN" (port));
	return result;
}

void out8(int port, uint8_t val)
{
    asm("outb %b0, %w1" : : "a" (val), "Nd" (port) );
}

void out16(int port, uint16_t val)
{
    asm("outw %w0, %w1" : : "a" (val), "Nd" (port) );
}

void out32(int port, uint32_t val)
{
	asm volatile ("outl %%eax, %%dx" : : "dN" (port), "a" (val));
}
