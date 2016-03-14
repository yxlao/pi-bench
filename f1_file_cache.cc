#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <stdlib.h>
#include "utils.h"
// experiment repetitions
#define NUM_TRIAL 1
#define NUM_ITER 1
#define NUM_UNROLL 1
unsigned long time_trials_1[NUM_TRIAL];
unsigned long time_trials_2[NUM_TRIAL];

using namespace std;

int main() {
     //define variables
     long long int size = 512;
     int buffer_size = 4096;
     char filename[128];
     char * buffer = new char[buffer_size];
    
     //experiment
     for (int i = 0; i < 21; i++) {
       sprintf (filename, "/home/pi/temp_%lld", size);
       ifstream file;
       file.open(filename, ios::in); 

       for (int j = 0; j < NUM_TRIAL; j++) {
       file.clear();
       file.seekg(0, ios::beg);
       RESET_CCNT;
       GET_LOW_CCNT(time_start);

       for (int k = 0; k < size; k += buffer_size) {
         file.read(buffer, buffer_size);
       }
       GET_LOW_CCNT(time_end);

       //unsigned long time_1 = (time_end - time_start) * 64;
       //cout << "size: " << size << " first: " << time_1 << endl;
       
       time_trials_1[j] = (time_end - time_start) * 64;

       file.clear();
       file.seekg(0, ios::beg);  

       GET_LOW_CCNT(time_start);
       
       for (int k = 0; k < size; k += buffer_size) {
         file.read(buffer, buffer_size);
       }
       
       GET_LOW_CCNT(time_end);
       //unsigned long time_2 = (time_end - time_start) * 64;
        
       //cout << "size: " << size << " second: " << time_2  << endl;
       time_trials_2[j] = (time_end - time_start) * 64;
       }
       cout << "size:(Mb) " << (double)size / (double) 1024 / (double) 1024 << " first read " << endl;  
       print_all_stats(time_trials_1, NUM_TRIAL, NUM_ITER, NUM_UNROLL);       
       
       cout << " " << endl;

       cout << "size:(Mb) " << (double)size / (double) 1024 / (double) 1024 << " second read " << endl;  
       print_all_stats(time_trials_2, NUM_TRIAL, NUM_ITER, NUM_UNROLL); 

       cout << " " << endl;      
       file.close();       
    
       size *= 2;
    }
    // clean-ups
    return 0;
}
