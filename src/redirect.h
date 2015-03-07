#ifndef REDIRECT_H
#define REDIRECT_H

#include "debug.h"
#include "command.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

fdpair fd_open(command_t*);
int fd_close(fdpair);

#endif
