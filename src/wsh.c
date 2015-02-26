// the williams shell
// (c) 2015 nathan m perry

#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

#define BUFFER 255
#define PROMPT "$- "

int main(int argc, char **argv) {
  char* line = malloc(BUFFER); //raw user input
  char** tokens; //input split/tokenized
  do {
    fputs(PROMPT, stdout);
    tokens = parse(line);  
  } while (line == fgets(line, BUFFER, stdin));

  return 0;
}
