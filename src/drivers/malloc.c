#include <memory.h>

uint32_t last_alloc = 0;
uint32_t heap_end = 0;
uint32_t heap_begin = 0;

uint32_t memory_used = 0;

void init_memory(uint32_t kernel_end)
{
    last_alloc = kernel_end + 0x1000;
    heap_begin = last_alloc;
    heap_end = 0x400000;
    //memset((char *)heap_begin, 0, heap_end - heap_begin);
    printf("Kernel heap starts at: 0x%x\n", last_alloc);
}

char* malloc(size_t size)
{
	if(!size) return 0;

	/* Loop through blocks and find a block sized the same or bigger */
	uint8_t *mem = (uint8_t *)heap_begin;
	while((uint32_t)mem < last_alloc)
	{
		struct alloc_t *a = (struct alloc_t *)mem;
		/* If the alloc has no size, we have reaced the end of allocation */
		//mprint("mem=0x%x a={.status=%d, .size=%d}\n", mem, a->status, a->size);
		if(!a->size)
			goto nalloc;
		/* If the alloc has a status of 1 (allocated), then add its size
		 * and the sizeof struct alloc_t to the memory and continue looking.
		 */
		if(a->status) {
			mem += a->size;
			mem += sizeof(struct alloc_t);
			mem += 4;
			continue;
		}
		/* If the is not allocated, and its size is bigger or equal to the
		 * requested size, then adjust its size, set status and return the location.
		 */
		if(a->size >= size)
		{
			/* Set to allocated */
			a->status = 1;

			//printf("RE:Allocated %d bytes from 0x%x to 0x%x\n", size, mem + sizeof(struct alloc_t), mem + sizeof(struct alloc_t) + size);
			memset(mem + sizeof(struct alloc_t), 0, size);
			memory_used += size + sizeof(struct alloc_t);
			return (char *)(mem + sizeof(struct alloc_t));
		}
		/* If it isn't allocated, but the size is not good, then
		 * add its size and the sizeof struct alloc_t to the pointer and
		 * continue;
		 */
		mem += a->size;
		mem += sizeof(struct alloc_t);
		mem += 4;
	}

	nalloc:;
	if(last_alloc+size+sizeof(struct alloc_t) >= heap_end)
	{
		//panic("Cannot allocate %d bytes! Out of memory.\n", size);
	}
	struct alloc_t *alloc = (struct alloc_t *)last_alloc;
	alloc->status = 1;
	alloc->size = size;

	last_alloc += size;
	last_alloc += sizeof(struct alloc_t);
	last_alloc += 4;
	//printf("Allocated %d bytes from 0x%x to 0x%x\n", size, (uint32_t)alloc + sizeof(struct alloc_t), last_alloc);
	memory_used += size + 4 + sizeof(struct alloc_t);
	memset((char *)((uint32_t)alloc + sizeof(struct alloc_t)), 0, size);
    return (char *)((uint32_t)alloc + sizeof(struct alloc_t));
}

void free(void* mem)
{
	struct alloc_t *alloc = (mem - sizeof(struct alloc_t));
    memory_used -= alloc->size + sizeof(struct alloc_t);
    alloc->status = 0;
}
