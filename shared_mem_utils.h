#ifndef SHARED_MEM_UTILS_H
#define SHARED_MEM_UTILS_H

void* create_shared_mem(const char* mapping_name, const int size);
void* open_shared_mem(const char* mapping_name, const int size);

#endif
