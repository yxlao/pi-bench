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
unsigned long time_trials[NUM_TRIAL];
using namespace std;

#define MAX_INT_ARRAY_SIZE 16777216 / 2 // 32M Bytes
#define CACHE_FLUSH_SIZE 4194304 / 4
#define BLOCK_SIZE 4096

char buffer[BLOCK_SIZE] __attribute__((aligned(0x1000)));

int main() {
     //define variables
     long long int size =4096;
     srand((unsigned int)time(NULL));    
     long time_sum = 0;

     char filename[128];

     struct timeval start, stop;

     int file1, file2;
  
     //sequential access
     for (int i = 0; i < 18; i++) {

       sprintf (filename, "/home/pi/temp_%lld", size);
    
       file1 = open(filename, O_RDONLY | O_DIRECT); 
  
       gettimeofday(&start, NULL);
       for (long long int k = 0; k < size; k += BLOCK_SIZE) {
           read(file1, buffer, BLOCK_SIZE);
       }
       gettimeofday(&stop, NULL); 
       double report_size1 = (double) size / (double) 1024 / (double) 1024;
       double report_time1 = (double) (stop.tv_sec - start.tv_sec) + (double) (stop.tv_usec - start.tv_usec) / (double) 1000000;
       cout << "size: " << report_size1 << "(Mb) seq: " << report_time1 <<" (s) " << report_size1 / report_time1  << endl;
	    
       close(file1); 
      
       size *= 2;       
      
     }//end of sequential access 


    //reset parameters
    size = 4096;

    //random access
    for (int i = 0; i < 18; i++) {
 
       sprintf (filename, "/home/pi/temp_%lld", size);
       file2 = open(filename, O_RDONLY | O_DIRECT);

       int block_num = ceil((double)size / (double)BLOCK_SIZE);

       long long int * randInd = new long long int[block_num];

       for (int i = 0; i < block_num; i++) {
           randInd[i] = rand() % block_num * BLOCK_SIZE;
       }
       
       gettimeofday(&start, NULL); 
       for (long long int k = 0; k < size; k += BLOCK_SIZE) {
           lseek(file2, randInd[k / BLOCK_SIZE], SEEK_SET);
           read(file2, buffer, BLOCK_SIZE);
       }
       gettimeofday(&stop, NULL);    
       
       double report_size2 = (double) size / (double) 1024 / (double) 1024;
       double report_time2 = (double) (stop.tv_sec - start.tv_sec) + (double) (stop.tv_usec - start.tv_usec) / (double) 1000000;
       cout << "size: " << report_size2 << " (Mb) ran: " <<report_time2 <<" (s)" << report_size2 / report_time2 <<  endl;

       close(file2);

       size *= 2;
    }//end of random access

     return 0;
}
