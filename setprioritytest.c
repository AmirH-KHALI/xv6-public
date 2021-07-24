#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "user.h"
#include "x86.h"


void create_test_processes(int n, int idx) {

    int random_data_size = ((idx + 1) * 76235 + (n - idx) * 42423);
    malloc(idx * 10 * random_data_size * sizeof(char *));

    if (idx < n && fork() == 0)
        create_test_processes(n, idx + 1);
    else
        while(1);
}

int main(int argc, const char *argv[]) {

    int pcount = 10;

    int pid = fork();

    if (pid == 0) {
        create_test_processes(pcount - 2, 0);
        exit();
    }

    sleep(500);

    spri(40);

    int len;
    struct proc_info *procs = malloc(sizeof(struct proc_info) * NPROC);
    pdump(procs, &len);

    for (int i = 0; i < len; ++i) {
        printf(1, "id: %d, memsize: %d, priority: %d\n", procs[i].pid, procs[i].memsize, procs[i].priority);
    }

    exit();
}


