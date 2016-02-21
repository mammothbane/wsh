#ifndef BUILTIN_H
#define BUILTIN_H

#include "command.h"

extern const int BUILTIN_EXIT, 
  BUILTIN_CD,
  BUILTIN_OTHER,
  NOT_BUILTIN;

int builtin(command_t*);

#endif
