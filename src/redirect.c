//code to handle file creation and redirection
//(c) 2015 nathan m perry

#include "redirect.h"

/*
 * Open out for writing in truncate mode if it exists.
 * Open in for reading if it exists.
 * Return both file descriptors.
 */
fdpair fd_open(command_t *cmd) {
  int in = -1, out = -1;
  if (cmd->in) { 
    in = open(cmd->in, O_RDONLY);
    if (in < 0) {
      perror("fd_open(in)");
      exit(EXIT_FAILURE);
    }
  }
  if (cmd->out) {
    out = open(cmd->out, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
    if (out < 0) {
      perror("fd_open(out)");
      exit(EXIT_FAILURE);
    }
  }
  return (fdpair){in, out};
}

/*
 * Close both files if they exist.
 */
void fd_close(fdpair pair) {
  int err = 0;
  if (pair.in >= 0) {
    err = close(pair.in);
    if (err) {
      perror("fd_close(in)");
      exit(EXIT_FAILURE);
    }
  }
  if (pair.out >= 0) {
    err = close(pair.out);
    if (err) {
      perror("fd_close(out)");
      exit(EXIT_FAILURE);
    }
  }
}
