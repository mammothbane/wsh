//background job implementation
//(c) 2015 nathan m perry

#include "job.h"

static int l_size = 8;
static job_t **array; //job handles

void jt_init(void) {
  array = calloc(sizeof(job_t*), l_size);
}

int jb_create(command_t *cmd, int pid) {
  int index = l_size;
  int i;
  for (i = 0; i < l_size; i++) {
    if (!array[i]) {
      index = i;
      break;
    }
  }
  if (index == l_size) {
    l_size *= 2;
    array = realloc(array, l_size*sizeof(job_t*));
    int j;
    for (j = index; j < l_size; j++) array[j] = NULL; //realloc doesn't zero
  }
  job_t* job = malloc(sizeof(job_t));
  job->pid = pid;
  job->list = cmd;
  array[index] = job;
  return job;
}

void jb_kill(int job) {
  //pre: job is a handle to a job
  free(array[job]);
  array[job] = NULL;  
}

void jt_print(void) {
  int i, j = 0;
  for (i = 0; i < l_size; i++) {
    if (array[i]) {
      j++;
      printf("[%d] %s\n", list->command[0]);
    }
  }
}

void jt_free(void) {
  int i;
  for (i = 0; i < l_size; i++)
    if (array[i]) free(array[i]);
  free(array);
}
