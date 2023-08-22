/**
 * @file fat16.c
 * @author Joe Bayer (joexbayer)
 * @brief Main API for the FAT16 Filesystem.
 * @version 0.1
 * @date 2023-05-31
 * @see http://www.tavi.co.uk/phobos/fat.html
 * @see https://wiki.osdev.org/FAT
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdint.h>
#include <fs/fat16.h>
#include <kutils.h>
#include <diskdev.h>
#include <memory.h>

static struct fat_boot_table boot_table = {0};
static byte_t* fat_table_memory = NULL;  /* pointer to the in-memory FAT table */

/* HELPER FUNCTIONS */

uint16_t get_fat_start_block()
{
    return BOOT_BLOCK + 1;  /* FAT starts right after the boot block */
}

uint16_t get_root_directory_start_block()
{
    return get_fat_start_block() + boot_table.fat_blocks;  /* Root directory starts after FAT */
}

uint16_t fat16_get_fat_entry(uint32_t cluster)
{
    if(fat_table_memory == NULL){
        return -1;
    }

    uint32_t fat_offset = cluster * 2;  /* Each entry is 2 bytes */
    return *(uint16_t*)(fat_table_memory + fat_offset);
}

void fat16_set_fat_entry(uint32_t cluster, uint16_t value)
{
    if(fat_table_memory == NULL){
        return;
    }

    uint32_t fat_offset = cluster * 2;  /* Each entry is 2 bytes */
    *(uint16_t*)(fat_table_memory + fat_offset) = value;
}

void fat16_sync_fat_table()
{
    if(fat_table_memory == NULL){
        return;
    }

    int start_block = get_fat_start_block();
    for (uint16_t i = 0; i < boot_table.fat_blocks; i++) {
        write_block(fat_table_memory + i * 512, start_block + i);
    }
}

/* wrapper functions TODO: inline replace */
void fat16_allocate_cluster(uint32_t cluster)
{
    fat16_set_fat_entry(cluster, 0xFFFF);  /* marking cluster as end of file */
}

void fat16_free_cluster(uint32_t cluster)
{
    fat16_set_fat_entry(cluster, 0x0000);  /* marking cluster as free */
}

uint32_t fat16_get_free_cluster()
{
    for (int i = 2; i < 65536; i++) {  /* Start from 2 as 0 and 1 are reserved entries */
        if (fat16_get_fat_entry(i) == 0x0000) {

            fat16_allocate_cluster(i);
            return i;
        }
    }
    return 0;  /* no free cluster found */
}

/**
 * Writes (synchronizes) a directory entry back to the root directory of the FAT16 filesystem.
 *
 * @param index: The index of the directory entry to be updated.
 * @param entry: Pointer to the directory entry data to be written.
 * @return 0 on success, negative value on error.
 */
static int fat16_sync_root_directory_entry(uint32_t index, const struct fat16_directory_entry* entry)
{
    if(index >= boot_table.root_dir_entries)
        return -1;  /* index out of range */

    uint16_t block_num = get_root_directory_start_block() + (index / ENTRIES_PER_BLOCK);
    byte_t buffer[512];

    /* Read the block containing the directory entry to be updated */
    if(read_block(buffer, block_num) < 0){
        dbgprintf("Error reading block\n");
        return -2;  /* error reading block */
    }

    /* Copy the provided directory entry to the correct position in the buffer */
    memcpy(&buffer[(index % ENTRIES_PER_BLOCK) * sizeof(struct fat16_directory_entry)], entry, sizeof(struct fat16_directory_entry));

    /* Write the updated block back to the disk */
    if(write_block(buffer, block_num) < 0) {
        dbgprintf("Error writing block\n");
        return -3;  /* error writing block */
    }

    return 0;  /* success */
}

/**
 * Read a root directory entry by index.
 * @param index The index of the root directory entry.
 * @param entry_out Pointer to the destination struct where the entry should be copied.
 * @return 0 on success, or a negative value on error.
 */
static int fat16_read_root_directory_entry(uint32_t index, struct fat16_directory_entry* entry_out)
{
    if(index >= boot_table.root_dir_entries)
        return -1;  /* index out of range */

    uint16_t block_num = get_root_directory_start_block() + (index / ENTRIES_PER_BLOCK);
    byte_t buffer[512];
    if(read_block(buffer, block_num) < 0){
        dbgprintf("Error reading block\n");
        return -2;  /* error reading block */
    }

    struct fat16_directory_entry* dir_entry = (struct fat16_directory_entry*)(buffer + index * sizeof(struct fat16_directory_entry));

    /* Copy the directory entry to the output */
    memcpy(entry_out, &buffer[(index % ENTRIES_PER_BLOCK) * sizeof(struct fat16_directory_entry)], sizeof(struct fat16_directory_entry));
    
    return 0;  /* success */
}

/**
 * @brief 
 * 
 * @param filename 
 * @param ext 
 * @param entry_out 
 * @return int index of directory
 */
static int fat16_find_file_entry(const char *filename, const char* ext, struct fat16_directory_entry* entry_out)
{
    /* Search the root directory for the file. */
    for (int i = 0; i < boot_table.root_dir_entries; i++) {
        struct fat16_directory_entry entry;

        fat16_read_root_directory_entry(i, &entry);
        if (memcmp(entry.filename, filename, 8) == 0 && memcmp(entry.extension, ext, 3) == 0) {
            if (entry_out) {
                *entry_out = entry;
            }
            return i;  /* Found */
        }
    }
    return -1;  /* Not found */
}

/**
 * Adds a new root directory entry.
 * @param filename The name of the file (up to 8 characters, not including the extension).
 * @param extension The file extension (up to 3 characters).
 * @param attributes Attributes for the file (read-only, hidden, system, etc.).
 * @param start_cluster The first cluster of the file.
 * @param file_size The size of the file in bytes.
 * @return 0 on success, or a negative value on error.
 */
int fat16_add_root_directory_entry(const char *filename, const char *extension, byte_t attributes, uint16_t start_cluster, uint32_t file_size)
{
    uint16_t root_start_block = get_root_directory_start_block();
    uint16_t root_blocks = (boot_table.root_dir_entries * sizeof(struct fat16_directory_entry)) / 512;

    byte_t buffer[512];

    for (uint16_t block = 0; block < root_blocks; block++) {
        read_block(buffer, root_start_block + block);

        for (int entry = 0; entry < ENTRIES_PER_BLOCK; entry++) {
            struct fat16_directory_entry* dir_entry = (struct fat16_directory_entry*)(buffer + entry * sizeof(struct fat16_directory_entry));

            if (dir_entry->filename[0] == 0x00 || dir_entry->filename[0] == 0xE5) {  /* empty or deleted entry */
                /* Fill in the directory entry */
                memset(dir_entry, 0, sizeof(struct fat16_directory_entry));  /* Clear the entry */
                memcpy(dir_entry->filename, filename, 8);
                memcpy(dir_entry->extension, extension, 3);
                dir_entry->attributes = attributes;
                dir_entry->first_cluster = start_cluster;
                dir_entry->file_size = file_size;

                /* Write the block back to disk */
                write_block(buffer, root_start_block + block);
                return 0;  /* success */
            }
        }
    }

    return -1;  /* no empty slot found in the root directory */
}

int fat16_read_file(const char *filename, const char* ext, void *buffer, int buffer_length)
{
    struct fat16_directory_entry entry;
    int find_result = fat16_find_file_entry(filename, ext, &entry);
    if (find_result < 0) {
        dbgprintf("File not found\n");
        return -1;
    }  /* File not found */

    int ret = fat16_read(&entry, 0, buffer, buffer_length);
    return ret;  /* Return bytes read */
}

int fat16_create_file(const char *filename, const char* ext, const void *data, int data_length)
{
    int first_cluster = fat16_get_free_cluster();  
    struct fat16_directory_entry entry = {
        .first_cluster = first_cluster,
    };

    fat16_write(&entry, 0, data, data_length);


    fat16_add_root_directory_entry(filename, ext, 0x20, first_cluster, data_length);
    fat16_sync_fat_table();

    return 0;  /* Success */
}

void fat16_print_root_directory_entries()
{
    for (int i = 0; i < boot_table.root_dir_entries; i++) {
        struct fat16_directory_entry entry;
        struct fat16_directory_entry* dir_entry = &entry;

        fat16_read_root_directory_entry(i, &entry);
        /* Check if the entry is used (filename's first byte is not 0x00 or 0xE5) */
        if (dir_entry->filename[0] != 0x00 && dir_entry->filename[0] != 0xE5) {
            /* Print the filename (you might need to format it further depending on your needs) */
            char name[9];
            memcpy(name, dir_entry->filename, 8);
            name[8] = '\0';

            char extension[4];
            memcpy(extension, dir_entry->extension, 3);
            extension[3] = '\0';

            /* print detailed info about the entry */
            dbgprintf("Filename: %s.%s (%d bytes) Attributes: 0x%x Cluster: %d %s\n", name, extension, dir_entry->file_size, dir_entry->attributes, dir_entry->first_cluster, dir_entry->attributes & 0x10 ? "<DIR>" : "");
        }
    }
}

int fat16_format()
{
    int total_blocks = disk_size()/512;

    struct fat_boot_table new_boot_table = {
        .manufacturer = "NETOS   ",  /* This can be any 8-character string */
        .bytes_per_plock = 512,      /* Standard block size */
        .blocks_per_allocation = 1,  /* Usually 1 for small devices */
        .reserved_blocks = 1,        /* The boot block */
        .num_FATs = 1,               /* Standard for FAT16 */
        .root_dir_entries = 32,     /* This means the root directory occopies 2 blocks TODO: Currently hardcoded*/
        .total_blocks = total_blocks,
        .media_descriptor = 0xF8,    /* Fixed disk  */
        .fat_blocks = FAT_BLOCKS,
        /* ... other fields ... */
        .file_system_identifier = "FAT16   "
    };

    /* dbgprint out bootblock information: */
    dbgprintf("bootblock information:\n");
    dbgprintf("manufacturer: %s\n", new_boot_table.manufacturer);
    dbgprintf("bytes_per_plock: %d\n", new_boot_table.bytes_per_plock);
    dbgprintf("blocks_per_allocation: %d\n", new_boot_table.blocks_per_allocation);
    dbgprintf("reserved_blocks: %d\n", new_boot_table.reserved_blocks);
    dbgprintf("num_FATs: %d\n", new_boot_table.num_FATs);
    dbgprintf("root_dir_entries: %d\n", new_boot_table.root_dir_entries);
    dbgprintf("total_blocks: %d\n", new_boot_table.total_blocks);
    dbgprintf("media_descriptor: %d\n", new_boot_table.media_descriptor);
    dbgprintf("fat_blocks: %d\n", new_boot_table.fat_blocks);
    dbgprintf("file_system_identifier: %s\n", new_boot_table.file_system_identifier);

    /* Update the boot table */
    boot_table = new_boot_table;

    /* Write the boot table to the boot block */
    write_block((byte_t* )&new_boot_table, BOOT_BLOCK);

    /* Clear out the FAT tables */
    byte_t zero_block[512];
    memset(zero_block, 0, sizeof(zero_block));
    for (uint16_t i = 0; i < new_boot_table.fat_blocks; i++) {
        write_block((byte_t*) zero_block, get_fat_start_block() + i);
        /* We don't need the line for FAT2 anymore. */
    }

    /* Clear out the root directory area */
    for (uint16_t i = 0; i < new_boot_table.root_dir_entries * 32 / 512; i++) {
        write_block(zero_block, get_root_directory_start_block() + i);
    }

    /* Load FAT table into memory. */
    fat_table_memory = (byte_t*)kalloc((boot_table.fat_blocks * 512));  /* Allocate memory for the FAT table */
    for (uint16_t i = 0; i < boot_table.fat_blocks; i++) {
        read_block(fat_table_memory + i * 512, get_fat_start_block() + i);
    }

    return 0;  /* assume success */
}


void fat16_set_time(uint16_t *time, ubyte_t hours, ubyte_t minutes, ubyte_t seconds)
{
    /* Clear the existing time bits */
    *time &= 0xFC00;
    /* Set the hours bits */
    *time |= (hours & 0x1F) << 11;
    /* Set the minutes bits */
    *time |= (minutes & 0x3F) << 5;

    /* Set the seconds bits (converted to two-second periods) */
    ubyte_t twoSecondPeriods = seconds / 2;
    *time |= twoSecondPeriods & 0x1F;
}

void fat16_set_date(uint16_t *date, uint16_t year, ubyte_t month, ubyte_t day)
{
    /* Clear the existing date bits */
    *date &= 0xFE00;
    /* Set the year bits (offset from 1980) */
    *date |= ((year - 1980) & 0x7F) << 9;
    /* Set the month bits */
    *date |= (month & 0x0F) << 5;
    /* Set the day bits */
    *date |= (day & 0x1F);
}

int fat16_initialize()
{
    /* load the bootblock */

    return -1;
}

/* Open a file. Returns a file descriptor or a negative value on error. */
int fat16_open(const char *path);

/* Close an open file. Returns 0 on success, and a negative value on error. */
int fat16_close(int fd);

/* Create a new directory. Returns 0 on success, and a negative value on error. */
int fat16_mkdir(const char *path);

/* Delete a file or directory. Returns 0 on success, and a negative value on error. */
int fat16_remove(const char *path);

/* List the contents of a directory. */
int fat16_listdir(const char *path, void (*callback)(const char *name, int is_directory));


/* Blocks before ROOT directory: (size of FAT)*(number of FATs) + 1 */