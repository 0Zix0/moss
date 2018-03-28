#ifndef _PCI_H
#define _PCI_H

#include <moss.h>
#include <ports.h>
#include <vga.h>

void init_pci();
uint16_t pci_read16(uint32_t bus, uint32_t slot, uint32_t func, uint16_t offset);

#endif