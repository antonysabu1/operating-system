# 🖥️ Operating System Programs – C Language

This repository contains a collection of Operating System (OS) programs implemented in C. These programs cover core OS concepts such as CPU scheduling, memory management, process synchronization, and deadlock avoidance algorithms — typically studied in the 3rd or 4th semester of Computer Science & Engineering courses.

---

## 📌 Programs Included

| Program File                                | Description                                    |
|---------------------------------------------|------------------------------------------------|
| `CPU SCHEDULING - FCFS.c`                   | First-Come-First-Serve (FCFS) scheduling       |
| `CPU SCHEDULING - SJF.c`                    | Shortest Job First (SJF) scheduling            |
| `CPU SCHEDULING - ROUND ROBIN.c`            | Round Robin CPU scheduling                     |
| `CPU SCHEDULING - PRIORITY SCHEDULING.c`    | Priority-based CPU scheduling                  |
| `bankers algorithm.c`                       | Banker's Algorithm for deadlock avoidance      |
| `disk_scheduling.c`                         | Disk scheduling algorithms (e.g., FCFS, SCAN)  |
| `factshare.c`                               | Example program for shared memory/fork usage   |
| `memory_allocation.c`                       | Memory allocation strategies (First fit, etc.) |
| `page_replacement.c`                        | Page replacement algorithms (FIFO, LRU, etc.)  |
| `semaphore.c`                               | Semaphore implementation for synchronization   |

---

## 🛠️ How to Compile & Run

Use GCC (GNU Compiler Collection) or any C compiler:

```bash
gcc program_name.c -o program_name
./program_name
