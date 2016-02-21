// main program
// (c) 2015-2016 Nathan M. Perry

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#include "job.h"
#include "parser.h"
#include "command.h"
#include "redirect.h"
#include "builtin.h"
#include "executor.h"
#include "debug.h"

#define PROMPT "$ - "

int cpid = 0;

// interrupt handler for SIGINT
static void catch_int();
struct sigaction intr = { .sa_handler = catch_int };

int main(int argc, char **argv) {
	sigaction(SIGINT, &intr, NULL);

	// initialize the job table
	jt_init();

	char *line;
	command_t *list;

	// parse each line of input
	while ((line = readline(PROMPT))) {
		list = parse(line);  
		if (list && list->command) {
			do {
				int bi = builtin(list);
				if (bi == BUILTIN_EXIT) {
					exit((list->command[1] ? atoi(list->command[1]) : 0));
				} else if (bi == BUILTIN_CD) {
					
				} else if (bi == BUILTIN_OTHER) {
					
				} else {
					list = execute(list);
					cpid = 0;
				}

				if (list->next) list = list->next;
				else break;
			} while (1);
		}
		jt_update();
	} 
	jt_free();
	return 0;
}

void catch_int() {
	debug_print("caught an interrupt. terminating process %d if it exists\n", cpid);
	if (cpid) {
		if (kill(cpid, SIGINT) < 0) {
			perror("ctrl-c");
		}
	}
}
