#ifndef COMMAND_H
#define COMMAND_H

typedef char ps_type_t;

typedef struct command {
	char **command, *in, *out; // text of the command
	ps_type_t ps_type;
	struct command *next;
} command_t;

typedef struct fdpair {
	int in, out;
} fdpair;

extern int cpid;
extern const ps_type_t 
	PS_FG,
	PS_BG,
	PS_PIPE,
	PS_IN,
	PS_OUT;

#endif
