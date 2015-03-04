// the wsh parser
// (c) 2015 nathan m perry

#include "parser.h"
#include <string.h>

static struct command_w token(char *line); //return a command 

char **parse(char *line) {
  int i,j;
  for (i = 0; line[i]; line[i] == ' ' ? i++ : ); //count occurrences of ' '
  if (i > 0) {
    char **words = malloc((i+1)*sizeof(char*));
    for (j = 0; *line; j++) {
      words[j] = strsep(&line,' '); 
    }

    free(words);
  }
} 

struct command_w *token(char **line, int index, int len) {
  command_w *cmds = malloc(len*sizeof(command_w));
  int i, j = 0, k = 0; 
  // i: word index in line
  // j: command index in cmds
  // k: word index in current command
  
  for (i = 0; i < len; i++) {
    command_t com = cmds[j].command;
    if (strpbrk(line[i], "#\n;")) {
      com.ps_type &= ~PS_BG;
      j++;
      k = 0;
    } else if (strpbrk(line[i], "|")){
      com.ps_type |= PS_PIPE;
      j++;
      k = 0;
    } else if (strpbrk(line[i], "&")) {
      com.ps_type |= PS_BG;
      j++;
      k = 0;
    } else if (strpbrk(line[i], ">")) { //these two won't match bash exactly
      com.ps_type |= PS_IN;
      if (strlen(line[i]) > 1) { 
	com.in = (line[i] + 1);
      } else com.in = line[i + 1];
    } else if (strpbrk(line[i], "<")) {
      com.ps_type |= PS_OUT;
      if (strlen(line[i]) > 1) {
	com.out = (line[i] + 1);
      } else com.out = line[i + 1];
    } else com.command[k] = strdup(line[i]);
  }
  
  return (struct command_w){com, i - index};
}
