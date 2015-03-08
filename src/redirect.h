#ifndef REDIRECT_H
#define REDIRECT_H

#include "debug.h"
#include "command.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

fdpair fd_open(command_t*);
void fd_close(fdpair);

#endif
