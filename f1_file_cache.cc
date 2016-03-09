#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <stdlib.h>
#include "utils.h"
// experiment repetitions
#define NUM_TRIAL 100
unsigned long time_trials[NUM_TRIAL];
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

       RESET_CCNT;
       GET_LOW_CCNT(time_start);

       for (int k = 0; k < size; k += buffer_size) {
         file.read(buffer, buffer_size);
       }
       GET_LOW_CCNT(time_end);

       unsigned long time_1 = (time_end - time_start) * 64;
       cout << "size: " << size << " first: " << time_1 << endl;
       
       file.clear();
       file.seekg(0, ios::beg);  

       GET_LOW_CCNT(time_start);
       
       for (int k = 0; k < size; k += buffer_size) {
         file.read(buffer, buffer_size);
       }
       
       GET_LOW_CCNT(time_end);
       unsigned long time_2 = (time_end - time_start) * 64;
        
       cout << "size: " << size << " second: " << time_2  << endl;
       file.close();       
    
       size *= 2;
    }


     // clean-ups
     return 0;
}
