#ifndef PARSER_H
#define PARSER_H

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

command_t *parse(char*); //parse string read in 
void cmd_free(command_t*);

#endif
