// a test for job.c
// (c) 2015 nathan m perry

#include "../src/job.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <assert.h>

int main() {
  int i;

  jt_init();
  jb_create("one", 1);
  jt_free();

  jt_init();
  i = jb_create("two", 2);
  jb_create("three", 3);
  jb_create("four", 4);
  jb_complete(i);
  jt_free();

  return 0;
}
