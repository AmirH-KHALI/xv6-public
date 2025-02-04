#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "user.h"
#include "x86.h"


int main(int argc, const char *argv[]) {

    int pcount = 10;
    int pids[NPROC];

    for (int i = 0; i < pcount; ++i) {
        pids[i] = fork();
        if (!pids[i]) {

            int random_data_sz = ((i + 1) * 76235 + (pcount - i) * 42423);
            char *data = malloc(sizeof(char) * random_data_sz);
            memset(data, random_data_sz, sizeof(char) * random_data_sz);

            while (1);
        }
    }

    sleep(50);

    int len;
    struct proc_info *procs = malloc(sizeof(struct proc_info) * NPROC);
    pdump(procs, &len);

    for (int i = 0; i < len; ++i) {
        printf(1, "id: %d, memsize: %d\n", procs[i].pid, procs[i].memsize);
    }

    for (int i = 0; i < pcount; ++i) {
        kill(pids[i]);
        wait();
    }

    free(procs);

    exit();
}
