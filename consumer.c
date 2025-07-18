#include "fastqueue.h"
#include "utils.h"

#include <stdio.h>
#include <unistd.h>

#define shmem_name "fq.bin"
#define shmem_size 4096

int main(void) {
  void* shmem_addr = create_shmem(shmem_name, shmem_size);
  struct fq_queue* q = (struct fq_queue*)(shmem_addr);
  struct fq_consumer c = fq_consumer_create(q);
  
  uint8_t c_buffer[4] = {0};
  int32_t bytes_read = 0;
  
  while(1) {
    bytes_read = fq_consumer_read(&c, c_buffer);
    
    printf("bytes read: %d\n", bytes_read);
    for(int i = 0; i < bytes_read; i++) {
      printf("%c\n", c_buffer[i]);
    }
    
    sleep(1);
  }

  return 0;
}
