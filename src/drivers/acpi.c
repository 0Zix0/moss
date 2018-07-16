#include <acpi.h>

// https://wiki.osdev.org/ACPI
// https://wiki.osdev.org/Device_Management
// https://github.com/pdoane/osdev/blob/master/acpi/acpi.c

void acpi_parse(uint8_t* p)
{
    struct rsdp_descriptor_t* rsdp = (struct rsdp_descriptor_t*)p;

    printf("RSDP Info:\n");
    printf("  Sig:       %c%c%c%c%c%c%c%c\n", rsdp->signature[0], 
                                      rsdp->signature[1], 
                                      rsdp->signature[2], 
                                      rsdp->signature[3], 
                                      rsdp->signature[4], 
                                      rsdp->signature[5], 
                                      rsdp->signature[6], 
                                      rsdp->signature[7]);
    printf("  Checksum:  %d\n", rsdp->checksum);
    printf("  OEM:       %c%c%c%c%c%c\n", rsdp->oem[0], 
                                  rsdp->oem[1], 
                                  rsdp->oem[2], 
                                  rsdp->oem[3], 
                                  rsdp->oem[4], 
                                  rsdp->oem[5]);
    printf("  Revision:  %d\n", rsdp->revision);
    printf("  RSDT Addr: 0x%x\n", rsdp->rsdtAddr);

    /*
    // TODO: just chunk a struct over this pointer (https://wiki.osdev.org/RSDP)
    uint8_t sum = 0;
    for(int i = 0; i < 20; i++)
    {
        sum += p[i];
    }

    // TODO: Check if sum is zero, if not, we did not find it.

    char oem[7];
    memcpy(oem, p + 9, 6);
    oem[6] = '\0';
    printf("OEM: '%s'\n", oem);

    uint8_t revision = p[15];
    printf("Revision: %d\n", revision);
    if(revision == 0) {
        // ACPI version 1.
    }
    */
}

void init_acpi()
{
    uint8_t* p = (uint8_t*)0x000e0000;
    uint8_t* end = (uint8_t*)0x000fffff;

    while(p < end) {
        uint64_t sig = *(uint64_t*)p;
        if(sig == 0x2052545020445352) {
            // Found it.
            acpi_parse(p);
        }
        // Signature is on a 16 byte boundary, so incremement by 16.
        p += 16;
    }
}