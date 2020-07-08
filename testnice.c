#include "types.h"
#include "stat.h"
#include "user.h"
#include "proc_info.h"

//print process info with formatting
void print_proc(struct proc_info *info) {
  printf(0, "\nPID: %d | NAME: %s | MEMSIZE: %d | PRIORITY: %d | LVL: %d\n" , info -> pid, info -> name, info -> memsize, info -> priority, info -> level);
}

void print_processes(struct proc_info *p) 
{
    printf(0, "\nList of processes that are RUNNING or RUNNABLE sorted by memsize:");
    for (int i = 0; i < 100; i++)
    {
      if (p[i].pid == 0) break; //A zero pid indicates the end of process list
      print_proc(&p[i]);
    }
}

//                     ind 0  1  2  3  4  5  6  7  8  9  10
int test_queue_lvl[100] = {1, 2, 3, 1, 1, 2, 3, 1, 1, 2, 3};

/**
 * A recursive procedure used to create the test processes.
 */
void create_test_processes(int pcnt, int idx)
{
  if (idx == pcnt) while(1); //NOP

  int pid = fork();

  if (pid == 0) create_test_processes(pcnt, idx + 1);
  else if (pid > 0) {while (1); //NOP
  }
  else printf(0, "E: fork error");
}

int main(void)
{
  struct proc_info p[100];
  
  int pid = fork();

  if (pid > 0)
  {
    sleep(300);
    printf(0, "Changing queue level for process with pid=%d to %d\n", pid, 2);
    nice(pid, 2);
    rnps(p);
    print_processes(p);
  } else if (pid == 0)
  {
    create_test_processes(10, 0);
  } else
  {
    printf(0, "E: fork error in main");
  }

  exit();
}
