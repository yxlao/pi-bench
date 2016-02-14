#include "utils.h"
#include <pthread.h>
using namespace std;

void * RunThread(void * ) {
    GET_CCNT(time_end);
    pthread_exit(NULL);
}

int main() {
    RESET_CCNT;
    pthread_t tid;

    for (int i = 0; i < NUM_ITER; ++i) {
        GET_CCNT(time_start);
        pthread_create(&tid, NULL, RunThread, NULL);
        pthread_join(tid, NULL);
        time_total += time_end - time_start;
        // cout << start << "," << end << "," << end - start << endl;
    }
    cout << 1. * time_total / NUM_ITER << endl;
    return 0;
}
