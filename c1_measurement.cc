#include <iostream>
#include "utils.h"
using namespace std;

/*
We define two types of measurement overhead:
Type 1: overhead per measurement
t_loop * NUM_ITER + t_readcycle
Type 2: overhead per operation
(t_loop * NUM_ITER + t_readcycle) / (NUM_ITER * NUM_UNROLL)
*/
int main() {
    // overhead per measurement
    RESET_CCNT;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        GET_CCNT(time_start);
        for (int j = 0; j < NUM_ITER; ++j) {
        }
        GET_CCNT(time_end);
        time_trials[i] = time_end - time_start;
    }
    cout << "## Overhead per measurement:" << endl;
    print_all_stats(time_trials, NUM_TRIAL, 1, 1);

    // overhead per operation
    RESET_CCNT;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        GET_CCNT(time_start);
        for (int j = 0; j < NUM_ITER; ++j) {
        }
        GET_CCNT(time_end);
        time_trials[i] = time_end - time_start;
    }
    for (int i = 0; i < NUM_TRIAL; ++i) {
        time_trials[i] = (unsigned long) ((float)time_trials[i] /
                                          (float)NUM_ITER /
                                          (float)NUM_UNROLL);
    }
    cout << "Overhead per operation:" << endl;
    print_all_stats(time_trials, NUM_TRIAL, 1, 1);
    return 0;
}