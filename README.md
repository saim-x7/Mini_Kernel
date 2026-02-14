Mini OS-Kernel Simulator 

🖥️A lightweight Operating System Simulator written in C.This project simulates the core functionalities of an OS kernel, focusing on Process Scheduling and Memory Management. 
It provides a CLI environment to create processes, visualize CPU scheduling algorithms, and manage RAM allocation dynamically.


🚀 Features
1. Process Scheduling (CPU)Implemented standard scheduling algorithms to demonstrate different strategies for CPU resource allocation:
     FCFS (First-Come, First-Served): Non-preemptive.
     SJF (Shortest Job First): Non-preemptive.
     Priority Scheduling: Non-preemptive (Lower number = Higher priority).
     Round Robin (RR): Preemptive with configurable Time Quantum.

Visualization:
    Generates a text-based Gantt Chart for every simulation.
    Calculates Average Waiting Time, Turnaround Time, and CPU Utilization.
    
2. Memory Management (RAM)
   Simulates a Contiguous Memory Allocation system with a variable partition scheme:

   Allocation Strategies:
   First Fit:Allocates the first available block that fits.
   Best Fit: Allocates the smallest block that fits (minimizes wasted space).
   Worst Fit: Allocates the largest block available.

   Deallocation & Coalescing:
   Frees memory blocks by PID.
   Auto-Merge: Automatically merges adjacent free blocks to reduce external fragmentation.

   🛠️ Project Structure
   main.c: The entry point. Handles the CLI menu and user input.
   scheduler.c: Contains logic for FCFS, SJF, Priority, and Round Robin algorithms.
   memory_mgr.c: Manages the RAM array, allocation logic, and memory coalescing.
   process_mgr.c: Handles creation, deletion, and storage of PCB (Process Control Blocks).
   shared.h: Defines common structures (PCB, Block) and constants.
   Makefile: Automates the compilation process.


   💻 Installation & UsagePrerequisites
   GCC CompilerMake (Optional, but recommended)
   1. Clone the RepositoryBashgit clone https://github.com/saim-x7/mini-os-kernel.git
      -->cd mini-os-kernel
    CompileUse the included Makefile to compile the source code:
      -->make
Or manually: gcc -Wall -std=c11 -o simulator main.c process_mgr.c scheduler.c memory_mgr.c3. 
then  --> ./simulator
