#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "utils.h"
// experiment repetitions
#define NUM_TRIAL 100
#define NUM_UNROLL 1
#define NUM_ITER 1
unsigned long time_trials[6][NUM_TRIAL];
using namespace std;

#define MAX_INT_ARRAY_SIZE 16777216 / 2 // 32M Bytes
#define CACHE_FLUSH_SIZE 4194304 / 4
#define BLOCK_SIZE 4096

char buffer[BLOCK_SIZE] __attribute__((aligned(0x1000)));

int main(int argc, char *argv[]) {
    //define variables
    long long int size;
    srand((unsigned int)time(NULL));

    char filename[128];
    int file1;
    
    for (int j = 0; j < NUM_TRIAL; j++) {
      size = 8 * 1024 * 1024;
      cout << j << endl;
      //sequential access
      for (int i = 0; i < 6; i++) {
        cout << "size is " << size << endl;
        sprintf (filename, "/home/pi/temp_%lld", size);

        file1 = open(filename, O_RDONLY | O_DIRECT);

        RESET_CCNT;
        GET_LOW_CCNT(time_start);
        for (long long int k = 0; k < size; k += BLOCK_SIZE) {
          read(file1, buffer, BLOCK_SIZE);
        }
        GET_LOW_CCNT(time_end);
        time_trials[i][j] = (time_end - time_start); 
        close(file1);

        size *= 2;

      }//end of sequential access
    }
    
    //output result
    size = 8 * 1024 * 1024;
    for (int k = 0; k < 6; k++) {
      cout << "seq access, size is: " << size << endl;
      print_all_stats(time_trials[k], NUM_TRIAL, NUM_ITER, NUM_UNROLL);
      cout << " " << endl;
      size *= 2;
    }    
    return 0;
}
