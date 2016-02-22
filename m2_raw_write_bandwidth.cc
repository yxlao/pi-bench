#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "utils.h"
using namespace std;

// experiment repetitions
#define NUM_TRIAL  10000
#define NUM_ITER   200
#define NUM_UNROLL 5
unsigned long time_trials[NUM_TRIAL];

int main() {
    int i, j;
    char * data = new char[4194304];//4MByte = 4194304 Chars
    for (int i = 0; i < 4194304; i++) {
        data[i] = 'a' + i % ('z' - 'a');
    }
    //write test
    for (i = 0; i < NUM_TRIAL; i++) {
        RESET_CCNT;
        GET_CCNT(time_start);
        for (j = 0; j < 4194304; j++) {
            data[j] = 'a';
        }
        GET_CCNT(time_end);
        time_trials[i] = time_end - time_start;
    }
    print_trimmed_mean_std(time_trials, NUM_TRIAL, 1, 1);
    delete data;
    return 0;
}
