#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "utils.h"
// experiment repetitions
#define NUM_TRIAL 100
#define NUM_ITER 1
#define NUM_UNROLL 1
unsigned long time_trials_first[7][NUM_TRIAL];
unsigned long time_trials_second[7][NUM_TRIAL];

using namespace std;

int main() {
     //define variables
     long long int size[7] = {64, 128, 150, 175, 200, 300, 383};
     for (int j = 0; j < 7; j++) {
       size[j] = size[j] * 1024 * 1024;
     }
     int buffer_size = 4096;
     char filename[128];
     char * buffer = new char[buffer_size];
     
     //experiment
     for (int m = 0; m < NUM_TRIAL; m++) {
     //do num_trial in outer loop to minimize the cache effect of repeat experiment
       for (int i = 0; i < 7; i++) {
         long long int cur_size = size[i]; 
         sprintf (filename, "/home/pi/temp_%lld", cur_size);
         int file;
         file = open(filename, O_RDONLY);
         lseek(file, 0, SEEK_END);
         RESET_CCNT;
         
         //read first time
         GET_LOW_CCNT(time_start);
         for (int k = 0; k < cur_size; k += buffer_size) {
           if (k == 0) {
             lseek(file, -1 * buffer_size, SEEK_CUR);
           } else {
             lseek(file, -2 * buffer_size, SEEK_CUR);
           }
           read(file, buffer, buffer_size);
         }
         GET_LOW_CCNT(time_end);

         time_trials_first[i][m] = (time_end - time_start);

         lseek(file, 0, SEEK_END);
         RESET_CCNT;
         
         //read second time
         GET_LOW_CCNT(time_start);
       
         for (int k = 0; k < cur_size; k += buffer_size) {
           if (k == 0) {
             lseek(file, -1 * buffer_size, SEEK_CUR);
           } else {
             lseek(file, -2 * buffer_size, SEEK_CUR);
           }
           read(file, buffer, buffer_size);
         }  
         GET_LOW_CCNT(time_end);
         time_trials_second[i][m] = (time_end - time_start);    
         close(file);       
      }
    }

    //print result
    for (int n = 0; n < 7; n++) {
      cout << "size is: " << size[n] << " first read time " << endl;
 
      print_all_stats(time_trials_first[n], NUM_TRIAL, NUM_ITER, NUM_UNROLL);
      cout << " " << endl;

      cout << "size is: " << size[n] << " second read time " << endl;
      print_all_stats(time_trials_second[n], NUM_TRIAL, NUM_ITER, NUM_UNROLL);
      cout << " " << endl; 

    }


    // clean-ups
    return 0;
}
