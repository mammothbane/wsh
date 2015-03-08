// the williams shell
// (c) 2015 nathan m perry

#include "wsh.h"

#define PROMPT "$ - "

int main(int argc, char **argv) {
  char *line;
  command_t *list;
  while ((line = readline(PROMPT))) {
    list = parse(line);  
    if (list && list->command) {
      do {
	int bi = builtin(list);
	if (bi == BUILTIN_EXIT) {
	  exit((list->command[1] ? atoi(list->command[1]) : 0));
	} else if (bi == BUILTIN_CD) {
	  
	} else if (bi == BUILTIN_OTHER) {

	} else {
	  fdpair fds = fd_open(list);
	  int status, pid = execute(list);
	  wait(&status);
	  fd_close(fds);
	}

	if (list->next) list = list->next;
	else break;
      } while (1);
    }    
  } 

  return 0;
}
