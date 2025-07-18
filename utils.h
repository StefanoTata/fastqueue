#ifndef SHARED_MEM_UTILS_H
#define SHARED_MEM_UTILS_H

void* create_shmem(const char* mapping_name, const int size);
void destroy_shmem(const void* addr, const char* mapping_name, const int size);

#endif
