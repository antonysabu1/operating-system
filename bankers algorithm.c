#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int allocation[MAX_PROCESSES][MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int available[MAX_RESOURCES];
int n, m;

bool check(int i) {
    for (int j = 0; j < m; j++) {
        if (need[i][j] > available[j])
            return false;
    }
    return true;
}

int main() {
    printf("Enter the number of Processes: ");
    scanf("%d", &n);

    printf("Enter the number of Resources: ");
    scanf("%d", &m);

    // Allocation matrix input
    for (int i = 0; i < n; i++) {
        printf("Enter the number of instances allocated for Process P%d:\n", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Max matrix input
    for (int i = 0; i < n; i++) {
        printf("Enter Max matrix entry for Process P%d:\n", i);
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Available resources input
    printf("Enter the number of instances available of Resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    // Calculate Need matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Banker's Algorithm
    char sequence[MAX_PROCESSES][4]; // to hold strings like "P0"
    int visited[MAX_PROCESSES] = {0};
    int count = 0;

    while (count < n) {
        bool safe = false;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && check(i)) {
                // Mark process as visited and simulate resource release
                visited[i] = 1;
                sprintf(sequence[count], "P%d", i);
                count++;
                safe = true;

                for (int j = 0; j < m; j++) {
                    available[j] += allocation[i][j];
                }
            }
        }
        if (!safe) {
            break; // No safe process found — unsafe state
        }
    }

    // Output
    if (count < n) {
        printf("\nThe System is Unsafe!\n");
    } else {
        printf("\nThe System is Safe!\n");
        printf("Safe Sequence is: ");
        for (int i = 0; i < n; i++) {
            printf("%s ", sequence[i]);
        }

        printf("\nAvailable resources after completion: ");
        for (int i = 0; i < m; i++) {
            printf("%d ", available[i]);
        }
        printf("\n");
    }

    return 0;
}
