#include <iostream>
// #include "raspbian-ccr/cycles.c"
#include "utils.h"
// #include <cstdint>
#include <pthread.h>
#include <unistd.h>
using namespace std;
int fd[2];
unsigned long start;
void * RunThread(void * ) {
  GET_CCNT(end_time);
 // write(fd[1], (void*)&start, sizeof(unsigned long));
  pthread_exit(NULL);
}

int main() {
    RESET_CCNT;
    pthread_t tid;
    unsigned long total = 0;
    // unsigned long total1 = 0;
    for (int i = 0; i < STD_ITER; ++i) {
       // pipe(fd);
        pthread_create(&tid, NULL, RunThread, NULL);
       // read(fd[0], &start_time, 1);
        GET_CCNT(start_time);
        pthread_join(tid, NULL);
       // GET_CCNT(end_time);
        total += end_time - start_time;
       // total1 += end_time - start;
        // cout << start << "," << end << "," << end - start << endl;
    }
    cout << 1. * total / STD_ITER <<" " << 1. * total / STD_ITER << endl;
    return 0;
}
