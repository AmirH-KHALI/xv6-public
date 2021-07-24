#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, const char *argv[]) {

    int wtime = 0;
    int rtime = 0;

    if (fork() == 0) {
        sleep(10);
        printf(1, "Child Sleep\n");
        sleep(400);
        printf(1, "Child Done\n");
        exit();
    }

    printf(1, "Parent Wait\n");
    waitx(&wtime, &rtime);
    printf(1, "Parent Done with wtime: %d, rtime: %d\n", wtime, rtime);

    exit();
}
