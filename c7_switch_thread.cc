#include "utils.h"
#include <pthread.h>
#include <unistd.h>

// experiment repetitions
#define NUM_TRIAL  10000
#define NUM_ITER   200
#define NUM_UNROLL 5
unsigned long time_trials[NUM_TRIAL];

void* thread_switch(void* idt) {
    for (int i; i < NUM_ITER / 2; i++) {
        std::cout << "partner " << i << std::endl;
        std::cout.flush();
    }
    return 0;
}

int main() {
    pthread_t partner;
    pthread_create(&partner, NULL, thread_switch, NULL);
    for (int i; i < NUM_ITER / 2; i++) {
        std::cout << "main " << i << std::endl;
        std::cout.flush();
    }

    pthread_join(partner, NULL);

    // RESET_CCNT;
    // pthread_t tid;
    // // unsigned long time_total1 = 0;
    // for (int i = 0; i < NUM_TRIAL; ++i) {
    //     // pipe(fd);
    //     pthread_create(&tid, NULL, RunThread, NULL);
    //     // read(fd[0], &time_start, 1);
    //     GET_CCNT(time_start);
    //     pthread_join(tid, NULL);
    //     // GET_CCNT(time_end);
    //     time_trials[i] = time_end - time_start;
    // }

    // std::cout << "## Thread creation " << std::endl;
    // print_all_stats(time_trials, NUM_TRIAL, 1, 1);
    return 0;
}


// long long getThreadContextSwitchOverhead(unsigned long long threadRunOverhead) {
//     pthread_t thread1;
//     unsigned long long time1, time2;

//     long long localSwitches = numThreadSwitches / 2;
//     long long switchCount = 0;

//     time1 = rdtsc();
//     pthread_create(&thread1, NULL, thread_switch, NULL);

//     for (; switchCount < localSwitches; switchCount++) {
//         sched_yield();
//     }

//     pthread_join(thread1, NULL);
//     time2 = rdtsc();
//     return (time2 - time1 - threadRunOverhead) / numThreadSwitches;
// }