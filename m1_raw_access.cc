#include <iostream>
#include <stdlib.h>
#include "utils.h"

// experiment repetitions
#define NUM_TRIAL  10000
#define NUM_ITER   200
#define NUM_UNROLL 5
unsigned long time_trials[NUM_TRIAL];

// maximum size of integer array
#define MAX_INT_ARRAY 67108864 // 64M ints, 256M bytes

// deprecated random index
// #include <time.h>
// time_t t;
// srand((unsigned)time(&t));
// ind = (unsigned int)((float)rand() / (float)RAND_MAX * size);

int main() {
    int size = 1, temp;
    unsigned long ind;
    int* data = new int[MAX_INT_ARRAY];
    for (int i = 0; i < MAX_INT_ARRAY; i++) {
        data[i] = i % 10;
    }

    for (int s = 0; s < 30; s++) {
        RESET_CCNT;
        ind = 0;
        for (int i = 0; i < NUM_TRIAL; i++) {
            int real_ind = ind % size;
            GET_CCNT(time_start);
            temp = data[real_ind];
            GET_CCNT(time_end);
            time_trials[i] = time_end - time_start;
            ind += 8;
        }
        std::cout << s << ": " << size << std::endl;
        print_trimmed_mean_std(time_trials, NUM_TRIAL, 1, 1);
        size = size * 2;
    }
    (void) temp;
    delete data;
    return 0;
}
