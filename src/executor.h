#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "command.h"
#include "debug.h"
#include "redirect.h"
#include "job.h"

command_t* execute(command_t*);

#endif
