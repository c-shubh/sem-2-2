#include <stdio.h>
#include <stdlib.h>

// Define the process struct
typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int finish_time;
    int turnaround_time;
    int waiting_time;
} process;

// Define a function to compare processes by burst time
int cmpfunc(const void *a, const void *b) {
    process *p1 = (process *)a;
    process *p2 = (process *)b;
    return p1->burst_time - p2->burst_time;
}

int main() {
    int n, i;
    float total_wait = 0, total_turnaround = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    process p[n];

    // Input the process arrival times and burst times
    for (i = 0; i < n; i++) {
        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
        p[i].pid = i + 1;
    }

    // Sort the processes by burst time using the qsort function
    qsort(p, n, sizeof(process), cmpfunc);

    // Calculate the finish time, turnaround time, and waiting time for each process
    for (i = 0; i < n; i++) {
        if (i == 0) {
            // The first process starts running at its arrival time
            p[i].finish_time = p[i].arrival_time + p[i].burst_time;
        } else {
            // The next process starts running after the previous process finishes
            p[i].finish_time = p[i-1].finish_time + p[i].burst_time;
        }
        p[i].turnaround_time = p[i].finish_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        total_wait += p[i].waiting_time;
        total_turnaround += p[i].turnaround_time;
    }

    // Print the process table
    printf("\nProcess\tArrival Time\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", p[i].pid, p[i].arrival_time, p[i].burst_time,
            p[i].finish_time, p[i].turnaround_time, p[i].waiting_time);
    }

    // Calculate and print the average waiting time and average turnaround time
    printf("\nAverage Waiting Time: %f\n", total_wait/n);
    printf("Average Turnaround Time: %f\n", total_turnaround/n);

    return 0;
}
