#include <assert.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

void* create_shmem(const char* mapping_name, const int size) {
  int fd = open(mapping_name, O_CREAT | O_RDWR, S_IRWXU);
  if(fd == -1){
    perror("open failed");
    assert(NULL); 
  }
  
  if(ftruncate(fd, size) == -1) {
    perror("resizing file failed");
    assert(NULL); 
  }

  void* bm = mmap(NULL, size, PROT_EXEC | PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if(bm == MAP_FAILED) {
    perror("calling mmap failed");
    assert(NULL); 
  }

  close(fd);

  return bm;
}

void destroy_shmem(void* addr, const char* mapping_name, const int size) {
  if(munmap(addr, size) == -1) {
    perror("calling mummap failed");
    assert(NULL); 
  }
  
  if(unlink(mapping_name) == -1) {
    perror("calling unlink failed");
    assert(NULL); 
  }
}
