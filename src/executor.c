//run standard commands
//(c) 2015 nathan m perry

#include "executor.h"

int execute(command_t *command) {
  //pre: command not null, valid first entry
  int pid = fork();
  if (!pid) {
    debug_print("executing %s\n", command->command[0]);
    execvp(command->command[0], command->command);
    //debug_print("errno is: %d\n", errno);
    perror(NULL);
    exit(1);
  } else if (pid < 0) {
    exit(pid);
    //error
  } else return pid;
}
