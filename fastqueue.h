#ifndef FASTQUEUE_H
#define FASTQUEUE_H

#include <stdint.h>

//=============================================================================
//  QUEUE
//=============================================================================
struct fq_queue;
struct fq_queue* fq_queue_create(void);
uint8_t* fq_queue_get(struct fq_queue* q);

//=============================================================================
//  PRODUCER
//=============================================================================
struct fq_producer;
struct fq_producer* fq_producer_create(struct fq_queue* q);
void fq_producer_write(struct fq_producer* p, uint8_t* buffer, int32_t buffer_len);

//=============================================================================
//  CONSUMER
//=============================================================================
struct fq_consumer;
struct fq_consumer* fq_consumer_create(struct fq_queue* q);
int32_t fq_consumer_read(struct fq_consumer* c, uint8_t* buffer);


#endif
