/**
 * @file process.c
 * @author Joe Bayer (joexbayer)
 * @brief Simple abstraction to easily add programs and their functions to the terminal.
 * @version 0.1
 * @date 2022-06-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <kthreads.h>
#include <terminal.h>
#include <pcb.h>

#define MAX_KTHREADS 10
static int total_kthreads = 0;

struct kthread {
    char name[pcb_max_name_length];
    void (*entry)();
};

struct kthread kthread_table[MAX_KTHREADS];

int register_kthread(void (*f)(), char* name)
{
    if(strlen(name)+1 > pcb_max_name_length)
        return -1;

    kthread_table[total_kthreads].entry = f;
    memcpy(kthread_table[total_kthreads].name, name, strlen(name)+1);
    total_kthreads++;

    return 0;
}

int start(char* name)
{
    for (int i = 0; i < total_kthreads; i++)
    {
        if(memcmp(name, kthread_table[i].name, strlen(kthread_table[i].name)) == 0){
            pcb_create_kthread(kthread_table[i].entry, kthread_table[i].name);
            return 0;
        }
    }

    return -1;

    
}

void empty();