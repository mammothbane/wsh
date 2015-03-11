//run standard commands
//(c) 2015 nathan m perry

#include "executor.h"

static command_t* execute_internal(command_t*, int, int);
static void catch_int();

command_t* execute(command_t *command) {
  return execute_internal(command, 0, 0); 
}

struct sigaction sigint = { .sa_handler = catch_int };

int cpid = 0;

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

    //register SIGINT handler if this is a foreground process
    if (!(command->ps_type & PS_BG)) {
      sigaction(SIGINT, &sigint, NULL);
    }

    if (!cpid) { //in the second child. run exec here.
      printf("child %d spawned\n", getpid());
      debug_print("executing %s\n", command->command[0]);
      execvp(command->command[0], command->command);
      //debug_print("errno is: %d\n", errno);
      int err = errno;
      if (errno == 2) fprintf(stderr, "%s: command not found.\n", command->command[0]);
      else perror(NULL);
      debug_print("errno: %d\n", err);
      exit(EXIT_FAILURE);

    } else if (cpid < 0) {
      perror(NULL);
      //if (command->ps_type & PS_BG) jb_complete(jb_num);
      exit(EXIT_FAILURE);
      
    } else { //we're in the first child
      wait(NULL); //wait for the command to finish executing
      printf("[%d] wait complete for child %d. closing file descriptors: in = %d, out = %d\n", getpid(), cpid, pair.in, pair.out);
      fd_close(pair);
      //if (command->ps_type & PS_BG) jb_complete(jb_num);
      exit(EXIT_SUCCESS);
    }
  } else if (pid < 0) { //fork failed
    perror(NULL);
    exit(EXIT_FAILURE);
  } else {
    printf("creating job\n");
    jb_create(command->command[0], pid);
    if (command->ps_type & PS_BG) {
      printf("return from execute\n");
    } else {
      wait(NULL);
    }
    return ret;
  }
}


void catch_int() {
  printf("caught an interrupt. terminating process %d if it exists\n", cpid);
  if (cpid) {
    kill(SIGINT, cpid);
  }
}
