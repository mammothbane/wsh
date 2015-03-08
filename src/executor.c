//run standard commands
//(c) 2015 nathan m perry

#include "executor.h"

int execute(command_t *command) {
  //pre: command not null, valid first entry
  int pid = fork();
  if (!pid) {
    debug_print("executing %s\n", command->command[0]);
    fdpair pair = fd_open(command);
    printf("in: %d, out:%d\n", pair.in, pair.out);
    dup2(pair.in, 0);
    dup2(pair.out, 1);
    execvp(command->command[0], command->command);
    //debug_print("errno is: %d\n", errno);
    int err = errno;
    if (errno == 2) fprintf(stderr, "%s: command not found.\n", command->command[0]);
    else perror(NULL);
    debug_print("errno: %d\n", err);
    exit(1);
  } else if (pid < 0) {
    perror(NULL);
    exit(pid);
    //error
  } else return pid;
}
