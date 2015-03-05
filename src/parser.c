// the wsh parser
// (c) 2015 nathan m perry

#include "parser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *buffer;
command_t *list;
int lst_sz = 8;
const int bsize = 32;

static void cmd_addchar(command_t *cmd, int w_index, int c_index, char next);
static void cmd_settype(command_t *cmd, char type);
static void cmd_setinfile(command_t *cmd, char *in);
static void cmd_setoutfile(command_t *cmd, char *out);

void parser_init() {
  buffer = malloc(128);
  list = malloc(sizeof(command_t)*lst_sz);
}

void parser_finalize() {
  free(buffer);
  free(list);
}

//return list of commands terminated by 0x0
command_t *parse(char *line) {
  int i = 0, //command index in list 
    j = 0,   //word index in command
    k = 0;   //char index in word
  command_t *cur;
  while (*line) {
    list[i].command = calloc(sizeof(char**), 100); //fix this. dynamically reallocate if too many commands
    cur = &list[i];
    switch (*line) {
    case ';':
    case '\n':
    case '#':
      puts("\tend of foreground command");
      cmd_settype(cur, PS_FG);
      j = 0;
      i++;
      break;
    case '&':
      puts("\tend of background command");
      cmd_settype(cur, PS_BG);
      j = 0;
      i++;
      break;
    case '|':
      puts("\tend of piped command");
      cmd_settype(cur, PS_PIPE);
      j = 0;
      i++;
      break;
    case '>':
      puts("\texpecting output file");
      cmd_settype(cur, PS_OUT);
      break;
    case '<':
      puts("\texpecting input file");
      cmd_settype(cur, PS_IN);
      line++;
      char* 
      char* in = strsep(&line, "\n;&
      int l = 0, tmp = bsize;      
      char* in = malloc(tmp);
      while (*line && *line != ' ') {
	in[l] = *line;
	if (l == bsize-1) in = realloc(bsize*=2);
	line++;
	l++;
      }
      break;
    case ' ':
      puts("\tencountered space. incrementing word.");
      j++;
      k = 0;
      break;
    default:
      printf("\nline: %s\n", line);
      cmd_addchar(cur, j, k, *line);
      k++;
      break;
    } 
    if (i == lst_sz - 1) {
      lst_sz *= 2;
      printf("reallocating list to %d bytes\n", lst_sz);
      list = realloc(list, lst_sz*2*sizeof(command_t));
    }
    
    line++;
  }
  
} 

//inline?
			   
void cmd_addchar(command_t *cmd, int w_index, int c_index, char c) {
  
}


void cmd_settype(command_t *cmd, char c) {
  cmd->ps_type ^= !c;
}

void cmd_setinfile(command_t *cmd, char *file) {
  
}

void cmd_setoutfile(command_t *cmd, char *file) {
  
}
