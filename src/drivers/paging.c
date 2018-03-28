#include <memory.h>

static uint32_t* page_directory = 0;
static uint32_t page_dir_location = 0;
static uint32_t* last_page = 0;

void paging_map_virt_to_phys(uint32_t virt, uint32_t phys)
{
    uint16_t id = virt >> 22;
    for(int i = 0; i < 1024; i++)
    {
        last_page[i] = phys | 3;
        phys += 4096;
    }
    page_directory[id] = ((uint32_t)last_page) | 3;
    last_page = (uint32_t*)(((uint32_t)last_page) + 4096);
    printf("Mapping 0x%x (%d) to 0x%x\n", virt, id, phys);
}

void enable_paging()
{
	asm volatile("mov %%eax, %%cr3": :"a"(page_dir_location));	
	asm volatile("mov %cr0, %eax");
	asm volatile("orl $0x80000000, %eax");
    asm volatile("mov %eax, %cr0");
}

void init_paging()
{
    page_directory = (uint32_t*)0x400000;
    page_dir_location = (uint32_t)page_directory;
    last_page = (uint32_t*)0x404000;
    for(int i = 0; i < 1024; i++)
    {
        page_directory[i] = 0 | 2;
    }
    paging_map_virt_to_phys(0, 0);
    paging_map_virt_to_phys(0x400000, 0x400000);
    enable_paging();
}
