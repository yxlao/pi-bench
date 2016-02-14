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
  for (i = 0; i < 26; i++) {
    int * data = new int[size];
    //initial data
    for (j = 0; j < NUM_TRIAL; j++) {
      unsigned long time_total = 0;
      RESET_CCNT;
      for (k = 0; k < NUM_ITER * NUM_UNROLL; k++) {
        ind = rand() % size;
        GET_CCNT(start);
        //RESET_CCNT;
        read = data[ind];
        GET_CCNT(end);
        time_total += end - start;
      }

      if (j == 10) {
        cout << "memory read time of size " << size << " is: "
             << 1. * time_total << " average:  " << 1. * time_total / NUM_ITER / NUM_UNROLL
             << endl;
      }

      //unsigned long counter = 0;
      // for (int m = 0; m < size; m += 32) {
      //   counter ++;
      //  RESET_CCNT;
      //      read = data[m];
      //    GET_CCNT(end);
      //     data[m] = read;
      //  time_total += end;
      // }
      // if (j == 10) {
      //   cout << "memory read time of size " << size << " is: " << 1. * time_total << " average: " <<
      //    1. * time_total / counter << endl;
      // }
    }
    size = size * 2;
  }
  return 0;
}
