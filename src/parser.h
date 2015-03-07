#ifndef PARSER_H
#define PARSER_H

#include "debug.h"
#include "command.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

command_t *parse(char*); //parse string read in 
void cmd_free(command_t*);

#endif
