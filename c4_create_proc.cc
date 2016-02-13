#include <iostream>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "utils.h"
using namespace std;

int main() {
    RESET_CCNT;
    unsigned start;
    unsigned end;

    // pipes
    int fd[2];
    pipe(fd);

    // pid_t
    pid_t cpid;

    for (int i = 0; i < NUM_ITER; ++i) {
        // get start
        GET_CCNT(start);
        // fork
        cpid = fork();
        // parent
        if (cpid != 0) {
            wait(NULL);
            read(fd[0], (void*)&end, sizeof(unsigned));
        } else {
            GET_CCNT(end);
            write(fd[1], (void*)&end, sizeof(unsigned));
            exit(1);
        }
        time_total += end - start;
    }
    cout << 1. * time_total / NUM_ITER << endl;
    return 0;
}
