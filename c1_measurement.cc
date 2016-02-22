#include "utils.h"

// experiment repetitions
#define NUM_TRIAL  10000
#define NUM_ITER   200
#define NUM_UNROLL 5
unsigned long time_trials[NUM_TRIAL];

/*
We define two types of measurement overhead:
Type 1: overhead per measurement
t_loop * NUM_ITER + t_readcycle
Type 2: overhead per operation
(t_loop * NUM_ITER + t_readcycle) / (NUM_ITER * NUM_UNROLL)
*/
int main() {
    // cycle register read overhead
    RESET_CCNT;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        GET_CCNT(time_start);
        GET_CCNT(time_end);
        time_trials[i] = time_end - time_start;
    }
    std::cout << "##### Register read overhead:" << std::endl;
    print_all_stats(time_trials, NUM_TRIAL, 1, 1);

    // register read overhead + loop overhead
    RESET_CCNT;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        GET_CCNT(time_start);
        for (int j = 0; j < NUM_ITER; ++j) {
            // do operation NUM_UNROLL times
        }
        GET_CCNT(time_end);
        time_trials[i] = time_end - time_start;
    }
    std::cout << "##### Loop + register read overhead:" << std::endl;
    print_all_stats(time_trials, NUM_TRIAL, 1, 1);

    return 0;
}