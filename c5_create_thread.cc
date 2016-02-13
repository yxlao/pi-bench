#include <iostream>
// #include "raspbian-ccr/cycles.c"
#include "cycles.h"
// #include <cstdint>
#include <pthread.h>
using namespace std;

void * RunThread(void * ) {
  GET_CCNT(end_time);
  pthread_exit(NULL);
}

int main() {
    RESET;
    pthread_t tid;
    unsigned long total = 0;
    for (int i = 0; i < STD_ITER; ++i) {
        GET_CCNT(start_time);
        pthread_create(&tid, NULL, RunThread, NULL);
        pthread_join(tid, NULL);
        total += end_time - start_time;
        // cout << start << "," << end << "," << end - start << endl;
    }
    cout << 1. * total / STD_ITER << endl;
    return 0;
}
