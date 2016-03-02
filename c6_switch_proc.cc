#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "utils.h"

// experiment repetitions
#define NUM_TRIAL  10000
#define NUM_ITER   200
#define NUM_UNROLL 5
unsigned long time_trials[NUM_TRIAL];

int main() {
    // pipes
    int c2p[2];
    pipe(c2p);

    // pid_t
    pid_t cpid;

    for (int i = 0; i < NUM_TRIAL; ++i) {
        RESET_CCNT;
        // fork
        cpid = fork();
        if (cpid != 0) {
            // parent
            GET_CCNT(time_start);
            wait(NULL);
            read(c2p[0], (void*)&time_end, sizeof(unsigned long));
            // std::cout << "parent read 0" << std::endl;
        } else {
            // children
            GET_CCNT(time_end);
            write(c2p[1], (void*)&time_end, sizeof(unsigned long));
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
