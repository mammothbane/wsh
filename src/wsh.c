// the williams shell
// (c) 2015 nathan m perry

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT "$- "

int main(int argc, char **argv) {
  char *line;
  command_t *tokens; //input split/tokenized
  while ((line = readline("- "))) {
    tokens = parse(line);  
    
    
    
  } 

  return 0;
}
