#ifndef _MEMORY_H
#define _MEMORY_H

#include <moss.h>
#include <vga.h>
#include <string.h>

struct alloc_t {
	uint8_t status;
	uint32_t size;
};

void init_memory(uint32_t kernel_end);
char* malloc(size_t size);
void free(void* mem);

void paging_map_virt_to_phys(uint32_t virt, uint32_t phys);
void enable_paging();
void init_paging();

#endif
