#ifndef PARSER_H
#define PARSER_H

#define PS_FG 0x0
#define PS_BG 0x1
#define PS_PIPE 0x2
#define PS_IN 0x4
#define PS_OUT 0x8

typedef struct command {
  char **command, *in, *out; //text of the executable
  char ps_type;
  struct command *next;
} command_t;

command_t *parse(char*); //parse string read in 
void cmd_free(command_t*);

#endif
