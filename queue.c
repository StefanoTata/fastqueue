#include "fastqueue.h"
#include "utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

#define shmem_name "fq.bin"
#define shmem_size 4096

static void* shmem_addr = NULL;

void sighandler(int signum) {
  assert(signum == SIGINT && shmem_addr);
  printf("\nSIGINT handler\n");
  destroy_shmem(shmem_addr, shmem_name, shmem_size);
  exit(EXIT_SUCCESS);
}

int main(void) {
  int signum = SIGINT;
  const struct sigaction act = {.sa_handler = sighandler};
  struct sigaction *oldact = NULL;

  if(sigaction(signum, &act, oldact) == -1){
    perror("open failed");
    assert(NULL); 
  }
  
  shmem_addr = create_shmem(shmem_name, shmem_size);
  struct fq_queue* q = shmem_addr;
  
  printf("Running...\n");
  while(1) {
    sleep(1);
  }
  
  return 0;
}
