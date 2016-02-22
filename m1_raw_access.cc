#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "utils.h"

// experiment repetitions
#define NUM_TRIAL  10000
#define NUM_ITER   200
#define NUM_UNROLL 5
unsigned long time_trials[NUM_TRIAL];

int main() {
  int size = 1, ind, temp;
  time_t t;
  srand((unsigned)time(&t));
  //int* data = new int[67108864];
  //unsigned long * my_time_trials = new unsigned long[NUM_TRIAL * 100];

  for (int s = 0; s < 20; s++) {
    int * data = new int[size];
    RESET_CCNT;
    for (int i = 0; i < NUM_TRIAL; i++) {
      ind = (unsigned int)((float)rand() / (float)RAND_MAX * size);
      GET_CCNT(time_start);
      temp = data[ind];
      GET_CCNT(time_end);
      time_trials[i] = time_end - time_start;
    }
    std::cout << s << ": " << size << std::endl;
    print_trimmed_mean_std(time_trials, NUM_TRIAL, 1, 1);
    size = size * 2;
    delete data;
  }

 // delete data;
  //delete[] my_time_trials;
  return 0;
}
