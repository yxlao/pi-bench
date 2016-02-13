#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "utils.h"
using namespace std;

int main() {
    int i, j, k, size = 1, read, ind;
    time_t t;
    unsigned long start, end;
    srand((unsigned)time(&t));
    for (i = 0; i < 20; i++) {
        int * data = new int[size];
        //initial data
        for (j = 0; j < NUM_TRIAL; j++) {
            unsigned long time_total = 0;
            RESET_CCNT;
            for (k = 0; k < NUM_ITER; k++) {
                ind = rand() % size;
                GET_CCNT(start);
                read = data[ind];
                GET_CCNT(end);
                time_total += end - start;
            }
            if (j == 10) {
                cout << "memory read time of size " << size << " is: "
                     << 1. * time_total / NUM_ITER << endl;
            }
        }
        size = size * 2;
    }
    return 0;
}
