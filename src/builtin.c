//idenfity and execute commands
//(c) 2015 nathan m perry

#include "parser.h"
#include "builtin.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const int NOT_BUILTIN = 0x0,
  BUILTIN_EXIT = 0x1,
  BUILTIN_CD = 0x2,
  BUILTIN_OTHER = 0x4;

int builtin(command_t *cmd) {
  //pre: cmd not null 
  char* nm = cmd->command[0];
  if (!strcmp(nm, "exit")) return BUILTIN_EXIT;
  else if (!strcmp(nm, "cd")) {
    return BUILTIN_CD;
  } else if (!strcmp(nm, "help")) {
    
    return BUILTIN_OTHER;
  } else if (!strcmp(nm, "jobs")) {
    
    return BUILTIN_OTHER;
  } else if (!strcmp(nm, "kill")) {
    
    return BUILTIN_OTHER;
  }
  else return NOT_BUILTIN;
}
