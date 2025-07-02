#include "fastqueue.h"
#include "shared_mem_utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
  srand(42);

  void* bm = open_shared_mem("fq.bin", 4096);
  struct fq_queue* q = (struct fq_queue*)(bm);
  struct fq_producer* p = fq_producer_create(q);
  
  uint8_t p_buffer = 0;
  for(;;) {
    p_buffer = (rand() % (90 - 65)) + 65;
    fq_producer_write(p, &p_buffer, 1);
    printf("Sent %c\n", p_buffer);

    sleep(1);
  } 

  return 0;
}
