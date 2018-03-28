#include <pci.h>

uint16_t pci_read16(uint32_t bus, uint32_t slot, uint32_t func, uint16_t offset)
{
    uint64_t address;
    uint64_t lbus = (uint64_t)bus;
    uint64_t lslot = (uint64_t)slot;
    uint64_t lfunc = (uint64_t)func;
    uint16_t tmp = 0;
    address = (uint64_t)((lbus << 16) | (lslot << 11) | (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));
    out32(0xCF8, address);
    tmp = (uint16_t)((in32(0xCFC) >> ((offset & 2) * 8)) & 0xffff);
    return (tmp);
}

void init_pci()
{
    for(uint32_t bus = 0; bus < 256; bus++)
    {
        for(uint32_t slot = 0; slot < 32; slot++)
        {
            for(uint32_t function = 0; function < 8; function++)
            {
                uint16_t vendor = pci_read16(bus, slot, function, 0);
                if(vendor == 0xFFFF) continue;
                uint16_t device = pci_read16(bus, slot, function, 2);
                printf("V: %x D: %x\n", vendor, device);
            }
        }
    }
}
