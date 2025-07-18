#include "fastqueue.h"
#include "utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define shmem_name "fq.bin"
#define shmem_size 4096

int main(void) {
  srand(42);

  void* shmem_addr = create_shmem(shmem_name, shmem_size);
  struct fq_queue* q = (struct fq_queue*)(shmem_addr);
  struct fq_producer p = fq_producer_create(q);
  uint8_t p_buffer = 0;
  
  while(1) {
    p_buffer = (rand() % (90 - 65)) + 65;
    fq_producer_write(&p, &p_buffer, 1);
    printf("Sent %c\n", p_buffer);

    sleep(1);
  } 

  return 0;
}
