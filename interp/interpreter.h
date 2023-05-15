#ifndef FCB4F955_2425_46A5_9A2F_B11453605E94
#define FCB4F955_2425_46A5_9A2F_B11453605E94

//#define DEBUG

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#ifdef DEBUG
#define DEBUG_PRINT(fmt, ...) \
    printf("[DEBUG] " fmt, ##__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...)
#endif

/* 32kb input file buffer */
#define POOLSIZE 32*1024

/* 96kb text section */
#define VM_TEXT_SIZE 96*1024
/* 3kb data section */
#define VM_DATA_SIZE 3*1024
/* 1kb stack section */
#define VM_STACK_SIZE 1024

/* Total 132kb total memory */

/* 128 symbols */
#define LEX_MAX_SYMBOLS 128

#endif /* FCB4F955_2425_46A5_9A2F_B11453605E94 */