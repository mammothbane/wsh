#ifndef PARSER_H
#define PARSER_H

enum types {
  
}

typedef struct command_t {
  char **command, *in, *out; //text of the executable
  
} command;

char **parse(char*); //parse string read in 

#endif
