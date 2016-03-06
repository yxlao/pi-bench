#include <unistd.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include "utils.h"

// experiment repetitions
#define NUM_TRIAL  10000
#define NUM_ITER   200
#define NUM_UNROLL 5
unsigned long time_trials[NUM_TRIAL];

int main() {
    struct timeval start;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        RESET_CCNT;
        GET_CCNT(time_start);
        for (int j = 0; j < NUM_ITER; ++j) {
            gettimeofday(&start, NULL);
            gettimeofday(&start, NULL);
            gettimeofday(&start, NULL);
            gettimeofday(&start, NULL);
            gettimeofday(&start, NULL);
        }
        GET_CCNT(time_end);
        time_trials[i] = time_end - time_start;
    }
    std::cout << "## Syscall" << std::endl;
    print_all_stats(time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);

    return 0;
}
