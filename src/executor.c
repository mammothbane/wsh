// run standard commands
// (c) 2015-2016 Nathan M. Perry

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include "debug.h"
#include "redirect.h"
#include "job.h"
#include "executor.h"

static command_t* execute_internal(command_t*, int, int);

// execute the given command 
command_t* execute(command_t *command) {
	return execute_internal(command, 0, 0); 
}

/**
 * fdin and parent are used for recursive calls. set to 0 externally.
 * parent indicates whether this call is recursive. fdin is the file
 * descriptor that the command should read from (for use with pipes).
 * returns the last command processed.
 */
command_t* execute_internal(command_t *command, int fdin, int parent) {
	debug_print("in file descriptor is %d\n", fdin);

	int fdpipe[2];
	command_t* ret = command;

	while (ret->next && (ret->ps_type & PS_PIPE)) ret = ret->next;
	fdpair pair;

	pid_t pid = fork();

	// we're the child
	if (!pid) {
		debug_print("[%s:%d] read: %d, write: %d, next: %p\n", command->command[0], getpid(), fdpipe[0], fdpipe[1], command->next);
		
		//call piped command recursively if necessary
		if (command->next && (command->ps_type & PS_PIPE)) { 
			pipe(fdpipe);
			debug_print("pipe: %s[%d] -> [%d]%s\n", command->command[0], fdpipe[1], fdpipe[0], command->next->command[0]);
			execute_internal(command->next, fdpipe[0], 1);
		}

		// set up file descriptors
		pair = fd_open(command);
		if (fdpipe[1]) {
			close(pair.out);
			pair.out = fdpipe[1];
		}

		if (fdin) {
			close(pair.in);
			pair.in = fdin;
		}

		debug_print("[%s] in: %d, out: %d\n", command->command[0], pair.in, pair.out);
		if (pair.in >= 0) dup2(pair.in, 0);
		if (pair.out >= 0) dup2(pair.out, 1);

		//execute the command
		debug_print("child %d spawned\n", getpid());
		debug_print("executing %s\n", command->command[0]);
		
		execvp(command->command[0], command->command);

		if (errno == 2) fprintf(stderr, "%s: command not found.\n", command->command[0]);
		else perror(NULL);
		
		exit(EXIT_FAILURE); 
	
	// fork failed
	} else if (pid < 0) { 
		perror(NULL);
		exit(EXIT_FAILURE);

	// we're in the parent
	} else {
		if (!parent) {
			if (command->ps_type & PS_BG) {
				jb_create(command->command[0], pid);
			} else {
				cpid = pid;
				wait(NULL);
			}
		}
		return ret;
	}
}
