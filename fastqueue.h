#ifndef FASTQUEUE_H
#define FASTQUEUE_H

#include <stdint.h>

//=============================================================================
//  QUEUE
//=============================================================================
struct fq_queue {
  uint64_t  m_read_counter;
  uint64_t  m_write_counter;
  uint8_t   m_buffer[1024];
};

struct fq_queue* fq_queue_create(void* buffer);

//=============================================================================
//  PRODUCER
//=============================================================================
struct fq_producer {
  uint64_t m_local_counter;
  uint8_t* m_next_element;
  struct fq_queue* q; 
};

struct fq_producer* fq_producer_create(struct fq_queue* q);
void fq_producer_write(struct fq_producer* p, uint8_t* buffer, int32_t buffer_len);

//=============================================================================
//  CONSUMER
//=============================================================================
struct fq_consumer {
  uint64_t m_local_counter;
  struct fq_queue* q; 
  uint8_t* m_next_element;
};

struct fq_consumer* fq_consumer_create(struct fq_queue* q);
int32_t fq_consumer_read(struct fq_consumer* c, uint8_t* buffer);

#endif
