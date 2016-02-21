// the wsh parser
// (c) 2015-2016 Nathan M. Perry

#include <sys/types.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"
#include "parser.h"

/**
 * Command flags.
 * PS_FG    foreground
 * PS_BG    background
 * PS_PIPE  out piped to another command
 * PS_IN    has in redirect
 * PS_OUT   has out redirect
 */
const ps_type_t 
	PS_FG = 0x0,
  	PS_BG = 0x1,
  	PS_PIPE = 0x2,
  	PS_IN = 0x4,
  	PS_OUT = 0x8;

// read and parse a line, returning a null-terminated list of commands.
command_t* parse(char *line) {
	command_t *head = NULL, *cmd = NULL;

	// terminate the line at the first space-preceeded hashmark
	char *hash = strpbrk(line, "#");

	// ignore this line if the first character was a hashmark.
	if (hash == line) return 0;
	
	while (hash && *(hash - 1) != ' ')
		hash = strpbrk(hash, "#");

	if (hash) *(hash - 1) = '\0';
	
	while (*line) {
		// grab a pointer to the first breaking character
		char *pt = strpbrk(line, ";\n#&|");

		// interpret NULL as \0, otherwise pick out the 
		char div = (pt) ? *pt : 0;
		
		if (cmd) {
			cmd->next = calloc(sizeof(command_t), 1);
			cmd = cmd->next;
		} else head = cmd = calloc(sizeof(command_t), 1);

		char *com = (pt) ? strsep(&line, ";\n#&|") : line;
		debug_print("com before io: '%s'\n", com);
		while (*com) {
			char *pt2 = strpbrk(com, "<>");
			if (pt2) {
				char io = *pt2;
				char *pre = strsep(&com, "<>");

				if (com[0] == ' ') com++;

				char *file = strsep(&com, " ");
				if (io == '<') {
					// set infile
					debug_print("\tinfile to '%s'\n", file);
					cmd->in = strdup(file);
					cmd->ps_type |= PS_IN;

				} else {
	  				// set outfile
					debug_print("\toutfile to '%s'\n", file);
					cmd->out = strdup(file);
					cmd->ps_type |= PS_OUT;
				}
				debug_print("\tprecat com: '%s', pre: '%s'\n", com, pre);
				
				if (com) {
					com = strcat(pre, com);
				} else com = pre;

				debug_print("\tpost com: '%s'\n", com);
			} else break;
		}
		debug_print("\tcom after io: '%s'\n", com);
		if (!*com) break;
		int sz = 8, i = 0;
		cmd->command = calloc(sizeof(void*)*sz, 1);
		while (strpbrk(com, " ")) {
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
				// any of these terminate the command
				case '\n':
				case ';':
				case '#':
					cmd->ps_type &= ~PS_BG;
					break;
				// this terminates but makes it a job
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

void cmd_free(command_t *cmd) {


}
