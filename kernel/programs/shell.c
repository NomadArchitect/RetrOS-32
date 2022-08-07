/**
 * @file shell.c
 * @author Joe Bayer (joexbayer)
 * @brief Simple program handling input from user, mainly used to handles process management.
 * @version 0.1
 * @date 2022-06-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <pci.h>
#include <keyboard.h>
#include <screen.h>
#include <terminal.h>
#include <scheduler.h>
#include <pcb.h>
#include <process.h>
#include <io.h>

#include <windowmanager.h>
#include <net/dns.h>
#include <net/icmp.h>
#include <fs/fs.h>

#include <diskdev.h>


struct window w = {
	.anchor = 1,
	.height = SCREEN_HEIGHT-3,
	.width = SCREEN_WIDTH-3,
	.color = VGA_COLOR_LIGHT_BLUE
};

static uint8_t SHELL_POSITION =SCREEN_HEIGHT-3;
static const uint8_t SHELL_MAX_SIZE = 50;
static uint8_t shell_column = 3;
static char shell_buffer[50];
static uint8_t shell_buffer_length = 0;

static const char newline = '\n';
static const char backspace = '\b';

/*
 *	IMPLEMENTATIONS
 */
void shell_clear()
{
	for (size_t i = shell_column; i < SHELL_MAX_SIZE; i++)
	{
		scrput(i, SHELL_POSITION, ' ', VGA_COLOR_WHITE);
	}	
}

void reset_shell()
{
	memset(&shell_buffer, 0, 25);
	shell_column = strlen(current_process->name)+2;
	shell_buffer_length = 0;

	scrwrite(w.anchor+1, SHELL_POSITION, current_process->name, VGA_COLOR_LIGHT_CYAN);
	scrwrite(shell_column, SHELL_POSITION, "> ", VGA_COLOR_LIGHT_CYAN);
	shell_column += 1;

	screen_set_cursor(shell_column, SHELL_POSITION);
	shell_clear();
}

void exec_cmd()
{
	twritef("\n");
	for (int i = 0; i < current_process->total_functions; i++)
	{
		if(strncmp(current_process->functions[i].name, shell_buffer, strlen(current_process->functions[i].name))){
			current_process->functions[i].f();
			return;
		}
	}

	if(strncmp("help", shell_buffer, strlen("help"))){
		twriteln("HELP: ");
		twriteln("ls: see processes.");
		twriteln("lsf: see functions for process.");
		twriteln("switch $id: use process functions.");
		twriteln("start $id: start a process.");
		twriteln("stop $id: stop a process.");
		return;
	}
	
	if(strncmp("lsi", shell_buffer, strlen("lsi"))){
		list_instances();
		return;
	}

	if(strncmp("lsf", shell_buffer, strlen("lsf"))){
		list_functions();
		return;
	}

	if(strncmp("switch", shell_buffer, strlen("switch"))){
		int id = atoi(shell_buffer+strlen("switch")+1);
		switch_process(id);
		return;
	}

	if(strncmp("lspci", shell_buffer, strlen("lspci"))){
		list_pci_devices();
		return;
	}

	if(strncmp("ls", shell_buffer, strlen("ls"))){
		ls("");
		return;
	}

	if(strncmp("clear", shell_buffer, strlen("clear"))){
		scr_clear();
	}

	if(strncmp("stop", shell_buffer, strlen("stop"))){
		int id = atoi(shell_buffer+strlen("stop")+1);
		stop_task(id);
	}

	if(strncmp("start", shell_buffer, strlen("start"))){
		int id = atoi(shell_buffer+strlen("stop")+1);
		start_process(id);
	}

	if(strncmp("dig", shell_buffer, strlen("dig"))){
		char* hostname = shell_buffer+strlen("dig")+1;
		hostname[strlen(hostname)-1] = 0;
		gethostname(hostname);
	}

	if(strncmp("cat", shell_buffer, strlen("cat"))){
		char* name = shell_buffer+strlen("cat")+1;
		inode_t inode = open(name);
		file_read(inode);
		file_close(inode);
	}

	if(strncmp("ping", shell_buffer, strlen("ping"))){
		char* hostname = shell_buffer+strlen("ping")+1;
		hostname[strlen(hostname)-1] = 0;
		ping(hostname);
	}

	if(strncmp("touch", shell_buffer, strlen("touch"))){
		char* hostname = shell_buffer+strlen("touch")+1;
		hostname[strlen(hostname)-1] = 0;
		create_file(hostname);
	}

	if(strncmp("ps", shell_buffer, strlen("ps"))){
		print_pcb_status();
	}

	if(strncmp("fdisk", shell_buffer, strlen("fdisk"))){
		print_dev_status();
	}

	if(strncmp("sync", shell_buffer, strlen("sync"))){
		sync();
	}

	if(strncmp("exit", shell_buffer, strlen("exit"))){
		sync();
		outportw(0x604, 0x2000);
	}

	if(strncmp("exit", shell_buffer, strlen("exit"))){
		sync();
		outportw(0x604, 0x2000);
	}

	if(strncmp("cd", shell_buffer, strlen("cd"))){
		char* name = shell_buffer+strlen("cd")+1;
		name[strlen(name)-1] = 0;
		chdir(name);
	}

	if(strncmp("mkdir", shell_buffer, strlen("mkdir"))){
		char* name = shell_buffer+strlen("mkdir")+1;
		name[strlen(name)-1] = 0;
		mkdir(name);
	}


	//twrite(shell_buffer);
}

/**
 * @brief Puts a character c into the shell line 
 * at correct position. Also detects enter.
 * 
 * @param c character to put to screen.
 */
void shell_put(char c)
{
	unsigned char uc = c;
	if(uc == newline)
	{
		shell_buffer[shell_buffer_length] = newline;
		shell_buffer_length++;
		exec_cmd();
		reset_shell();
		return;
	}

	if(uc == backspace)
	{
		if(shell_column < 1)
			return;
		shell_column -= 1;
		scrput(shell_column, SHELL_POSITION, ' ', VGA_COLOR_WHITE);
		shell_buffer[shell_buffer_length] = 0;
		shell_buffer_length--;
		screen_set_cursor(shell_column-1, SHELL_POSITION);
		return;
	}

	if(shell_column == SHELL_MAX_SIZE)
	{
		return;
	}
	scrput(shell_column, SHELL_POSITION, uc, VGA_COLOR_WHITE);
	shell_buffer[shell_buffer_length] = uc;
	shell_buffer_length++;
	screen_set_cursor(shell_column, SHELL_POSITION);
	shell_column++;
}

void shell_main()
{
	attach_window(w);
	reset_shell();
	sleep(2);
	while(1)
	{
		char c = kb_get_char();
		if(c == -1)
			continue;
		shell_put(c);
	}
}

PROGRAM(shell, &shell_main)
reset_shell();
PROGRAM_END