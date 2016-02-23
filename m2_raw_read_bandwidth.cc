#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "utils.h"

// experiment repetitions
#define NUM_TRIAL  50
unsigned long time_trials[NUM_TRIAL];
using namespace std;

// #define MAX_CHAR_ARRAY_SIZE 268435456 // 256M bytes
#define MAX_CHAR_ARRAY_SIZE 16777216 // 33554432 // 32M bytes
#define CACHE_FLUSH_SIZE 4194304 // 4M bytes, flush L1, L2 cache

void flush_write(char* data, int max_ind) {
     for (int i = 0; i < max_ind; i++) {
          data[i] = 'a' + i % ('z' - 'a');
     }
     return;
}

void flush_read(char* data, int max_ind) {
     char temp;
     for (int i = 0; i < max_ind; i++) {
          temp = data[i];
     }
     (void) temp;
     return;
}

int main() {
     // init data
     char temp;
     char* data = new char[MAX_CHAR_ARRAY_SIZE];
     char* cache_data = new char[CACHE_FLUSH_SIZE];
     flush_write(data, MAX_CHAR_ARRAY_SIZE);
     flush_write(cache_data, CACHE_FLUSH_SIZE);

     // experiments
     for (int i = 0; i < NUM_TRIAL; i++) {
          flush_write(cache_data, CACHE_FLUSH_SIZE);
          flush_read(cache_data, CACHE_FLUSH_SIZE);
          RESET_CCNT;
          GET_CCNT(time_start);
          for (int j = 0; j < MAX_CHAR_ARRAY_SIZE; j += 512) {
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

     // print results
     print_all_stats(time_trials, NUM_TRIAL, 1, 1);

     // clen-ups
     (void) temp;
     delete data;
     return 0;
}
