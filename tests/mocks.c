#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <time.h>
#include <sync.h>

#include <fs/fs.h>
#include <fs/inode.h>
#include <fs/superblock.h>
#include <fs/directory.h>


#define DEBUG 0
#define DISKSIZE 1000000

extern FILE* filesystem;

int get_current_time(struct time* time_s){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    time_s->year = tm.tm_year;
    time_s->month = tm.tm_mon;
    time_s->day = tm.tm_mday;
    time_s->hour = tm.tm_hour;
    time_s->minute = tm.tm_min;
    time_s->second = tm.tm_sec;

    return 0;
}

void _start_pcb()
{
    
}

void spin_lock(spinlock_t* lock) {
}

void spin_unlock(spinlock_t* lock) {
}


void mutex_init(mutex_t* l)
{

}

void acquire(mutex_t* l)
{

}

void release(mutex_t* l)
{

}

int disk_size()
{
    return DISKSIZE;
}

uint32_t serial_printf(char* fmt, ...)
{
    if(DEBUG) {
            va_list argptr;
            va_start(argptr, fmt);
            vfprintf(stderr, fmt, argptr);
            va_end(argptr);
        }
    return 1;
}


void kfree(void* ptr)
{
    free(ptr);
}

/* Functions needed for inode and bitmap to work. */

/* Functions needed for inode and bitmap to work. */
int32_t twriteln(char* fmt, ...)
{
    if(DEBUG) {
        va_list argptr;
        va_start(argptr, fmt);
        vfprintf(stderr, fmt, argptr);
        va_end(argptr);
    }

    return 0;
}

int32_t twritef(char* fmt, ...)
{
    if(DEBUG) {
        va_list argptr;
        va_start(argptr, fmt);
        vfprintf(stderr, fmt, argptr);
        va_end(argptr);
    };
    return 0;
}

void* kalloc(int size){
    return malloc(size);
}

/* Functions simulating the disk device read / write functions. */
int read_block(char* buf, int block)
{
    fseek(filesystem, block*512, SEEK_SET);
    int ret = fread(buf, 1, 512, filesystem);
    if(ret <= 0)
        return 0;
    return 1;
}

int write_block(char* buf, int block)
{
    fseek(filesystem, block*512, SEEK_SET);
    fwrite(buf, 1, 512, filesystem);
    return 1;
}

int write_block_offset(char* usr_buf, int size, int offset, int block)
{
    char buf[512];
    read_block(buf, block);
    memcpy(&buf[offset], usr_buf, size);

    return write_block(buf, block);
}

int read_block_offset(char* usr_buf, int size, int offset, int block)
{
    char buf[512];
    read_block((char*)buf, block);
    memcpy(usr_buf, &buf[offset], size);

    return 1;   
}