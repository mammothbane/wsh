// the wsh parser
// (c) 2015 nathan m perry

#include "parser.h"

const char PS_FG = 0x0,
  PS_BG = 0x1,
  PS_PIPE = 0x2,
  PS_IN = 0x4,
  PS_OUT = 0x8;

//return list of commands terminated by 0x0
command_t *parse(char *line) {
  command_t *head = 0, *cmd = 0;
  
  //terminate the line at the first space-preceeded hashmark
  char *hash = strpbrk(line, "#");
  if (hash > line) {
    while (*(hash - 1) != ' ' && hash) hash = strpbrk(hash, "#");
    if (hash) *(hash - 1) = '\0';
  } else if (hash == line) return 0;
  
  while (*line) {
    char *pt = strpbrk(line, ";\n#&|");
    char div = (pt) ? *pt : 0;
    if (cmd) { 
      cmd->next = calloc(sizeof(command_t), 1);
      cmd = cmd->next;
    } else head = cmd = calloc(sizeof(command_t), 1);
    char *com = (pt) ? strsep(&line, ";\n#&|") : line;
    while (*com) {
      char *pt2 = strpbrk(com, "<>");
      if (pt2) {
	char io = *pt2;
	char *pre = strsep(&com, "<>");
	if (com[0] == ' ') com++;
	char *file = strsep(&com, " ");
	if (io == '<') {
	  //set infile
	  cmd->in = strdup(file);
	  cmd->ps_type |= PS_IN;
	} else {
	  //set outfile
	  cmd->out = strdup(file);
	  cmd->ps_type |= PS_OUT;
	}
	if (com) {
	  com = strcat(pre, com);
	} else com = pre;
      } else break;
    }
    if (!*com) break;
    int sz = 8, i = 0;
    cmd->command = calloc(sizeof(void*)*sz, 1);
    while (strpbrk(com, " ")) {
      char *sep = strsep(&com, " ");
      if (*sep) {
	cmd->command[i] = strdup(sep);
	i++;
	if (i == sz - 1) {
	  sz *= 2;
	  cmd->command = realloc(cmd->command, sz*sizeof(void*));
	}
      }
    }
    if (*com) {
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
