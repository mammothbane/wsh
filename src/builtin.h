#ifndef BUILTIN_H
#define BUILTIN_H

#include "command.h"
#include "debug.h"
#include "job.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

extern const int BUILTIN_EXIT, 
  BUILTIN_CD,
  BUILTIN_OTHER,
  NOT_BUILTIN;

int builtin(command_t*);

#endif
