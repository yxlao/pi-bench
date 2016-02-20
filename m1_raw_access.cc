#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "utils.h"
using namespace std;

int main() {
  int size = 1, temp, ind;
  time_t t;
  srand((unsigned)time(&t));
  int* data = new int[67108864];

  for (int s = 0; s < 27; s++) {
    RESET_CCNT;
    for (int i = 0; i < NUM_TRIAL; i++) {
      ind = (unsigned int)((float)rand() / (float)RAND_MAX * size);
      GET_CCNT(time_start);
      temp = data[ind];
      GET_CCNT(time_end);
      time_trials[i] = time_end - time_start;
    }
    cout << size << endl;
    print_trimmed_mean_std(time_trials, NUM_TRIAL, 1, 1);
    size = size * 2;
  }

  delete data;
  (void) temp;
  return 0;
}
