#ifndef JOB_H
#define JOB_H

#include "debug.h"
#include "command.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

typedef struct job {
  int pid;
  char* name;
  struct job *next;
} job_t;

void jt_init(void); //initialize the job table
int jb_create(char* name, int pid); //return job number
void jb_kill(int);
void jb_complete(int);
void jt_print(void);
void jt_free(void);
void jt_update(void);

#endif
