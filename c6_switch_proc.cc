#include <iostream>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "utils.h"
using namespace std;

int main() {
    RESET_CCNT;
    // pipes
    int fd[2];
    pipe(fd);

    // pid_t
    pid_t cpid;

    for (int i = 0; i < NUM_ITER; ++i) {
        // fork
        cpid = fork();

        // parent
        if (cpid != 0) {
            GET_CCNT(time_start);
            wait(NULL);
            read(fd[0], (void*)&time_end, sizeof(unsigned));
        } else {
            GET_CCNT(time_end);
            write(fd[1], (void*)&time_end, sizeof(unsigned));
            exit(1);
        }
        time_total += time_end - time_start;
    }
    cout << 1. * time_total / NUM_ITER << endl;
    return 0;
}
