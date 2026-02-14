#include <stdio.h>
#include <string.h>
#include "scheduler.h"
#include "process_mgr.h"

//Helpers

void bubble_sort_arr(PCB arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].arrival > arr[j+1].arrival) {
                PCB temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

//Gantt Chart Display

void draw_gantt(int history[], int len) {
    if (len < 1) return;

    printf("\n   === Gantt Chart ===\n");

    printf("    +");
    for (int i = 0; i < len; i++) printf("-----");
    printf("+\n");

    printf("    |");
    for (int i = 0; i < len; i++) {
        if (history[i] == 0) printf(" xx |");
        else printf(" P%d |", history[i]);
    }
    printf("\n");

    printf("    +");
    for (int i = 0; i < len; i++) printf("-----");
    printf("+\n");

    printf("    0");
    for (int i = 1; i <= len; i++) {
        if (i < 10) printf("    %d", i);
        else printf("   %d", i);
    }
    printf("\n");
}

void show_stats(PCB data[], int n, int history[], int h_len) {
    double avg_w = 0, avg_t = 0;
    int tot_burst = 0;
    int end_time = 0;

    // Update main table
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < pCount; j++) {
            if (pList[j].pid == data[i].pid) {
                data[i].t_turn = data[i].t_end - data[i].arrival;
                data[i].t_wait = data[i].t_turn - data[i].burst;
                data[i].status = TERMINATED;
                pList[j] = data[i];
                break;
            }
        }
        
        avg_w += data[i].t_wait;
        avg_t += data[i].t_turn;
        tot_burst += data[i].burst;

        if (data[i].t_end > end_time) end_time = data[i].t_end;
    }

    draw_gantt(history, h_len);

    printf("\n--- Final Metrics ---\n");
    printf("--------------------------------------------------------------------\n");
    printf("| PID | Arr | Burst | Prio | State      | Wait (WT) | Turn (TAT) |\n");
    printf("|-----|-----|-------|------|------------|-----------|------------|\n");

    for (int i = 0; i < n; i++) {
        printf("| %-3d | %-3d | %-5d | %-4d | TERMINATED | %-9d | %-10d |\n",
               data[i].pid, data[i].arrival, data[i].burst,
               data[i].priority, data[i].t_wait, data[i].t_turn);
    }
    printf("--------------------------------------------------------------------\n");

    double util = 0.0;
    if (end_time > 0) {
        util = ((double)tot_burst / end_time) * 100.0;
    }

    printf("\nSummary:\n");
    printf("Avg Waiting: %.2f\n", avg_w / n);
    printf("Avg Turnaround: %.2f\n", avg_t / n);
    printf("CPU Utilization: %.2f%%\n", util);
    printf("---------------------------\n");
}

// --- Scheduling Algos ---

void run_FCFS() {
    if (pCount == 0) { printf("No processes.\n"); return; }

    PCB temp[MAX_PROC];
    for(int i=0; i<pCount; i++) temp[i] = pList[i];
    
    bubble_sort_arr(temp, pCount);

    int timer = 0;
    int chart[1000];
    int c_idx = 0;

    for (int i = 0; i < pCount; i++) {
        while (timer < temp[i].arrival) {
            chart[c_idx++] = 0;
            timer++;
        }

        temp[i].t_start = timer;
        for (int t = 0; t < temp[i].burst; t++) {
            chart[c_idx++] = temp[i].pid;
            timer++;
        }
        temp[i].t_end = timer;
    }

    show_stats(temp, pCount, chart, c_idx);
}

void run_SJF() {
    if (pCount == 0) { printf("No processes.\n"); return; }

    PCB temp[MAX_PROC];
    for(int i=0; i<pCount; i++) temp[i] = pList[i];

    int timer = 0, done = 0;
    int visited[MAX_PROC] = {0};
    int chart[1000];
    int c_idx = 0;

    while (done < pCount) {
        int idx = -1;
        int min_b = 999999;

        for (int i = 0; i < pCount; i++) {
            if (temp[i].arrival <= timer && !visited[i]) {
                if (temp[i].burst < min_b) {
                    min_b = temp[i].burst;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            temp[idx].t_start = timer;
            for (int t = 0; t < temp[idx].burst; t++) {
                chart[c_idx++] = temp[idx].pid;
                timer++;
            }
            temp[idx].t_end = timer;
            visited[idx] = 1;
            done++;
        } else {
            chart[c_idx++] = 0;
            timer++;
        }
    }
    show_stats(temp, pCount, chart, c_idx);
}

void run_Priority() {
    if (pCount == 0) { printf("No processes.\n"); return; }

    PCB temp[MAX_PROC];
    for(int i=0; i<pCount; i++) temp[i] = pList[i];

    int timer = 0, done = 0;
    int visited[MAX_PROC] = {0};
    int chart[1000];
    int c_idx = 0;

    while (done < pCount) {
        int idx = -1;
        int best_p = 999999; 

        for (int i = 0; i < pCount; i++) {
            if (temp[i].arrival <= timer && !visited[i]) {
                if (temp[i].priority < best_p) {
                    best_p = temp[i].priority;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            temp[idx].t_start = timer;
            for (int t = 0; t < temp[idx].burst; t++) {
                chart[c_idx++] = temp[idx].pid;
                timer++;
            }
            temp[idx].t_end = timer;
            visited[idx] = 1;
            done++;
        } else {
            chart[c_idx++] = 0;
            timer++;
        }
    }
    show_stats(temp, pCount, chart, c_idx);
}

void run_RR(int q) {
    if (pCount == 0) { printf("No processes.\n"); return; }

    PCB temp[MAX_PROC];
    for(int i=0; i<pCount; i++) temp[i] = pList[i];
    
    bubble_sort_arr(temp, pCount);

    int timer = 0, done = 0;
    int chart[5000];
    int c_idx = 0;

    int que[1000], fr = 0, rr = 0;
    int in_q[MAX_PROC] = {0};

    // First process
    if (temp[0].arrival <= 0) {
        que[rr++] = 0;
        in_q[0] = 1;
    }

    while (done < pCount) {
        if (fr == rr) {
             int found = 0;
             for(int i=0; i<pCount; i++) {
                 if(!in_q[i] && temp[i].arrival <= timer && temp[i].remaining > 0) {
                     que[rr++] = i;
                     in_q[i] = 1;
                     found = 1;
                 }
             }
             if(!found) {
                 chart[c_idx++] = 0;
                 timer++;
                 for(int i=0; i<pCount; i++) {
                     if(!in_q[i] && temp[i].arrival <= timer && temp[i].remaining > 0) {
                         que[rr++] = i;
                         in_q[i] = 1;
                     }
                 }
             }
             continue;
        }

        int k = que[fr++];
        int slice = (temp[k].remaining < q) ? temp[k].remaining : q;

        if (temp[k].t_start == -1) temp[k].t_start = timer;

        for (int t = 0; t < slice; t++) {
            chart[c_idx++] = temp[k].pid;
            timer++;
        }
        temp[k].remaining -= slice;

        // Check new arrivals
        for (int i = 0; i < pCount; i++) {
            if (temp[i].remaining > 0 && temp[i].arrival <= timer && !in_q[i]) {
                que[rr++] = i;
                in_q[i] = 1;
            }
        }

        if (temp[k].remaining > 0) {
            que[rr++] = k;
        } else {
            temp[k].t_end = timer;
            done++;
        }
    }
    show_stats(temp, pCount, chart, c_idx);
}
