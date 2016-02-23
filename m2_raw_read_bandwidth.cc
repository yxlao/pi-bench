#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "utils.h"

// experiment repetitions
#define NUM_TRIAL  10000
#define NUM_ITER   200
#define NUM_UNROLL 5
unsigned long time_trials[NUM_TRIAL];
using namespace std;

int main() {
    int i, j;
    char temp;
    char * data = new char[262144];//256KByte = 256 * 1024 Characters = 262144
    for (int i = 0; i < 262144; i++) {
        data[i] = 'a' + i % ('z' - 'a');
    }
    //read test
    for (i = 0; i < NUM_TRIAL; i++) {
        RESET_CCNT;
        GET_CCNT(time_start);
        for (j = 0; j < 261664; j += 512) {
           temp = data[j];
           temp = data[j + 32];
           temp = data[j + 64];
           temp = data[j + 96];
           temp = data[j + 128];
           temp = data[j + 160];
           temp = data[j + 192];
           temp = data[j + 224];
           temp = data[j + 256];
           temp = data[j + 288];
           temp = data[j + 320];
           temp = data[j + 352];
           temp = data[j + 384];
           temp = data[j + 416];
           temp = data[j + 448];
           temp = data[j + 480];
        }
        GET_CCNT(time_end);
        time_trials[i] = time_end - time_start;
    }
    print_trimmed_mean_std(time_trials, NUM_TRIAL, 1, 1);
    (void) temp;  // make g++ "unused variable" go away
    delete data;
    return 0;
}
