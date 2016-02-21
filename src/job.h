#ifndef JOB_H
#define JOB_H

#include <sys/types.h>

typedef struct job {
  pid_t pid;
  char* name;
  struct job *next;
} job_t;

void jt_init    (void);                  // initialize the job table
int  jb_create  (char* name, pid_t pid); // create a job with the given name and PID and return the job number
void jb_kill    (int);
void jb_complete(int);
void jt_print   (void);
void jt_free    (void);
void jt_update  (void);

#endif
