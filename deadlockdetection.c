#include <stdio.h>

int n_processes, n_resources;

void detectDeadlock(int available[], int max_resources[][n_resources], int allocation[][n_resources]) {
    int work[n_resources], finish[n_processes], safe_sequence[n_processes];
    int i, j, process_count = 0;

    for (i = 0; i < n_resources; i++) {
        work[i] = available[i];
    }

    for (i = 0; i < n_processes; i++) {
        finish[i] = 0;
    }

    while (process_count < n_processes) {
        int found = 0;
        for (i = 0; i < n_processes; i++) {
            if (finish[i] == 0) {
                int can_allocate = 1;
                for (j = 0; j < n_resources; j++) {
                    if (max_resources[i][j] - allocation[i][j] > work[j]) {
                        can_allocate = 0;
                        break;
                    }
                }

                if (can_allocate) {
                    for (j = 0; j < n_resources; j++) {
                        work[j] += allocation[i][j];
                    }
                    safe_sequence[process_count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("Deadlock detected!\n");
            return;
        }
    }

    printf("No deadlock detected. Safe sequence: ");
    for (i = 0; i < n_processes; i++) {
        printf("%d ", safe_sequence[i]);
    }
    printf("\n");
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &n_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &n_resources);

    int max_resources[n_processes][n_resources], allocation[n_processes][n_resources], available[n_resources];

    printf("Enter the maximum resources for each process:\n");
    for (int i = 0; i < n_processes; i++) {
        for (int j = 0; j < n_resources; j++) {
            scanf("%d", &max_resources[i][j]);
        }
    }

    printf("Enter the allocated resources for each process:\n");
    for (int i = 0; i < n_processes; i++) {
        for (int j = 0; j < n_resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the available resources: ");
    for (int i = 0; i < n_resources; i++) {
        scanf("%d", &available[i]);
    }

    detectDeadlock(available, max_resources, allocation);

    return 0;
}
