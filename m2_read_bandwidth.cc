#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "utils.h"

// experiment repetitions
#define NUM_TRIAL 100
unsigned long time_trials[NUM_TRIAL];
using namespace std;

#define MAX_INT_ARRAY_SIZE 16777216 / 2 // 32M Bytes
#define CACHE_FLUSH_SIZE 4194304 / 4

void flush_write(int* data, int max_ind) {
    for (int i = 0; i < max_ind; i++) {
        data[i] = i;
    }
    return;
}

void flush_read(int* data, int max_ind) {
    int temp;
    for (int i = 0; i < max_ind; i++) {
        temp = data[i];
    }
    (void) temp;
    return;
}

int main() {
    // init data
    int temp;
    int* data = new int[MAX_INT_ARRAY_SIZE];
    int* cache_data = new int[CACHE_FLUSH_SIZE];
    flush_write(data, MAX_INT_ARRAY_SIZE);
    flush_write(cache_data, CACHE_FLUSH_SIZE);

    // experiments
    for (int i = 0; i < NUM_TRIAL; i++) {
        flush_write(cache_data, CACHE_FLUSH_SIZE);
        flush_read(cache_data, CACHE_FLUSH_SIZE);
        RESET_CCNT;
        GET_CCNT(time_start);
        for (int j = 0; j < MAX_INT_ARRAY_SIZE; j += 4) {
             temp = data[j];
        }
        GET_CCNT(time_end);
        time_trials[i] = time_end - time_start;
    }

    // print results
    print_all_stats(time_trials, NUM_TRIAL, 1, 1);

    // clen-ups
    (void) temp;
    delete data;
    return 0;
}
