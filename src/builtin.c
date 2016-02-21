// builtin commands
// (c) 2015-2016 Nathan M. Perry

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "builtin.h"
#include "debug.h"
#include "job.h"

const int 
	NOT_BUILTIN = 0x0,
	BUILTIN_EXIT = 0x1,
	BUILTIN_CD = 0x2,
	BUILTIN_OTHER = 0x4;

// try to parse the command as a builtin, returning any of BUILTIN_EXIT,
// BUILTIN_CD, BUILTIN_OTHER, and NOT_BUILTIN depending on how it matches.
int builtin(command_t *cmd) {
	char* nm = cmd->command[0];

	if (!strcmp(nm, "exit")) {
		return BUILTIN_EXIT;

	} else if (!strcmp(nm, "cd")) {
		return BUILTIN_CD;

	} else if (!strcmp(nm, "help")) {
		puts("builtin commands:\n\thelp\tthis help page");
		puts("\tjobs\tlist all running jobs");
		puts("\tkill\tkill a job");
		puts("\tcd\tchange directory");
		puts("\texit\texit the shell");  
		return BUILTIN_OTHER;

	} else if (!strcmp(nm, "jobs")) {
		jt_print();
		return BUILTIN_OTHER;

	} else if (!strcmp(nm, "kill")) {
		jb_kill(atoi(cmd->command[1]));
		return BUILTIN_OTHER;
	}
	else return NOT_BUILTIN;
}
