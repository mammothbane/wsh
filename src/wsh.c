// the williams shell
// (c) 2015 nathan m perry

#include "parser.h"
#include "builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT "$- "

int main(int argc, char **argv) {
  char *line;
  command_t *list;
  while ((line = readline("- "))) {
    list = parse(line);  
    if (list && list->command[0]) {
      do {
	int bi = builtin(list);
	if (bi == BUILTIN_EXIT) {
	  exit((list->command[1] ? atoi(list->command[1]) : 0));
	} else if (bi == BUILTIN_CD) {
	  
	} else if (bi == BUILTIN_OTHER) {

	} else {

	}

	if (list->next) list = list->next;
	else break;
      } while (1);
    }    
  } 

  return 0;
}
