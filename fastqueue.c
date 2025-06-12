#include "fastqueue.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//=============================================================================
//  QUEUE
//=============================================================================
struct fq_queue
{
  uint64_t  m_read_counter;
  uint64_t  m_write_counter;
  uint8_t*  m_buffer;
};

//TODO create queue passing pointer to mapped mem
struct fq_queue* fq_queue_create(void)
{
  struct fq_queue* q = malloc(sizeof(*q));
  q->m_read_counter = 0;
  q->m_write_counter = 0;
  q->m_buffer = malloc(2056);
  return q;
}

uint8_t* fq_queue_get(struct fq_queue* q)
{
  return q->m_buffer;
}

//=============================================================================
//  PRODUCER
//=============================================================================
struct fq_producer
{
  int32_t m_local_counter;
  uint8_t* m_next_element;
  struct fq_queue* q; 
};

struct fq_producer* fq_producer_create(struct fq_queue* q)
{
  struct fq_producer* p = malloc(sizeof(*p));
  p->q = q;
  p->m_local_counter = 0;
  p->m_next_element = q->m_buffer;
  return p;
}

void fq_producer_write(struct fq_producer* p, uint8_t* buffer,
    int32_t buffer_size)
{
  const int32_t payload_size = sizeof(int32_t) + buffer_size;
  p->m_local_counter += payload_size;
  p->q->m_write_counter = p->m_local_counter;

  memcpy(p->m_next_element, &buffer_size, sizeof(int32_t));
  memcpy(p->m_next_element + sizeof(int32_t), buffer, buffer_size);
  
  p->q->m_write_counter = p->m_local_counter;
  p->m_next_element += payload_size;
}

//=============================================================================
//  CONSUMER
//=============================================================================
struct fq_consumer
{
  struct fq_queue* q; 
};

struct fq_consumer* fq_consumer_create(struct fq_queue* q)
{
  struct fq_consumer* c = malloc(sizeof(*c));
  c->q = q;
  return c;
}

int32_t fq_consumer_read(struct fq_consumer* c, uint8_t* buffer)
{
  return 0;
}

