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
  //printf("in file descriptor is %d\n", fdin);
  //pre: command not null, valid first entry
  int fdpipe[2];
  command_t* ret = command;
  while (ret->next && (ret->ps_type & PS_PIPE)) ret = ret->next;
  fdpair pair;
  int pid = fork();
  if (!pid) {

    //call piped command recursively if necessary
    if (command->next && (command->ps_type & PS_PIPE)) { 
      pipe(fdpipe);
      execute_internal(command->next, fdpipe[0], 1);
    }

    //set file descriptors for child
    pair = fd_open(command);
    if (fdpipe[1]) {
      close(pair.out);
      pair.out = fdpipe[1];
    }
    if (fdin) {
     close(pair.in);
     pair.in = fdin;
    }
    if (pair.in >= 0) dup2(pair.in, 0);
    if (pair.out >= 0) dup2(pair.out, 1);

    //execute the command
    int spid = fork(); //fork so we can do work after the process is done
    if (!spid) {
      execvp(command->command[0], command->command);
      if (errno == 2) fprintf(stderr, "%s: command not found.\n", command->command[0]);
      else perror(NULL);
      exit(EXIT_FAILURE);
    } else if (spid < 0) { //fork failed
      perror(NULL);
      exit(EXIT_FAILURE);
    } else { //fork succeeded and we're still the first child process
      int status;
      wait(&status); //wait until the command we're running is finished
      fd_close(pair); //then clean up any open file descriptors
      exit(WEXITSTATUS(status));
      }
  } else if (pid < 0) { //fork failed
    perror(NULL);
    exit(EXIT_FAILURE);
  } else {
    if (!parent) {
      if (command->ps_type & PS_BG) {
	jb_create(command->command[0], pid);
      } else {
	cpid = pid;
	wait(NULL);
      }
    } 
    return ret;
   }
}
