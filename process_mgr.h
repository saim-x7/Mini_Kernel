#ifndef PROCESS_MGR_H
#define PROCESS_MGR_H

#include "shared.h"

// Global access
extern PCB pList[MAX_PROC];
extern int pCount;

void init_proc_list();
void create_process(int arr, int brst, int prio, int mem);
void print_p_table();
void clear_stats();
void clear_all_proc();

#endif
