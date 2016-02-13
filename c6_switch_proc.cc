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
    unsigned total = 0;

    // pipes
    int fd[2];
    pipe(fd);

    // pid_t
    pid_t cpid;

    for (int i = 0; i < STD_ITER; ++i) {
        // fork
        cpid = fork();

        // parent
        if (cpid != 0) {
            GET_CCNT(start);
            wait(NULL);
            read(fd[0], (void*)&end, sizeof(unsigned));
        } else {
            GET_CCNT(end);
            write(fd[1], (void*)&end, sizeof(unsigned));
            exit(1);
        }
        total += end - start;
    }
    cout << 1. * total / STD_ITER << endl;
    return 0;
}
