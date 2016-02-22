#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "utils.h"
using namespace std;

int main() {
    int i, j, sum = 0;
    int * data = new int[1048576];//4MByte = 1M integers = 2 ^ 20 integers = 1048576 integers
    //read test
    for (i = 0; i < NUM_TRIAL; i++) {
        RESET_CCNT;
        GET_CCNT(time_start);
        for (j = 0; j < 1048504; j += 80) {
            sum = data[j];
            sum = data[j + 8];//next cache line
            sum = data[j + 16];
            sum = data[j + 24];
            sum = data[j + 32];
            sum = data[j + 40];
            sum = data[j + 48];
            sum = data[j + 56];
            sum = data[j + 64];
            sum = data[j + 72];
        }
        GET_CCNT(time_end);
        time_trials[i] = time_end - time_start;
    }
    //cout << counter<<endl;
    print_trimmed_mean_std(time_trials, NUM_TRIAL, 1, 1);
    delete data;
    return 0;
}