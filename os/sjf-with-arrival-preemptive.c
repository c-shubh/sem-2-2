#include <stdio.h>
#include <stdlib.h>

// Process structure
typedef struct
{
  int pid;            // process ID
  int burst_time;     // burst time of the process
  int remaining_time; // remaining time of the process
  int arrival_time;   // arrival time of the process
  int waiting_time;   // waiting time of the process
} process;

// Comparison function for qsort
int compare_arrival_time(const void *a, const void *b)
{
  const process *pa = (const process *)a;
  const process *pb = (const process *)b;
  return pa->arrival_time - pb->arrival_time;
}

int main()
{
  int n, i, j, t, total_waiting_time = 0, total_turnaround_time = 0;
  float avg_waiting_time, avg_turnaround_time;
  process temp;

  // Read the number of processes
  printf("Enter the number of processes: ");
  scanf("%d", &n);

  // Allocate memory for the process array
  process *processes = malloc(n * sizeof(process));

  // Read the arrival time and burst time of each process
  for (i = 0; i < n; i++)
  {
    printf("Enter the arrival time and burst time of process %d: ", i + 1);
    scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
    processes[i].pid = i + 1;
    processes[i].remaining_time = processes[i].burst_time;
    processes[i].waiting_time = 0;
  }

  // Sort the processes by arrival time
  qsort(processes, n, sizeof(process), compare_arrival_time);

  // Run the scheduling algorithm
  int current_time = 0, completed = 0;
  while (completed < n)
  {
    // Find the process with the shortest remaining time
    int shortest = -1;
    for (i = 0; i < n; i++)
    {
      if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0)
      {
        if (shortest == -1 || processes[i].remaining_time < processes[shortest].remaining_time)
        {
          shortest = i;
        }
      }
    }

    if (shortest == -1)
    {
      // No process is ready to run, advance time
      current_time++;
    }
    else
    {
      // Run the selected process for one unit of time
      processes[shortest].remaining_time--;
      current_time++;

      if (processes[shortest].remaining_time == 0)
      {
        // The process has completed
        completed++;
        t = current_time;
        processes[shortest].waiting_time = t - processes[shortest].arrival_time - processes[shortest].burst_time;
        total_waiting_time += processes[shortest].waiting_time;
        total_turnaround_time += t - processes[shortest].arrival_time;
      }
    }
  }

  // Calculate the average waiting time and turnaround time
  avg_waiting_time = (float)total_waiting_time / n;
  avg_turnaround_time = (float)total_turnaround_time / n;

  // Print the results
  printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
  for (i = 0; i < n; i++)
  {
    printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].waiting_time + processes[i].burst_time);
  }
  printf("Average waiting time: %.2f\n", avg_waiting_time);
  printf("Average turnaround time: %.2f\n", avg_turnaround_time);

  // Free the memory allocated for the process array
  free(processes);

  return 0;
}