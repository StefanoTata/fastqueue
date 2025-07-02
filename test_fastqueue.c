#include "fastqueue.h"
#include "shared_mem_utils.h"

#include <stdio.h>

int main(void) {
  void* bm = create_shared_mem("fq.bin", 4096);
  fq_queue_create(bm);
  
  return 0;
 }
