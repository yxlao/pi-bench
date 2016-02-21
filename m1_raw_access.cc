#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "utils.h"
using namespace std;

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
    cout << s << ": " << size << endl;
    print_trimmed_mean_std(time_trials, NUM_TRIAL, 1, 1);
    size = size * 2;
    delete data;
  } 

 // delete data;
  //delete[] my_time_trials;
  return 0;
}
