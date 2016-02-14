#include <iostream>
#include "utils.h"
using namespace std;

int main() {
    RESET_CCNT;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        GET_CCNT(time_start);
        for (int j = 0; j < NUM_ITER; ++j) {
        }
        for (int j = 0; j < NUM_ITER; ++j) {
        }
        for (int j = 0; j < NUM_ITER; ++j) {
        }
        for (int j = 0; j < NUM_ITER; ++j) {
        }
        for (int j = 0; j < NUM_ITER; ++j) {
        }
        GET_CCNT(time_end);
        time_trials[i] = time_end - time_start;
    }
    print_all_stats(time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);
    return 0;
}