#include <stdio.h>
#include <string.h>

int q[100], front = -1, rear = -1;

struct process {
    char name[20];
    int at, bt, wt, tt, ct;
    int left, status;
} p[20];

struct done {
    char name[20];
    int st, ct;
} d[20];

// Enqueue operation for ready queue
void enqueue(int j) {
    if (front == -1 && rear == -1)
        front = 0;
    rear++;
    q[rear] = j;
}

// Dequeue operation for ready queue
int dequeue() {
    int item = q[front];
    if (front == rear)
        front = rear = -1;
    else
        front++;
    return item;
}

int main() {
    int n, i, j, t, k, ls = 0, num = 0, idle = 0;
    float avwt = 0, avtt = 0;

    printf("ENTER THE NUMBER OF PROCESSES: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nENTER DETAILS OF PROCESS %d", i + 1);
        printf("\nPROCESS NAME: ");
        scanf(" %s", p[i].name);
        printf("ARRIVAL TIME: ");
        scanf("%d", &p[i].at);
        printf("BURST TIME: ");
        scanf("%d", &p[i].bt);
        p[i].left = p[i].bt;
        p[i].status = 0;
    }

    printf("\nENTER THE TIME QUANTUM: ");
    scanf("%d", &t);

    for (i = 0; ls < n;) {
        for (j = 0; j < n; j++) {
            if (p[j].status == 0 && p[j].at <= i) {
                enqueue(j);
                p[j].status = 1;
            }
        }

        if (idle == 0 && front == -1) {
            strcpy(d[num].name, "Idle");
            d[num].st = i;
            idle = 1;
            i++;
        } else if (front != -1) {
            if (idle == 1) {
                d[num].ct = i;
                idle = 0;
                num++;
            }

            k = dequeue();
            d[num].st = i;
            strcpy(d[num].name, p[k].name);

            if (p[k].left <= t) {
                d[num].ct = i + p[k].left;
                p[k].ct = d[num].ct;
                i = d[num].ct;
                p[k].tt = i - p[k].at;
                p[k].wt = p[k].tt - p[k].bt;
                p[k].status = 2;
                ls++;
                num++;
            } else {
                d[num].ct = i + t;
                i = d[num].ct;
                p[k].left -= t;
                num++;

                for (j = 0; j < n; j++) {
                    if (p[j].status == 0 && p[j].at <= i) {
                        enqueue(j);
                        p[j].status = 1;
                    }
                }
                enqueue(k);  // Re-queue the same process
            }
        } else {
            i++;
        }
    }

    printf("\nPROCESS NAME\tCOMPLETION TIME\tWAITING TIME\tTURNAROUND TIME\n\n");
    for (i = 0; i < n; i++) {
        printf("%10s\t\t%5d\t\t%5d\t\t%5d\n",
               p[i].name, p[i].ct, p[i].wt, p[i].tt);
        avwt += p[i].wt;
        avtt += p[i].tt;
    }

    printf("\n\nGANTT CHART:\n");
    printf("\t------------------------------------------------------------\n\t");
    for (i = 0; i < num; i++) {
        printf("| %s\t", d[i].name);
    }
    printf("|\n\t------------------------------------------------------------\n\t");
    for (i = 0; i < num; i++) {
        printf("%d\t", d[i].st);
    }
    printf("%d\n", d[num - 1].ct);

    printf("\nAVERAGE WAITING TIME: %.2f ms", avwt / n);
    printf("\nAVERAGE TURNAROUND TIME: %.2f ms\n", avtt / n);

    return 0;
}

