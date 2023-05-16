#include <windowmanager.h>
#include <util.h>
#include <pci.h>
#include <terminal.h>
#include <keyboard.h>
#include <arch/interrupts.h>
#include <timer.h>
#include <screen.h>
#include <pcb.h>
#include <memory.h>
#include <net/skb.h>
#include <net/arp.h>
#include <ata.h>
#include <bitmap.h>
#include <net/socket.h>
#include <net/dns.h>
#include <fs/fs.h>
#include <serial.h>
#include <syscall_helper.h>
#include <syscalls.h>
#include <kthreads.h>
#include <scheduler.h>
#include <vbe.h>
#include <mouse.h>
#include <ipc.h>
#include <assert.h>
#include <arch/io.h>
#include <work.h>
#include <arch/gdt.h>
#include <kutils.h>

#include <virtualdisk.h>

#include <gfx/window.h>
#include <gfx/composition.h>
#include <gfx/api.h>

#include <multiboot.h>

#define USE_MULTIBOOT 0

/* This functions always needs to be on top? */
void kernel(uint32_t magic) 
{
	asm ("cli");

#if USE_MULTIBOOT
  	struct multiboot_info* mb_info = (struct multiboot_info*) magic;
	vbe_info->height = mb_info->framebuffer_height;
	vbe_info->width = mb_info->framebuffer_width;
	vbe_info->bpp = mb_info->framebuffer_bpp;
	vbe_info->pitch = mb_info->framebuffer_width;
	vbe_info->framebuffer = mb_info->framebuffer_addr;
    init_serial();
#else
	vbe_info = (struct vbe_mode_info_structure*) magic;
#endif
	//init_serial();
	vesa_printf(vbe_info->framebuffer, 10, 10, 15, "Booting OS...");
	/* Clear memory and BSS */
	//memset((char*)_bss_s, 0, (unsigned int) _bss_size);
    memset((char*)0x100000, 0, 0x800000-0x100000);
	CLI();

	kernel_size = _end-_code;
	init_memory();

	dbgprintf("Kernel is at: 0x%x\n", magic);
	dbgprintf("Kernel is at: 0x%x\n", kernel);

	dbgprintf("[VBE] INFO:\n");
	dbgprintf("[VBE] Height: %d\n", vbe_info->height);
	dbgprintf("[VBE] Width: %d\n", vbe_info->width);
	dbgprintf("[VBE] Pitch: %d\n", vbe_info->pitch);
	dbgprintf("[VBE] Bpp: %d\n", vbe_info->bpp);
	dbgprintf("[VBE] Memory Size: %d (0x%x)\n", vbe_info->width*vbe_info->height*(vbe_info->bpp/8), vbe_info->width*vbe_info->height*(vbe_info->bpp/8));
	//vmem_map_driver_region(vbe_info->framebuffer, (vbe_info->width*vbe_info->height*(vbe_info->bpp/8))+1);
	
	init_kctors();

	//vga_set_palette();

	init_interrupts();
	gfx_init();
	init_keyboard();
	mouse_init();
	init_pcbs();
	ipc_msg_box_init();
	init_pci();
	init_worker();

	init_arp();
	init_sockets();
	init_dns();

	if(!disk_attached()){
		dbgprintf("[KERNEL] Attaching virtual disk because not physical one was found.\n");
		virtual_disk_attach();
		//mkfs();
	}
	init_fs();

	register_kthread(&Genesis, "Genesis");
	register_kthread(&networking_main, "netd");
	register_kthread(&dhcpd, "dhcpd");
	register_kthread(&gfx_compositor_main, "wind");
	register_kthread(&error_main, "Error");
	register_kthread(&idletask, "idled");
	register_kthread(&dummytask, "Dummy");
	register_kthread(&worker_thread, "workd");
	register_kthread(&tcpd, "tcpd");

	#pragma GCC diagnostic ignored "-Wcast-function-type"
	add_system_call(SYSCALL_PRTPUT, (syscall_t)&terminal_putchar);
	add_system_call(SYSCALL_EXIT, (syscall_t)&kernel_exit);
	add_system_call(SYSCALL_SLEEP, (syscall_t)&kernel_sleep);
	add_system_call(SYSCALL_GFX_WINDOW, (syscall_t)&gfx_new_window);
	add_system_call(SYSCALL_GFX_GET_TIME,  (syscall_t)&get_current_time);
	add_system_call(SYSCALL_GFX_DRAW, (syscall_t)&gfx_syscall_hook);
	add_system_call(SYSCALL_GFX_SET_TITLE, (syscall_t)&kernel_gfx_set_title);


	add_system_call(SYSCALL_FREE, (syscall_t)&free);
	add_system_call(SYSCALL_MALLOC, (syscall_t)&malloc);

	add_system_call(SYSCALL_OPEN, (syscall_t)&fs_open);
	add_system_call(SYSCALL_READ, (syscall_t)&fs_read);
	add_system_call(SYSCALL_WRITE, (syscall_t)&fs_write);
	add_system_call(SYSCALL_CLOSE, (syscall_t)&fs_close);
	#pragma GCC diagnostic pop
	

	dbgprintf("[KERNEL] TEXT: %d\n", _code_end-_code);
	dbgprintf("[KERNEL] RODATA: %d\n", _ro_e-_ro_s);
	dbgprintf("[KERNEL] DATA: %d\n", _data_e-_data_s);
	dbgprintf("[KERNEL] BSS: %d (0x%x)\n", _bss_e-_bss_s, _bss_s);
	dbgprintf("[KERNEL] Total: %d (%d sectors)\n", _end-_code, ((_end-_code)/512)+2);
	dbgprintf("[KERNEL] Kernel reaching too: 0x%x\n", _end-_code);

	load_page_directory(kernel_page_dir);
	init_gdt();
	init_tss();
	enable_paging();

	dbgprintf("[KERNEL] Enabled paging!\n");
	
	vesa_init();

	start("idled");
	start("workd");
	//start("workd");
	start("wind");
	//start("netd");
  	start("kclock");
	start("shell");
	
	//pcb_create_process("/bin/clock", 0, NULL);
	
	init_pit(1);

	dbgprintf("[CLI] %d\n", cli_cnt);

	pcb_start();
	
	UNREACHABLE();
}

void init_kctors()
{
    int symbols = ((int)_kctor_table_size)/4;
    dbgprintf("%d total kernel constructors\n", symbols);

    unsigned int* __address = (unsigned int*)_start_kctor_table;
    for (int i = 0; i < symbols; i++){
        void (*__func)() = (void (*)()) *__address;
        __func();
        __address++;
    }
}

#define HEXDUMP_COLS 8
void hexdump(const void *data, int size)
{
    const unsigned char *p = (const unsigned char *)data;
    int i, j;

    for (i = 0; i < size; i += HEXDUMP_COLS) {
        twritef("%p: ", i);

        for (j = 0; j < HEXDUMP_COLS; j++) {
            if (i + j < size)
                twritef("%s%x ", p[i + j] < 16 ? "0" : "", p[i + j]);
            else
                twritef("   ");
            if (j % 8 == 7)
                twritef(" ");
        }
        twritef(" ");

        for (j = 0; j < HEXDUMP_COLS; j++) {
            if (i + j < size)
                twritef("%c", (p[i + j] >= 32 && p[i + j] <= 126) ? p[i + j] : '.');
            else
                twritef(" ");
        }
        twritef("\n");
    }
}