//tests for the parser
//(c) 2015 nathan m perry

#include "../src/parser.h"
#include "../src/debug.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

char* s1 = "",
  *s2 = "ls",
  *s3 = "ls .",
  *s4 = "ls . > test.c",
  *s5 = "ls ; grep a",
  *s6 = "ls; grep a",
  *s7 = ";",
  *s8 = "echo test | grep t",
  *s9 = "echo; echo; echo";

int main() {
  assert((void*)parse(strdup(s1)) == 0);
  command_t *cmd = parse(strdup(s2));
  assert(!strcmp(cmd->command[0], "ls"));
  assert(cmd->ps_type == PS_FG);
  assert(!cmd->next);
  cmd = parse(strdup(s3));
  assert(!strcmp(cmd->command[0], "ls"));
  assert(!strcmp(cmd->command[1], "."));
  assert(cmd->ps_type == PS_FG);
  assert(!cmd->next);
  cmd = parse(strdup(s4));
  assert(!strcmp(cmd->command[0], "ls"));
  assert(!strcmp(cmd->command[1], "."));
  assert(!strcmp(cmd->out, "test.c"));
  assert(cmd->ps_type == (PS_FG | PS_OUT));
  assert(!cmd->next);
  cmd = parse(strdup(s5));
  assert(!strcmp(cmd->command[0], "ls"));
  assert(cmd->next);
  assert(!strcmp(cmd->next->command[0], "grep"));
  assert(!strcmp(cmd->next->command[1], "a"));
  assert(cmd->ps_type == PS_FG);
  cmd = parse(strdup(s6));
  assert(!strcmp(cmd->command[0], "ls"));
  assert(cmd->next);
  assert(!strcmp(cmd->next->command[0], "grep"));
  assert(!strcmp(cmd->next->command[1], "a"));
  assert(cmd->ps_type == PS_FG);
  assert(!parse(strdup(s7))->command);
  cmd = parse(strdup(s8));
  assert(cmd->next);
  assert(cmd->ps_type & PS_PIPE);
  assert(!(cmd->ps_type & PS_BG));
  assert(!(cmd->next->ps_type & PS_BG));
  cmd = parse(strdup(s9));
  assert(cmd->next);
  assert(cmd->next->next);
  assert(!(cmd->ps_type & PS_PIPE));
  assert(!(cmd->next->ps_type & PS_PIPE));
  assert(!(cmd->next->next->ps_type & PS_PIPE));
  return 0;
}
