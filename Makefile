CC = gcc
CFLAG = -O2 -Wall -Wextra 
CDEBUGFLAG = -g -O0 -Wall -Wextra
LINKING_FLAGS = -lrt

SRC = fastqueue.c utils.c

all: CC += $(CFLAG)
all: queue producer consumer

debug: CC += $(CDEBUGFLAG)
debug: queue producer consumer

queue: $(SRC) queue.c 
	$(CC) queue.c $(SRC) $(LINKING_FLAGS) -o queue

producer: $(SRC) producer.c
	$(CC) producer.c $(SRC) $(LINKING_FLAGS) -o producer

consumer: $(SRC) consumer.c
	$(CC) consumer.c $(SRC) $(LINKING_FLAGS) -o consumer

clean:
	rm queue producer consumer
