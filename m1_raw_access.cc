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
  int size = 1, temp;
  unsigned long ind;
  time_t t;
  srand((unsigned)time(&t));
  int* data = new int[67108864];
  for (int i = 0; i < 67108864; i++) {
     data[i] = i % 10;
  }
  //unsigned long * my_time_trials = new unsigned long[NUM_TRIAL * 100];

  for (int s = 0; s < 30; s++) {
    RESET_CCNT;
    ind = 0;
    for (int i = 0; i < NUM_TRIAL; i++) {
      //ind = (unsigned int)((float)rand() / (float)RAND_MAX * size);
      int real_ind = ind % size;
      GET_CCNT(time_start);
      temp = data[real_ind];
      GET_CCNT(time_end);
    //  data[ind] = temp;
      time_trials[i] = time_end - time_start;
      ind += 8;
    }
    std::cout << s << ": " << size << std::endl;
    print_trimmed_mean_std(time_trials, NUM_TRIAL, 1, 1);
    size = size * 2;
  }
  (void) temp;
  delete data;
  // delete[] my_time_trials;
  return 0;
}
