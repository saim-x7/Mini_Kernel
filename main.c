


#include <stdio.h>
#include "shared.h"
#include "process_mgr.h"
#include "scheduler.h"
#include "memory_mgr.h"

    void display_info() {
    printf("\n**********************************************************************************************");
    printf("\n***                                   MINI OS-KERNEL                                       ***");
    printf("\n***                                 ------------------                                     ***");
    printf("\n*** Designed By:                                                                           ***");
    printf("\n***                                                                                        ***");
    printf("\n***                               SAIM ALI RIAZ  (230652).                                 ***");
    printf("\n***                               M.RAMISH FARAZ (230660).                                 ***");
    printf("\n***                               M.QASIM KHAN   (230618).                                 ***");
    printf("\n**********************************************************************************************\n");
}

int main() {
    int opt;
    
    // Initialize modules
    init_proc_list();
    init_mem(64);

    create_process(0, 5, 2, 10);
    create_process(2, 3, 1, 5);
    create_process(4, 1, 4, 2);
    create_process(6, 7, 3, 20);

    display_info();

    do {
        printf("\n[ MAIN MENU ]\n");
        printf("1. Processes\n");
        printf("2. Scheduling\n");
        printf("3. Memory\n");
        printf("4. Reset\n");
        printf("5. Exit\n");
        printf(">> ");
        
        if (scanf("%d", &opt) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (opt) {
            case 1: { // Processes
                int sub;
                printf("\n1. View Table\n2. Add Process\n>> ");
                scanf("%d", &sub);
                if (sub == 1) print_p_table();
                else if (sub == 2) {
                    int a, b, p, m;
                    printf("Arr Burst Prio Mem: ");
                    scanf("%d %d %d %d", &a, &b, &p, &m);
                    create_process(a, b, p, m);
                }
                break;
            }
            case 2: { // Scheduling
                int algo;
                printf("\n1. FCFS\n2. SJF\n3. RR\n4. Priority\n>> ");
                scanf("%d", &algo);
                if (algo == 1) run_FCFS();
                else if (algo == 2) run_SJF();
                else if (algo == 3) {
                    int q;
                    printf("Quantum: ");
                    scanf("%d", &q);
                    run_RR(q);
                }
                else if (algo == 4) run_Priority();
                break;
            }
            case 3: { // Memory
                int m_opt;
                printf("\n1. Set Size\n2. View Map\n3. Alloc\n4. Free\n>> ");
                scanf("%d", &m_opt);
                if (m_opt == 1) {
                    int u; printf("Size: "); scanf("%d", &u);
                    init_mem(u);
                }
                else if (m_opt == 2) show_mem_map();
                else if (m_opt == 3) {
                    int pid, sz, alg;
                    printf("PID Size Algo(1=FF,2=BF,3=WF): "); 
                    scanf("%d %d %d", &pid, &sz, &alg);
                    int r = -1;
                    if (alg == 1) r = mem_alloc_first(pid, sz);
                    else if (alg == 2) r = mem_alloc_best(pid, sz);
                    else if (alg == 3) r = mem_alloc_worst(pid, sz);
                    
                    if (r != -1) printf("Allocated at %d\n", r);
                    else printf("Failed.\n");
                }
                else if (m_opt == 4) {
                    int id; printf("PID: "); scanf("%d", &id);
                    printf("Freed %d units.\n", mem_free(id));
                }
                break;
            }
            case 4: { // Reset
                int r;
                printf("\n1. Reset Stats\n2. Delete All\n>> ");
                scanf("%d", &r);
                if (r == 1) clear_stats();
                else if (r == 2) clear_all_proc();
                break;
            }
            case 5: printf("Bye.\n"); break;
            default: printf("Invalid.\n");
        }

    } while (opt != 5);

    return 0;
}
