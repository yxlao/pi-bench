#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <stdlib.h>
#include "utils.h"
// experiment repetitions
#define NUM_TRIAL 100
unsigned long time_trials[NUM_TRIAL];
using namespace std;

#define MAX_INT_ARRAY_SIZE 16777216 / 2 // 32M Bytes
#define CACHE_FLUSH_SIZE 4194304 / 4

int main() {
     //define variables
     struct timeval start, stop;
     long long int size = 512;
     int buffer_size = 4096;
     char filename[128];
     char * buffer = new char[buffer_size];
    
     //experiment
     for (int i = 0; i < 21; i++) {
       sprintf (filename, "/home/pi/temp_%lld", size);
       ifstream file;
       file.open(filename, ios::in); 

       //RESET_CCNT;
       //GET_CCNT(time_start);

       gettimeofday(&start, NULL);    
       
       for (int k = 0; k < size; k += buffer_size) {
         file.read(buffer, buffer_size);
       }
       //GET_CCNT(time_end);

       gettimeofday(&stop, NULL);   

       //unsigned long time_1 = time_end - time_start;
       cout << "size: " << size << " first: " << ((stop.tv_sec - start.tv_sec) * 1000000L) + stop.tv_usec - start.tv_usec << endl;
       
       file.clear();
       file.seekg(0, ios::beg);  

       //GET_CCNT(time_start);
       
       gettimeofday(&start, NULL);
       
       for (int k = 0; k < size; k += buffer_size) {
         file.read(buffer, buffer_size);
       }
       
       //GET_CCNT(time_end);
       gettimeofday(&stop, NULL);
       //unsigned long time_2 = time_end - time_start;
       //cout << "time2 " << stop.tv_usec - start.tv_usec << endl;
        
       cout << "size: " << size << " second: " << ((stop.tv_sec - start.tv_sec) * 1000000L) + stop.tv_usec - start.tv_usec << endl;
       file.close();       
    
       //print_results
       //cout << "time 1: " << time_1 << " time 2: " << time_2 << " size: " << size << endl;
       size *= 2;
    }


     // clean-ups
     return 0;
}
