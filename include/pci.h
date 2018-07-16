#ifndef _PCI_H
#define _PCI_H

#include <moss.h>
#include <ports.h>
#include <vga.h>
#include <memory.h>

void init_pci();
void pci_print_devices();
uint16_t pci_read16(uint32_t bus, uint32_t slot, uint32_t func, uint16_t offset);

struct pci_device_t 
{
    uint16_t vendor;
    uint16_t device;
    // Classcode is defined as 0xAABB.
    // Where AA is the base class and BB is the subclass.
    uint16_t classCode;
};

#endif