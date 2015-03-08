#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "command.h"
#include "debug.h"
#include "redirect.h"

int execute(command_t*);

#endif
