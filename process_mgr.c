#include "process_mgr.h"

PCB pList[MAX_PROC];
int pCount = 0;

void init_proc_list() {
    pCount = 0;
}

void create_process(int arr, int brst, int prio, int mem) {
    if (pCount >= MAX_PROC) {
        printf("Error: Limit reached.\n");
        return;
    }
    
    // Fill data
    pList[pCount].pid = pCount + 1;
    pList[pCount].arrival = arr;
    pList[pCount].burst = brst;
    pList[pCount].remaining = brst;
    pList[pCount].priority = prio;
    pList[pCount].mem_req = mem;
    pList[pCount].status = NEW;
    
    // Init stats
    pList[pCount].t_start = -1;
    pList[pCount].t_end = -1;
    pList[pCount].t_wait = 0;
    pList[pCount].t_turn = 0;

    printf("Process P%d created.\n", pList[pCount].pid);
    pCount++;
}

void print_p_table() {
    if (pCount == 0) {
        printf("\nList is empty.\n");
        return;
    }

    printf("\n--- Process Table ---\n");
    printf("| PID | Arr | Burst | Prio | Mem | Status     |\n");
    printf("|-----|-----|-------|------|-----|------------|\n");

    for (int i = 0; i < pCount; i++) {
        char s[15];
        State st = pList[i].status;

        if (st == NEW) strcpy(s, "NEW");
        else if (st == READY) strcpy(s, "READY");
        else if (st == RUNNING) strcpy(s, "RUNNING");
        else if (st == WAITING) strcpy(s, "WAITING");
        else strcpy(s, "TERMINATED");

        printf("| %-3d | %-3d | %-5d | %-4d | %-3d | %-10s |\n",
               pList[i].pid, pList[i].arrival, pList[i].burst,
               pList[i].priority, pList[i].mem_req, s);
    }
}

void clear_stats() {
    for (int i = 0; i < pCount; i++) {
        pList[i].remaining = pList[i].burst;
        pList[i].t_start = -1;
        pList[i].t_end = -1;
        pList[i].t_wait = 0;
        pList[i].t_turn = 0;
        pList[i].status = NEW;
    }
    printf("Stats reset.\n");
}

void clear_all_proc() {
    pCount = 0;
    printf("All processes deleted.\n");
}
