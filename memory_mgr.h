#ifndef MEMORY_MGR_H
#define MEMORY_MGR_H

typedef struct {
    int start;
    int size;
    int pid; // 0 = free
} Block;

void init_mem(int sz);
void show_mem_map();
int mem_alloc_first(int pid, int sz);
int mem_alloc_best(int pid, int sz);
int mem_alloc_worst(int pid, int sz);
int mem_free(int pid);

#endif
