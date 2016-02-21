#ifndef PARSER_H
#define PARSER_H

#include "debug.h"
#include "command.h"

command_t *parse(char*); //parse string read in 
void cmd_free(command_t*);

/*
Command flags
PS_FG    foreground
PS_BG    background
PS_PIPE  out piped to another command
PS_IN    has in redirect
PS_OUT   has out redirect
*/
const char 
	PS_FG = 0x0,
  	PS_BG = 0x1,
  	PS_PIPE = 0x2,
  	PS_IN = 0x4,
  	PS_OUT = 0x8;

#endif
