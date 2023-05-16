#include <fs/fs.h>
#include <fs/inode.h>
#include <diskdev.h>
#include <terminal.h>
#include <pcb.h>
#include <fs/fs_error.h>
#include <ksyms.h>

/**
 * @brief Main API for filesystem 
 * Functions are exported through ksymbols.
 * No header file includes needed.
 */


/**
 * @brief Creates a new directory
 * 
 * @param argc 
 * @param argv 
 */
void mkdir(int argc, char* argv[])
{
    if(argc == 1){
        twritef("usage: mkdir <name>\n");
        return;
    }

    int ret = fs_create_directory(argv[1], current_running->current_directory);
    if(ret == -FS_ERR_INODE_MISSING){
        twritef("Unable to find current directory\n");
        return;
    }

    twritef("Created directory.\n");
}
EXPORT_KSYMBOL(mkdir);