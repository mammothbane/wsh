//run standard commands
//(c) 2015 nathan m perry

#include "executor.h"

static command_t* execute_internal(command_t*, int, int);

command_t* execute(command_t *command) {
  return execute_internal(command, 0, 0); 
}

/*
 * fdin and parent are used for recursive calls. set to 0 externally.
 * return the last command processed
 */
command_t* execute_internal(command_t *command, int fdin, int parent) {
  //pre: command not null, valid first entry
  int fdpipe[2] = {fdin, 0};
  command_t* ret = command;
  while (ret->next && (ret->ps_type & PS_PIPE)) ret = ret->next;
  fdpair pair;
  int pid = fork();
  if (!pid) {
    int jb_num = -1;
    if (command->ps_type & PS_BG) jb_num = jb_create(command, getpid());
    printf("[%s:%d] read: %d, write: %d, next: %p\n", command->command[0], getpid(), fdpipe[0], fdpipe[1], command->next);
    
    //call piped command recursively if necessary
    if (command->next && (command->ps_type & PS_PIPE)) { 
      printf("pipe: %s -> %s\n", command->command[0], command->next->command[0]);
      pipe(fdpipe);
      execute_internal(command->next, fdpipe[1], 1);
    }

    //set file descriptors for child
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

    //fork a new child to wait for the process
    int cpid = fork();
    if (!cpid) { //in the second child. run exec here.
      debug_print("executing %s\n", command->command[0]);
      execvp(command->command[0], command->command);
      //debug_print("errno is: %d\n", errno);
      int err = errno;
      if (errno == 2) fprintf(stderr, "%s: command not found.\n", command->command[0]);
      else perror(NULL);
      debug_print("errno: %d\n", err);
      exit(1);
    } else if (pid < 0) {
      perror(NULL);
      if (command->ps_type & PS_BG) jb_complete(jb_num);
      exit(cpid);
    } else { //we're in the first child
      wait(NULL); //wait for the command to finish executing
      fd_close(pair);
      if (command->ps_type & PS_BG) jb_complete(jb_num);
      return 0;
    }
  } else if (pid < 0) { //fork failed
    perror(NULL);
    exit(pid);
  } else {
    if (command->ps_type & PS_BG) {
      printf("return from execute\n");
    } else {
      wait(NULL);
    }
    return ret;
  }
}
