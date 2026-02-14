#include <stdio.h>
#include "memory_mgr.h"
#include "shared.h"

Block ram[MAX_RAM];
int b_count = 0;
int total_ram = 0;

void init_mem(int sz) {
    if (sz > MAX_RAM) sz = MAX_RAM;
    total_ram = sz;
    
    ram[0].start = 0;
    ram[0].size = sz;
    ram[0].pid = 0; 
    
    b_count = 1;
    printf("RAM Initialized: %d units.\n", sz);
}

void show_mem_map() {
    printf("\n--- RAM Map ---\n");
    for (int i = 0; i < b_count; i++) {
        if (ram[i].pid == 0) {
            printf("[Free:%d] ", ram[i].size);
        } else {
            printf("[P%d:%d] ", ram[i].pid, ram[i].size);
        }
    }
    printf("\n");
}

void add_split_block(int idx, int st, int sz, int id) {
    for (int i = b_count; i > idx; i--) {
        ram[i] = ram[i-1];
    }
    ram[idx].start = st;
    ram[idx].size = sz;
    ram[idx].pid = id;
    b_count++;
}

int mem_alloc_first(int pid, int sz) {
    for (int i = 0; i < b_count; i++) {
        if (ram[i].pid == 0 && ram[i].size >= sz) {
            int old_sz = ram[i].size;
            
            ram[i].pid = pid;
            ram[i].size = sz;
            
            int left = old_sz - sz;
            if (left > 0) {
                add_split_block(i + 1, ram[i].start + sz, left, 0);
            }
            return ram[i].start;
        }
    }
    return -1;
}

int mem_alloc_best(int pid, int sz) {
    int idx = -1;
    int best = 999999;

    for (int i = 0; i < b_count; i++) {
        if (ram[i].pid == 0 && ram[i].size >= sz) {
            if (ram[i].size < best) {
                best = ram[i].size;
                idx = i;
            }
        }
    }

    if (idx != -1) {
        int old_sz = ram[idx].size;
        ram[idx].pid = pid;
        ram[idx].size = sz;
        
        int left = old_sz - sz;
        if (left > 0) {
            add_split_block(idx + 1, ram[idx].start + sz, left, 0);
        }
        return ram[idx].start;
    }
    return -1;
}

int mem_alloc_worst(int pid, int sz) {
    int idx = -1;
    int worst = -1;

    for (int i = 0; i < b_count; i++) {
        if (ram[i].pid == 0 && ram[i].size >= sz) {
            if (ram[i].size > worst) {
                worst = ram[i].size;
                idx = i;
            }
        }
    }

    if (idx != -1) {
        int old_sz = ram[idx].size;
        ram[idx].pid = pid;
        ram[idx].size = sz;
        
        int left = old_sz - sz;
        if (left > 0) {
            add_split_block(idx + 1, ram[idx].start + sz, left, 0);
        }
        return ram[idx].start;
    }
    return -1;
}

int mem_free(int pid) {
    int freed = 0;
    for (int i = 0; i < b_count; i++) {
        if (ram[i].pid == pid) {
            ram[i].pid = 0;
            freed += ram[i].size;
        }
    }
    
    // Merge blocks
    for (int i = 0; i < b_count - 1; i++) {
        if (ram[i].pid == 0 && ram[i+1].pid == 0) {
            ram[i].size += ram[i+1].size;
            
            for (int j = i + 1; j < b_count - 1; j++) {
                ram[j] = ram[j+1];
            }
            b_count--;
            i--;
        }
    }
    
    return freed;
}
