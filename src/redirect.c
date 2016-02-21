// handle file creation and redirection
// (c) 2015-2016 Nathan M. Perry

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "redirect.h"

/**
 * Open out for writing in truncate mode if it exists.
 * Open in for reading if it exists.
 * Return both file descriptors.
 */
fdpair fd_open(command_t *cmd) {
	int in = -1, out = -1;
	if (cmd->in) { 
		in = open(cmd->in, O_RDONLY);
		if (in < 0) {
			perror("error reading input");
			exit(EXIT_FAILURE);
		}
	}
	if (cmd->out) {
		out = open(cmd->out, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
		if (out < 0) {
			perror("error writing output");
			exit(EXIT_FAILURE);
		}
	}
	return (fdpair){in, out};
}

/**
 * Close both files if they exist.
 */
void fd_close(fdpair pair) {
	int err = 0;
	if (pair.in >= 0) {
		err = close(pair.in);
		if (err) {
			perror("error closing input");
			exit(EXIT_FAILURE);
		}
	}
	if (pair.out >= 0) {
		err = close(pair.out);
		if (err) {
			perror("error closing output");
			exit(EXIT_FAILURE);
		}
	}
}
