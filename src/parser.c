// the wsh parser
// (c) 2015 nathan m perry

#include "parser.h"
#include "debug.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//return list of commands terminated by 0x0
command_t *parse(char *line) {
  command_t *head = 0, *cmd = 0;
  while (*line) {
    char *pt = strpbrk(line, ";\n#&|");
    char div = (pt) ? *pt : 0;
    if (cmd) { 
      cmd->next = malloc(sizeof(command_t));
      cmd = cmd->next;
    } else head = cmd = malloc(sizeof(command_t));
    char *com = (pt) ? strsep(&line, ";\n#&|") : line;
    debug_print("com before io: '%s'\n", com);
    //printf("a%s\n", com);
    //char *ccom = strdup(com), *cinit = ccom;
    while (*com) {
      char *pt2 = strpbrk(com, "<>");
      if (pt2) {
	char io = *pt2;
	char *pre = strsep(&com, "<>");
	if (com[0] == ' ') com++;
	char *file = strsep(&com, " ");
	if (io == '<') {
	  //set infile
	  debug_print("\tinfile to '%s'\n", file);
	  cmd->in = strdup(file);
	  cmd->ps_type |= PS_IN;
	} else {
	  //set outfile
	  debug_print("\toutfile to '%s'\n", file);
	  cmd->out = strdup(file);
	  cmd->ps_type |= PS_OUT;
	}
	debug_print("\tprecat com: '%s', pre: '%s'\n", com, pre);
	if (com) {
	  com = strcat(pre, com);
	  //com = strcat(strcat(pre, " "), com);
	} else com = pre;
	//printf(
	debug_print("\tpost com: '%s'\n", com);
      } else break;
    }
    debug_print("\tcom after io: '%s'\n", com);
    //free(cinit);
    if (!*com) break;
    int sz = 8, i = 0;
    cmd->command = malloc(sizeof(void*)*sz);
    while (strpbrk(com, " ")) {
      //debug_print("\tcom: '%s'\n", com);
      char *sep = strsep(&com, " ");
      if (*sep) {
	debug_print("\tencountered command: '%s'\n", sep);
	cmd->command[i] = strdup(sep);
	i++;
	if (i == sz - 1) {
	  sz *= 2;
	  cmd->command = realloc(cmd->command, sz*sizeof(void*));
	  debug_print("\targv length ->  %d\n", sz);
	}
      }
    }
    if (*com) {
      debug_print("\tlast command: '%s'\n", com);
      cmd->command[i] = strdup(com);
    }
    if (div) {
      switch (div) {
      case '\n':
      case ';':
      case '#':
	cmd->ps_type &= ~PS_BG;
	break;
      case '&':
	cmd->ps_type |= PS_BG;
	break;
      case '|':
	cmd->ps_type |= PS_PIPE;
	break;
      }      
    } else break;
  }
  return head;
}
