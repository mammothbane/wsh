//background job implementation
//(c) 2015 nathan m perry

#include "job.h"

static int l_size = 8;
static job_t **array; //job handles

void jt_init(void) {
  array = calloc(sizeof(job_t*), l_size);
}

int jb_create(char *name, int pid) {
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
  job->name = name;
  printf("creating job %s with pid %d\n", name, pid);
  array[index] = job;
  return index;
}

void jb_kill(int job) {
  if (array[job]) {
    if (kill(array[job]->pid, SIGINT) < 0) {
      perror("KILL");
    }
  }
}

void jb_complete(int job) {
  free(array[job]);
  array[job] = NULL;
}

void jt_print(void) {
  int i;
  for (i = 0; i < l_size; i++) {
    if (array[i]) {
      printf("[%d] %s\n", i, array[i]->name);
    }
  }
}

void jt_update(void) {
  int i, status;
  for (i = 0; i < l_size; i++) {
    if (array[i] && waitpid(array[i]->pid, &status, WNOHANG) == -1) { 
      jb_complete(i);
      printf("[%d] %s\n", i, (WIFSIGNALED(status)) ? "terminated" : "finished");
    }
  }
}

void jt_free(void) {
  int i;
  for (i = 0; i < l_size; i++)
    if (array[i]) free(array[i]);
  free(array);
}
