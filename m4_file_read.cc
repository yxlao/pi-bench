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
#define BLOCK_SIZE 4096

/*
void try_flush() {
  ifstream file;
  char filename[128] = "flush_1073741824";
  char * buffer = new char[BLOCK_SIZE];
  file.open(filename, ios::in);
  for (long long int k = 0; k < 1073741824; k += BLOCK_SIZE) {
    file.read(buffer, BLOCK_SIZE);
    if (!file) cout << "flush end early" << endl;
  }
  file.close();
}*/

int main() {
     //define variables
     long long int size =4096;
     
     //int counter = 0;   
 
     char filename[128];
     char * buffer = new char[BLOCK_SIZE];     

     struct timeval start, stop;

     ifstream file1, file2;
     file1.rdbuf() -> pubsetbuf(0, 0);//disable read buffer
     file2.rdbuf() -> pubsetbuf(0, 0);
     //sequential access
     for (int i = 0; i < 18; i++) {
       
       sprintf (filename, "/home/pi/temp_%lld", size);
    
       file1.open(filename, ios::in); 

       file1.seekg(0, ios::beg);

       gettimeofday(&start, NULL);

       //counter = 0;	
       for (long long int k = 0; k < size; k += BLOCK_SIZE) {
           //file1.seekg(k, ios::beg);
           file1.read(buffer, BLOCK_SIZE);
           if (!file1) {
              cout << k <<  " seq read end early " << size <<endl;
              break;
           }
           //counter++;
       }
  
       gettimeofday(&stop, NULL);
	    
       cout << "size: " << size << " seq: " << ((stop.tv_sec - start.tv_sec) * 1000000L) + stop.tv_usec - start.tv_usec << endl;
	    
       file1.close(); 
      
       size *= 2;       
      
     }//end of sequential access 


    //reset parameters
    size = 4096;

    //random access
    for (int i = 0; i < 18; i++) {
 
       sprintf (filename, "home/pi/temp_%lld", size);
      
       file2.open(filename, ios::in);

       int block_num = ceil((double)size / (double)BLOCK_SIZE);
       
       long long int * randInd = new long long int[block_num];
  
       for (int i = 0; i < block_num; i++) {
           randInd[i] = rand() % block_num * BLOCK_SIZE;
       }
  
       file2.seekg(0, ios::beg);
       //if (!file2) cout << "file2 fail at the very beginning" << endl;
       gettimeofday(&start, NULL);
       //counter = 0;
       for (long long int k = 0; k < size; k += BLOCK_SIZE) {
           file2.seekg(randInd[k / BLOCK_SIZE], ios::beg);
         //  file2.seekg(k, ios::beg);
         //  cout << "randInd" << randInd[k / BLOCK_SIZE] << endl;
           file2.read(buffer, BLOCK_SIZE);
         //  if (!file2){
           //   cout << "rand read end early" << endl;
            //  break;
         //  }
           //counter ++;
       }

       gettimeofday(&stop, NULL); 
  
       cout << "size: " << size << " ran: " << ((stop.tv_sec - start.tv_sec) * 1000000L) + stop.tv_usec - start.tv_usec << endl;

       file2.close();
        
       size *= 2;
    }//end of random access
     
     return 0;
}
