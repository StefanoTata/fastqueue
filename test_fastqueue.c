#include "fastqueue.h"

#include <stdio.h>

int main(void)
{
  uint8_t buffer[4] = {0};
  buffer[0] = 'A';
  struct fq_queue* q = fq_queue_create();
  struct fq_producer* p = fq_producer_create(q);
 
  fq_producer_write(p, buffer, 1);

  uint8_t* b = fq_queue_get(q);
  printf("%c\n", b[4]);

  return 0;
  }
