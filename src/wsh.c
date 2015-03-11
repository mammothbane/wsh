// the williams shell
// (c) 2015 nathan m perry

#include "wsh.h"

#define PROMPT "$ - "

int cpid = 0;

static void catch_int();

struct sigaction intr = { .sa_handler = catch_int };

int main(int argc, char **argv) {
  sigaction(SIGINT, &intr, NULL);
  jt_init();
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
	  list = execute(list);
	  cpid = 0;
	}

	if (list->next) list = list->next;
	else break;
      } while (1);
    }
    jt_update();
  } 
  jt_free();
  return 0;
}

void catch_int() {
  if (cpid) {
    if (kill(cpid, SIGINT) < 0) {
      perror("ctrl-c");
    }
  }
}
