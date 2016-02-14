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

    for (int i = 0; i < NUM_TRIAL; ++i) {
        // get start
        GET_CCNT(time_start);
        // fork
        cpid = fork();
        // parent
        if (cpid != 0) {
            wait(NULL);
            read(fd[0], (void*)&time_end, sizeof(unsigned long));
        } else {
            GET_CCNT(time_end);
            write(fd[1], (void*)&time_end, sizeof(unsigned long));
            exit(1);
        }
        time_trials[i] = time_end - time_start;
    }

    print_all_stats(time_trials, NUM_TRIAL, 1, 1);

    return 0;
}
