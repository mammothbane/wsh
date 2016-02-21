#ifndef PARSER_H
#define PARSER_H

#include "command.h"

command_t *parse(char*);   // parse command string into command_t 
void cmd_free(command_t*);

#endif
