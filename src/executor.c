//run standard commands
//(c) 2015 nathan m perry

#include "executor.h"

command_t* execute(command_t *command, int fdin) {
  //pre: command not null, valid first entry
  int fdpipe[2] = {fdin, 0};
  command_t* ret = command;
  while (ret->next && (ret->ps_type & PS_PIPE)) ret = command->next;
  fdpair pair;
  int pid = fork();
  if (!pid) {
    printf("[%s:%d] read: %d, write: %d, next: %p\n", command->command[0], getpid(), fdpipe[0], fdpipe[1], command->next);
    if (command->next && (command->ps_type | PS_PIPE)) { 
      pipe(fdpipe);
      execute(command->next, fdpipe[1]);
    }
    debug_print("executing %s\n", command->command[0]);
    pair = fd_open(command);
    if (fdpipe[1]) {
      close(pair.out);
      pair.out = fdpipe[1];
    }
    if (fdpipe[0]) {
      close(pair.in);
      pair.in = fdpipe[0];
    }
    printf("in: %d, out:%d\n", pair.in, pair.out);
    if (pair.in) dup2(pair.in, 0);
    if (pair.out) dup2(pair.out, 1);
    execvp(command->command[0], command->command);
    //debug_print("errno is: %d\n", errno);
    int err = errno;
    if (errno == 2) fprintf(stderr, "%s: command not found.\n", command->command[0]);
    else perror(NULL);
    debug_print("errno: %d\n", err);
    exit(1);
  } else if (pid < 0) { //fork failed
    perror(NULL);
    exit(pid);
  } else {
    if (command->ps_type & PS_BG) {
      printf("return from execute\n");
    } else {
      wait(NULL);
    }
    fd_close(pair);
    return ret;
  }
}
