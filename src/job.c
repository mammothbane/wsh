//background job implementation
//(c) 2015 nathan m perry

#include "job.h"

static int l_size = 8;
static job_t **array; //job handles
static void jb_print(job_t* job, int index);

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
  array[index] = job;
  return index;
}

//finish this:
void jb_kill(int job) {
  //pre: job is a handle to a job
  //send sigkill
  jb_complete(job);
}

void jb_complete(int job) {
  free(array[job]);
  array[job] = NULL;
}

void jt_print(void) {
  int i, j = 0;
  for (i = 0; i < l_size; i++) {
    if (array[i]) {
      j++;
      jb_print(array[i], j);
    }
  }
}

void jb_print(job_t* job, int index) {
  command_t *cmd = job->list;
  printf("[%d] %s\n", index);
  while (cmd) {
    printf("%s ", cmd->command[0]); 
    if (cmd->ps_type & PS_PIPE) {
      fputs("| ", stdout);
      cmd = cmd->next; 
    }
  }
  putchar('\n');
}

void jt_free(void) {
  int i;
  for (i = 0; i < l_size; i++)
    if (array[i]) free(array[i]);
  free(array);
}
