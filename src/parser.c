// the wsh parser
// (c) 2015 nathan m perry

#include "parser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//return list of commands terminated by 0x0
command_t *parse(char *line) {
  while (*line) {
    char *pt = strpbrk(line, ";\n#&|");
    char div = (pt) ? *pt : 0;
    char *com = (pt) ? strsep(&line, ";\n#&|") : line;
    printf("com before io: '%s'\n", com);
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
	  printf("\tinfile to '%s'\n", file);
	  //set infile
	} else {
	  printf("\toutfile to '%s'\n", file);
	  //set outfile
	}
	printf("\tprecat com: '%s', pre: '%s'\n", com, pre);
	if (com) {
	  com = strcat(pre, com);
	  //com = strcat(strcat(pre, " "), com);
	} else com = pre;
	//printf(
	printf("\tpost com: '%s'\n", com);
      } else break;
    }
    printf("\tcom after io: '%s'\n", com);
    //free(cinit);
    if (!*com) break;
    while (strpbrk(com, " ")) {
      //      if (strpbrk(com, " ")) {
      char *sep = strsep(&com, " ");
      printf("\tencountered command: '%s'\n", sep);
      //put pt3 into command
      //printf("%s\n", sep);
      //} else break;
    }
    printf("\tlast command: '%s'\n", com);
    sleep(1);
    if (!div) break;
    //printf("div: '%s'\n", div ? "present" : "not present");
  }
}
