SRC = fastqueue.c shared_mem_utils.c

CFLAG = -O2 -Wall -Wextra 
CDEBUGFLAG = -g -O0 -Wall -Wextra
LINKING_FLAGS = -lrt

all_debug: fastqueue_debug producer_debug consumer_debug

fastqueue: $(SRC) test_fastqueue.c 
	gcc $(CFLAG) test_fastqueue.c $(SRC) $(LINKING_FLAGS) -o test_fastqueue

fastqueue_debug: $(SRC) test_fastqueue.c 
	gcc $(CDEBUGFLAG) test_fastqueue.c $(SRC) $(LINKING_FLAGS) -o test_fastqueue

producer_debug: $(SRC) test_producer.c
	gcc $(CDEBUGFLAG) test_producer.c $(SRC) $(LINKING_FLAGS) -o test_producer

consumer_debug: $(SRC) test_consumer.c
	gcc $(CDEBUGFLAG) test_consumer.c $(SRC) $(LINKING_FLAGS) -o test_consumer

clean: 
	rm test_fastqueue test_producer test_consumer
