/**
 * @file memory.c
 * @author Joe Bayer (joexbayer)
 * @brief A primitiv memory allocation program and virtual memory functions.
 * @version 0.3
 * @date 2022-06-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <memory.h>
#include <serial.h>
#include <sync.h>
#include <vbe.h>
#include <bitmap.h>
#include <assert.h>

/* prototypes */
void init_memory();
void* kalloc(int size);
void kfree(void* ptr);
/* ... */

static int memory_process_used = 0;
void free(void* ptr)
{
	if(ptr == current_running->allocations->address){
		struct allocation* old = current_running->allocations;
		current_running->allocations = current_running->allocations->next;
		current_running->used_memory -= old->size;
		memory_process_used -= old->size;
		
		dbgprintf("[1] Free %d bytes of data from 0x%x\n", old->size, old->address);
		vmem_free_allocation(old);
		dbgprintf("Done\n");
		return;
	}

	struct allocation* iter = current_running->allocations;
	while(iter->next != NULL){
		if(iter->next->address == ptr){
			
			struct allocation* save = iter->next;
			iter->next = iter->next->next;
			current_running->used_memory -= save->size;
			memory_process_used -= save->size;

			dbgprintf("[2] Free %d bytes of data from 0x%x\n", save->size, save->address);
			vmem_free_allocation(save);
			dbgprintf("Done\n");
			return;
		}
	}
}

void* malloc(unsigned int size)
{	
	assert(size > 0);
	/* For rewrite with pages. */
	int ret;
	int num_pages = (size + PAGE_SIZE - 1) / PAGE_SIZE;
	struct allocation* allocation = kalloc(sizeof(struct allocation));
	allocation->bits = kalloc(sizeof(int)*num_pages);
	allocation->size = size;

	if(current_running->allocations == NULL){
		
		allocation->address = (uint32_t*) VMEM_HEAP;
		allocation->size = size;

		vmem_continious_allocation_map(allocation, allocation->address, num_pages, USER);
		
		allocation->next = NULL;

		current_running->allocations = allocation;
		current_running->used_memory += size;
		
		memory_process_used += size;
		dbgprintf("[1] Allocated %d bytes of data to 0x%x\n", size, allocation->address);
		return (void*) allocation->address;
	}

	struct allocation* iter = current_running->allocations;
	while(iter->next != NULL){
		if((uint32_t)(iter->next->address) - ((uint32_t)(iter->address)+iter->size) >= size){
			/* Found spot for allocation */
			allocation->address = (uint32_t)(iter->address)+iter->size;

			struct allocation* next = iter->next;
			iter->next = allocation;
			allocation->next = next;

			vmem_continious_allocation_map(allocation, allocation->address, num_pages, USER);

			current_running->used_memory += size;
			memory_process_used += size;
			dbgprintf("[2] Allocated %d bytes of data to 0x%x\n", size, allocation->address);
			return (void*) allocation->address;
		}
		iter = iter->next;
	}

	allocation->address = (uint32_t*)((uint32_t)(iter->address)+iter->size);
	vmem_continious_allocation_map(allocation, allocation->address, num_pages, USER);
	allocation->next = NULL;

	iter->next = allocation;
	memory_process_used += size;
	dbgprintf("[3] Allocated %d bytes of data to 0x%x\n", size, allocation->address);
	return (void*) allocation->address;
}

void* calloc(int size, int val)
{
	void* m = malloc(size);
	if(m == NULL)	
		return NULL;

	memset(m, val, size);
	return m;
}

error_t get_mem_info(struct mem_info* info)
{
	struct mem_info inf = {
		.kernel.total = kmemory_total(),
		.kernel.used = kmemory_used(),
		.permanent.total = PMEM_END_ADDRESS-PERMANENT_KERNEL_MEMORY_START,
		.permanent.used = pmemory_used()
	};

	*info = inf;

	return 0;
}

/**
 * @brief Initializes all memory chunks and sets them to be free.
 * 
 * @return void
 */
void init_memory()
{
	kmem_init();
	dbgprintf("Kernel memory initiated\n");
	vmem_init();
	dbgprintf("Virtual memory initiated\n");
	vmem_init_kernel();
	dbgprintf("Virtual Kernel memory initiated\n");
}