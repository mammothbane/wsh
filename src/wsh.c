// the williams shell
// (c) 2015 nathan m perry

#include "wsh.h"

#define PROMPT "$ - "

static void catch_int();

struct sigaction def = { .sa_handler = SIG_IGN };

int main(int argc, char **argv) {
  sigaction(SIGINT, &def, NULL);
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
	  //debug_print("[wsh]running execute\n");
	  list = execute(list);
	  //debug_print("[wsh]return from execute\n");
	}

	if (list->next) list = list->next;
	else break;
      } while (1);
    }
    //debug_print("running update\n");
    jt_update();
  } 
  jt_free();
  return 0;
}

//void catch_int() {
//  printf("caught an interrupt. terminating process %d if it exists\n", cpid);
//}
