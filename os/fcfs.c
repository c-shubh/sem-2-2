#include <stdio.h>
#include <stdlib.h>

typedef struct Process
{
  int pid;
  float at;
  float bt;
  float ft;
  float tat;
  float wat;
} Process;

int comparator(const void *a, const void *b)
{
  const Process *p = a;
  const Process *q = b;
  if (p->at > q->at)
    return 1;
  if (p->at < q->at)
    return -1;
  return 0;
}

int main()
{
  int n;
  printf("No. of processes: ");
  scanf("%d", &n);

  Process p[n];
  printf("Process info: number, arrival time, burst time:\n");
  for (int i = 0; i < n; i++)
    scanf("%d %f %f", &p[i].pid, &p[i].at, &p[i].bt);

  qsort(p, n, sizeof(Process), comparator);

  float finishTime[n];
  for (int i = 0; i < n; i++)
  {
    if (i == 0 || p[i].at > finishTime[i - 1])
      finishTime[i] = p[i].at + p[i].bt;
    else
      finishTime[i] = finishTime[i - 1] + p[i].bt;
    p[i].ft = finishTime[i];
    p[i].tat = finishTime[i] - p[i].at;
    p[i].wat = finishTime[i] - p[i].at - p[i].bt;
  }

  printf("\n%-6s %-6s %-6s %-6s %-6s %-6s\n", "pid", "at", "bt", "ft", "tat", "wat");
  for (int i = 0; i < n; i++)
    printf("%-6d %-6.2f %-6.2f %-6.2f %-6.2f %-6.2f\n", p[i].pid, p[i].at, p[i].bt,
           p[i].ft, p[i].tat, p[i].wat);

  float avgtat = 0, avgwat = 0;
  for (int i = 0; i < n; i++)
  {
    avgtat += p[i].tat;
    avgwat += p[i].wat;
  }
  avgtat /= n;
  avgwat /= n;
  printf("\nAverage:\n\tturnaround time: %.2f\n\twaiting time: %.2f\n", avgtat,
         avgwat);
}