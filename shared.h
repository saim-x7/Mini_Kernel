#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROC 50
#define MAX_RAM 256

typedef enum { NEW, READY, RUNNING, WAITING, TERMINATED } State;

// Process Control Block
typedef struct {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int priority;
    int mem_req;
    State status;
    
    // Stats
    int t_start;
    int t_end;
    int t_wait;
    int t_turn;
} PCB;

#endif
