// a test for job.c
// (c) 2015 nathan m perry

#include "../src/job.c"
#include <stdio.h>
#include <stdlib.h>

int main() {
  int i;
  jt_init();
  jb_create();
  jt_free();

  jt_init();
  i = jb_create();
  jb_complete(i);
  jt_free();

  return 0;
}
