#ifndef COMMAND_H
#define COMMAND_H

extern const char PS_FG,
  PS_BG,
  PS_PIPE,
  PS_IN,
  PS_OUT;

typedef struct command {
  char **command, *in, *out; //text of the executable
  char ps_type;
  struct command *next;
} command_t;

typedef struct fdpair {
  int in, out;
} fdpair;

#endif
