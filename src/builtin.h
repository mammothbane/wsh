#ifndef BUILTIN_H
#define BUILTIN_H


extern const int BUILTIN_EXIT, 
  BUILTIN_CD,
  BUILTIN_OTHER,
  NOT_BUILTIN;

#include "parser.h"

int builtin(command_t*);

#endif
