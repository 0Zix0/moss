#ifndef _MEMORY_H
#define _MEMORY_H

#include <moss.h>
#include <vga.h>

void paging_map_virt_to_phys(uint32_t virt, uint32_t phys);
void enable_paging();
void init_paging();

#endif
