#include "fastqueue.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//=============================================================================
//  PRODUCER
//=============================================================================
struct fq_producer fq_producer_create(struct fq_queue* q) {
  return (struct fq_producer) {
    .m_q = q,
    .m_local_counter = 0,
    .m_next_element = q->m_buffer
  };
}

void fq_producer_write(struct fq_producer* p, uint8_t* buffer,
    int32_t buffer_size) {
  const int32_t payload_size = sizeof(int32_t) + buffer_size;
  p->m_local_counter += payload_size;
  p->m_q->m_write_counter = p->m_local_counter;

  memcpy(p->m_next_element, &buffer_size, sizeof(int32_t));
  memcpy(p->m_next_element + sizeof(int32_t), buffer, buffer_size);
  
  p->m_q->m_read_counter = p->m_local_counter;
  p->m_next_element += payload_size;
}

//=============================================================================
//  CONSUMER
//=============================================================================
struct fq_consumer fq_consumer_create(struct fq_queue* q) {
  return (struct fq_consumer) {
    .m_q = q,
    .m_local_counter = 0,
    .m_next_element = q->m_buffer
  };
}

int32_t fq_consumer_read(struct fq_consumer* c, uint8_t* buffer) {
  if (c->m_local_counter == c->m_q->m_read_counter) 
    return 0;

  int32_t size = 0;
  memcpy(&size, c->m_next_element, sizeof(size));
  memcpy(buffer, c->m_next_element + sizeof(size), size);

  const int32_t payload_size = sizeof(size) + size;
  c->m_local_counter += payload_size;
  c->m_next_element += payload_size;

  return size;
}

