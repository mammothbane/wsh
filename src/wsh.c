// the williams shell
// (c) 2015 nathan m perry

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT "$- "

int main(int argc, char **argv) {
  parser_init();
  char *line;
  command_t *tokens; //input split/tokenized
  while ((line = readline("- "))) {
    tokens = parse(line);  
    
    
    
  } 

  parser_finalize();
  return 0;
}
