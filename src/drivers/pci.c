#include <pci.h>

char* pci_classify_base_class(uint8_t c)
{
    if(c == 0x00) return "Unclassified";
    if(c == 0x01) return "Mass Storage Controller";
    if(c == 0x02) return "Network Controller";
    if(c == 0x03) return "Display Controller";
    if(c == 0x04) return "Multimedia Converter";
    if(c == 0x05) return "Memory Controller";
    if(c == 0x06) return "Bridge Device";
    if(c == 0x07) return "Simple Communication Controller";
    if(c == 0x08) return "Base System Peripheral";
    if(c == 0x09) return "Input Device Controller";
    if(c == 0x0A) return "Docking Station";
    if(c == 0x0B) return "Processor";
    if(c == 0x0C) return "Serial Bus Controller";
    if(c == 0x0D) return "Wireless Controller";
    if(c == 0x0E) return "Intelligent Controller";
    if(c == 0x0F) return "Satellite Communication Controller";
    if(c == 0x10) return "Encryption Controller";
    if(c == 0x11) return "Signal Processing Controller";
    if(c == 0x12) return "Processing Accelerator";
    if(c == 0x13) return "Non-Essential Instrumentation";
    if(c > 0x13 && c < 0x40) return "Reserved";
    if(c == 0x40) return "Co-Processor";
    if(c > 0x40 && c < 0xFF) return "Reserved";
    if(c == 0xFF) return "Unassigned Class";
    return "";
}

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
                uint16_t classCode = pci_read16(bus, slot, function, 0x0A);
                char* className = pci_classify_base_class((classCode & 0xFF00) >> 8);
                printf("V: %o D: %o CC: %o C: %s\n", vendor, device, classCode, className);
            }
        }
    }
}
