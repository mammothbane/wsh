#ifndef REDIRECT_H
#define REDIRECT_H

#include "command.h"

fdpair fd_open(command_t*);
void fd_close(fdpair);

#endif
