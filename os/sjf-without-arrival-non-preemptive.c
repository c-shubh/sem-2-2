#include <stdio.h>
#include <stdlib.h>

// Define a structure to represent a process
typedef struct
{
    int id;
    int burst_time;
    int finish_time;
    int turnaround_time;
    int waiting_time;
} Process;

// Comparison function for sorting the processes based on their burst time
int compare(const void *a, const void *b)
{
    Process *p1 = (Process *)a;
    Process *p2 = (Process *)b;
    return (p1->burst_time - p2->burst_time);
}

int main()
{
    int n, i;
    float avg_turnaround_time, avg_waiting_time;
    Process processes[50];
    float total_waiting_time = 0, total_turnaround_time = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input burst time for each process and assign process IDs
    for (i = 0; i < n; i++)
    {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].id = i + 1;
    }

    // Sort the processes based on their burst time (in ascending order)
    qsort(processes, n, sizeof(Process), compare);

    // Calculate finish time, turnaround time, and waiting time for each process
    int time = 0;
    for (i = 0; i < n; i++)
    {
        processes[i].finish_time = time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].finish_time;
        processes[i].waiting_time = time;
        time = processes[i].finish_time;
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    // Calculate average waiting time and average turnaround time
    avg_waiting_time = total_waiting_time / n;
    avg_turnaround_time = total_turnaround_time / n;

    // Output results
    printf("\nProcess\tBurst Time\tFinish Time\tTurnaround Time\tWaiting Time");
    for (i = 0; i < n; i++)
    {
        printf("\nP%d\t\t%d\t\t%d\t\t%d\t\t\t%d", processes[i].id, processes[i].burst_time, processes[i].finish_time, processes[i].turnaround_time, processes[i].waiting_time);
    }
    printf("\n\nAverage Waiting Time: %.2f", avg_waiting_time);
    printf("\nAverage Turnaround Time: %.2f", avg_turnaround_time);

    return 0;
}
