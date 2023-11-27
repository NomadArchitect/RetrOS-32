
#include <util.h>
#include <ksyms.h>
#include <serial.h>
#include <terminal.h>
#include <assert.h>

#define KSYMS_MAX_SYMBOLS 100
#define KSYMS_MAX_DEPTH 100
#define KSYMS_MAX_SYMBOL_LENGTH 25

static struct kernel_symbols {
    struct symbol_entry {
        char name[KSYMS_MAX_SYMBOL_LENGTH];
        uintptr_t addr;
    } symtable[KSYMS_MAX_SYMBOLS];
    
    int num_symbols;
} __ksyms = {
    .num_symbols = 0
};

void ksyms_add_symbol(const char* name, uintptr_t addr) {
    
    assert(strlen(name) < KSYMS_MAX_SYMBOL_LENGTH);

    if (__ksyms.num_symbols < KSYMS_MAX_SYMBOLS) {
        memcpy(__ksyms.symtable[__ksyms.num_symbols].name, name, strlen(name));
        __ksyms.symtable[__ksyms.num_symbols].addr = addr;
        dbgprintf("Added new symbol %s at 0x%x\n", name, addr);
        __ksyms.num_symbols++;
    } else {
        twrite("Error: symbol table full\n");
    }
}

/**
 * @brief Checks if there exists a kernel symbol with the given name.
 * 
 * @param name name to resolve
 * @return uintptr_t function pointer, NULL on error.
 */
uintptr_t ksyms_resolve_symbol(const char* name)
{
    ERR_ON_NULL(name);
    for (int i = 0; i < __ksyms.num_symbols; i++) {
        int ksym_namelen = strlen(__ksyms.symtable[i].name);
        int namelen = strlen(name);
        if(memcmp(name, __ksyms.symtable[i].name, namelen) == 0 && ksym_namelen == namelen){
            return __ksyms.symtable[i].addr;
        }
    }

    return NULL;
}

void backtrace(void) {
    uintptr_t* frame_ptr = __builtin_frame_address(0);
    uintptr_t return_addr;
    int depth = 0;

    dbgprintf("Backtrace:\n");
    while (frame_ptr && depth < KSYMS_MAX_DEPTH) {
        return_addr = *((uintptr_t*) (frame_ptr + 1));
        dbgprintf("searching for 0x%x\n", return_addr);
        if(return_addr == 0) break;
        if(return_addr > 0x100000) break; // TODO: fix this (it's a hack to prevent backtracing into user space)

        int best_index = -1;
        uintptr_t best_diff = (uintptr_t)-1; // Max possible value for uintptr_t
        for (int i = 0; i < __ksyms.num_symbols; i++) {
            if (__ksyms.symtable[i].addr <= return_addr) {
                uintptr_t diff = return_addr - __ksyms.symtable[i].addr;
                if (diff < best_diff) {
                    best_diff = diff;
                    best_index = i;
                }
            }
        }

        if (best_index != -1) {
            dbgprintf("%s: 0x%x - 0x%x = 0x%x\n", 
                      __ksyms.symtable[best_index].name, 
                      return_addr, 
                      __ksyms.symtable[best_index].addr, 
                      best_diff);
            twritef("%s\n", __ksyms.symtable[best_index].name);
        } else {
            dbgprintf("Unknown symbol: 0x%lx\n", return_addr);
        }
        
        frame_ptr = (uintptr_t*) (*frame_ptr);
        depth++;
    }
}
EXPORT_KSYMBOL(backtrace);

