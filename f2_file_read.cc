#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"
// experiment repetitions
#define NUM_TRIAL 100
unsigned long time_trials[NUM_TRIAL];
using namespace std;

#define MAX_INT_ARRAY_SIZE 16777216 / 2 // 32M Bytes
#define CACHE_FLUSH_SIZE 4194304 / 4
#define BLOCK_SIZE 4096

int main() {
     //define variables
     long long int size =4096;
     srand((unsigned int)time(NULL));    

     char filename[128];
     char * buffer = new char[BLOCK_SIZE];     

     struct timeval start, stop;

     int file1, file2;

     //sequential access
     for (int i = 0; i < 18; i++) {
       
       sprintf (filename, "/home/pi/temp_%lld", size);
    
       file1 = open(filename, O_RDONLY | O_DIRECT); 
       if (file1 == -1) {
           cout << "seq open file failed, size: " << size <<  endl;
       }

       gettimeofday(&start, NULL);

       //counter = 0;	
       for (long long int k = 0; k < size; k += BLOCK_SIZE) {
           ssize_t byte = read(file1, buffer, BLOCK_SIZE);
           if (byte <= 0) {
              cout << k <<  " seq read end early " << size <<endl;
              break;
           }
       }
  
       gettimeofday(&stop, NULL);
	    
       cout << "size: " << size << " seq: " << ((stop.tv_sec - start.tv_sec) * 1000000L) + stop.tv_usec - start.tv_usec << endl;
	    
       close(file1); 
      
       size *= 2;       
      
     }//end of sequential access 


    //reset parameters
    size = 4096;

    //random access
    for (int i = 0; i < 18; i++) {
 
       sprintf (filename, "home/pi/temp_%lld", size);
      
       file2 = open(filename, O_RDONLY | O_DIRECT);
       if (file2 == -1) {
           cout << "rand open file failed, size: " << size << endl;
       }
       int block_num = ceil((double)size / (double)BLOCK_SIZE);
       
       long long int * randInd = new long long int[block_num];
  
       for (int i = 0; i < block_num; i++) {
           randInd[i] = rand() % block_num * BLOCK_SIZE;
       }
  
       gettimeofday(&start, NULL);
       
       //counter = 0;
       for (long long int k = 0; k < size; k += BLOCK_SIZE) {
           lseek(file2, randInd[k / BLOCK_SIZE], SEEK_SET);
           ssize_t byte2 = read(file2, buffer, BLOCK_SIZE);
           if (byte2 <= 0) {
             cout << k << "rand read end early " << size << endl;
             break;
           }
       }

       gettimeofday(&stop, NULL); 
  
       cout << "size: " << size << " ran: " << ((stop.tv_sec - start.tv_sec) * 1000000L) + stop.tv_usec - start.tv_usec << endl;

       close(file2);
        
       size *= 2;
    }//end of random access
     
     return 0;
}
