#include "fastqueue.h"
#include "shared_mem_utils.h"

#include <stdio.h>
#include <unistd.h>

int main(void) {
  void* bm = open_shared_mem("fq.bin", 4096);
  struct fq_queue* q = (struct fq_queue*)(bm);
  struct fq_consumer* c = fq_consumer_create(q);
  
  uint8_t c_buffer[4] = {0};
  int32_t bytes_read = 0;
  
  for(;;) {
    bytes_read = fq_consumer_read(c, c_buffer);
    
    printf("bytes read: %d\n", bytes_read);
    for(int i = 0; i < bytes_read; i++) {
      printf("%c\n", c_buffer[i]);
    }
    
    sleep(1);
  }
  

  return 0;
}
