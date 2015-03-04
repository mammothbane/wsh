// the williams shell
// (c) 2015 nathan m perry

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "parser.h"

int main(int argc, char **argv) {
  char* line; //raw user input
  char** tokens; //input split/tokenized
  while ((line = readline("- "))) {
    tokens = parse(line);  
  }

  return 0;
}
