#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "utils.h"

// experiment repetitions
#define NUM_TRIAL  1
#define NUM_ITER   200
#define NUM_UNROLL 5
unsigned long time_trials[NUM_TRIAL];

int main() {
    // pipes
    int c2p[2];
    int p2c[2];
    pipe(c2p);
    pipe(p2c);
    int temp;

    // pid_t
    pid_t cpid;

    for (int i = 0; i < NUM_TRIAL; ++i) {
        RESET_CCNT;
        // fork
        cpid = fork();
        if (cpid != 0) {
            // parent
            close(c2p[1]);
            close(p2c[0]);
            temp = 123124;
            GET_CCNT(time_start);
            read(c2p[0], &temp, sizeof(unsigned long));
            std::cout << "parent read " << temp << std::endl;
            temp = 101;
            write(p2c[1], &temp, sizeof(unsigned long));
            std::cout << "parent write " << temp << std::endl;
            GET_CCNT(time_end);
            wait(NULL); // wait all child process to finish
        } else {
            // children
            close(c2p[0]);
            close(p2c[1]);
            temp = 100;
            write(c2p[1], &temp, sizeof(unsigned long));
            std::cout << "child write " << temp << std::endl;
            read(p2c[0], &temp, sizeof(unsigned long));
            std::cout << "child read " << temp << std::endl;
            exit(1);
        }
        if (time_end > time_start) {
            time_trials[i] = time_end - time_start;
        } else {
            i--;
        }
    }

    print_all_stats(time_trials, NUM_TRIAL, 1, 1);

    return 0;
}
