#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>
#include <pcb.h>

extern char _code[], _end[], _code_end[], _ro_s[], _ro_e[], _data_s[], _data_e[], _bss_s[], _bss_e[];
extern int kernel_size;

enum {
	USED,
	FREE
};

#define PERMANENT_MEM_START 0x100000
#define PERMANENT_MEM_END 	0x200000
#define MEM_START 			    0x300000
#define MEM_END   			    0x400000
#define MEM_CHUNK 			    0x400
#define CHUNKS_SIZE (MEM_END-MEM_START)/MEM_CHUNK


extern uint32_t* kernel_page_dir;

struct mem_chunk
{
	uint16_t size;
	uint32_t* from;
	uint16_t chunks_used; /* Used when freeing */
	uint8_t status;
};

enum virtual_memory_constants {
  /* Main permission bits. */
  PRESENT = 1,
  READ_WRITE = 2,
  USER = 4,

  WRITE_THROUGH = 8,
  ACCESSED = 32,

  PAGE_DIRECTORY_BITS = 22,
  PAGE_TABLE_BITS = 12,
  PAGE_TABLE_MASK = 0x000003ff,
  PAGE_SIZE = 0x1000,
  PAGE_MASK = 0xfff,
};

struct allocation {
  int address;
  int size;
  struct allocation* next;
};

#define TABLE_INDEX(vaddr) ((vaddr >> PAGE_TABLE_BITS) & PAGE_TABLE_MASK)
#define DIRECTORY_INDEX(vaddr) ((vaddr >> PAGE_DIRECTORY_BITS) & PAGE_TABLE_MASK)

void init_memory();
void* kalloc(int size);
void print_memory_status();
void kfree(void* ptr);

void driver_mmap(uint32_t addr, int size);
void flush_tlb_entry(uint32_t vaddr);
void init_process_paging(struct pcb* pcb, char* data, int size);

int memory_permanent_usage();
int memory_permanent_total();
int memory_dynamic_total();
int memory_dynamic_usage();

int memory_pages_total();
int memory_pages_usage();

void load_page_directory();
void enable_paging();
void init_paging();

int memory_get_usage(char* name);
void memory_total_usage();

void* palloc(int size);

int memory_process_usage();
int memory_process_total();
void* malloc(int size);
void free(void* ptr);

#endif