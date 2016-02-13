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
    GET_CCNT(time_end);
    pthread_exit(NULL);
}

int main() {
    RESET_CCNT;
    pthread_t tid;
    // unsigned long time_total1 = 0;
    for (int i = 0; i < NUM_ITER; ++i) {
        // pipe(fd);
        pthread_create(&tid, NULL, RunThread, NULL);
        // read(fd[0], &time_start, 1);
        GET_CCNT(time_start);
        pthread_join(tid, NULL);
        // GET_CCNT(time_end);
        time_total += time_end - time_start;
    }
    cout << 1. * time_total / NUM_ITER << " " << 1. * time_total / NUM_ITER << endl;
    return 0;
}
