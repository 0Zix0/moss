#ifndef _ACPI_H
#define _ACPI_H

#include <moss.h>
#include <vga.h>
#include <string.h>

void init_acpi();

struct rsdp_descriptor_t {
    char signature[8];
    uint8_t checksum;
    char oem[6];
    uint8_t revision;
    uint32_t rsdtAddr;
} __attribute__((packed));

#endif