#ifndef PCB_H
#define PCB_H

#include <util.h>

enum {
    RUNNING = 1
};

struct pcb_t {
      uint32_t ebp;
      uint32_t esp;
      uint32_t eip;
      uint32_t fpu[32];
      uint8_t running;

      struct pcb_t *next;
}__attribute__((__packed__));
typedef struct pcb_t pcb_t;

extern pcb_t* current_running;
void context_switch();
void init_pcbs();

#endif