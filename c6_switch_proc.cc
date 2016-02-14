#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "utils.h"

int main() {
    // pipes
    int fd[2];
    pipe(fd);

    // pid_t
    pid_t cpid;

    for (int i = 0; i < NUM_TRIAL; ++i) {
        RESET_CCNT;
        // fork
        cpid = fork();
        // parent
        if (cpid != 0) {
            GET_CCNT(time_start);
            wait(NULL);
            read(fd[0], (void*)&time_end, sizeof(unsigned long));
        } else {
            GET_CCNT(time_end);
            write(fd[1], (void*)&time_end, sizeof(unsigned long));
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
