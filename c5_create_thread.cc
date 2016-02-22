#include "utils.h"
#include <pthread.h>
using namespace std;

// experiment repetitions
#define NUM_TRIAL  10000
#define NUM_ITER   200
#define NUM_UNROLL 5
unsigned long time_trials[NUM_TRIAL];

void * RunThread(void * ) {
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;

    for (int i = 0; i < NUM_TRIAL; ++i) {
        RESET_CCNT;
        GET_CCNT(time_start);
        pthread_create(&tid, NULL, RunThread, NULL);
        pthread_join(tid, NULL);
        GET_CCNT(time_end);
        if (time_end > time_start) {
            time_trials[i] = time_end - time_start;
        } else {
            std::cout << "eliminated " << i << std::endl;
            --i;
        }
    }
    std::cout << "## Thread creation " << std::endl;
    print_all_stats(time_trials, NUM_TRIAL, 1, 1);

    return 0;
}
