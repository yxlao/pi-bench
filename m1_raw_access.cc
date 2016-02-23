#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

// experiment repetitions
#define NUM_TRIAL  10000
#define NUM_ITER   200
#define NUM_UNROLL 5
unsigned long time_trials[NUM_TRIAL];

// maximum size of integer array
#define MAX_INT_ARRAY_SIZE 67108864 // 2^26=64M ints, 256M bytes

// deprecated random index
// #include <time.h>
// time_t t;
// srand((unsigned)time(&t));
// ind = (unsigned int)((float)rand() / (float)RAND_MAX * size);

void flush_write(int* data, int max_ind) {
    for (int i = 0; i < max_ind; i++) {
        data[i] = i % 10;
    }
    return;
}

int main() {
    // allocate data
    int* data = new int[MAX_INT_ARRAY_SIZE];
    flush_write(data, MAX_INT_ARRAY_SIZE);

    int temp, real_ind;
    unsigned long ind;
    int size = 1;

    for (int step = 0; step < 27; step++) {
        // init
        size = (int) pow(2, step);
        ind = 0;
        flush_write(data, size);
        RESET_CCNT;
        // run
        for (int i = 0; i < NUM_TRIAL; i++) {
            real_ind  = ind % size;
            GET_CCNT(time_start);
            temp = data[real_ind];
            GET_CCNT(time_end);
            time_trials[i] = time_end - time_start;
            ind += 8;
        }
        // finishing
        std::cout << step << ": " << size << std::endl;
        print_trimmed_mean_std(time_trials, NUM_TRIAL, 1, 1);
    }

    // clen-ups
    (void) temp;
    delete data;
    return 0;
}
