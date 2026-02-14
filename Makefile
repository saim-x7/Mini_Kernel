CC = gcc
CFLAGS = -Wall -std=c11
OUT = simulator
OBJ = main.o process_mgr.o scheduler.o memory_mgr.o

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) $(CFLAGS) -o $(OUT) $(OBJ)

main.o: main.c shared.h process_mgr.h scheduler.h memory_mgr.h
	$(CC) $(CFLAGS) -c main.c

process_mgr.o: process_mgr.c process_mgr.h shared.h
	$(CC) $(CFLAGS) -c process_mgr.c

scheduler.o: scheduler.c scheduler.h shared.h process_mgr.h
	$(CC) $(CFLAGS) -c scheduler.c

memory_mgr.o: memory_mgr.c memory_mgr.h shared.h
	$(CC) $(CFLAGS) -c memory_mgr.c

clean:
	rm -f *.o $(OUT)
