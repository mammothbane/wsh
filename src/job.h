#ifndef JOB_H
#define JOB_H

#include "debug.h"
#include "command.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct job {
  int pid;
  command_t *list;
  struct job *next;
} job_t;

void jt_init(void); //initialize the job table
int jb_create(command_t*, int pid); //return job number
void jb_kill(job_t**);
void jt_print(void);
void jt_free(void);

#endif
