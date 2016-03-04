#include <stdio.h>
#include <pthread.h>
#include <pthread.h>
#include <unistd.h>
#include "utils.h"

#define NUM_TRIAL  1000
#define NUM_ITER   200
#define NUM_UNROLL 5
unsigned long time_trials[NUM_TRIAL];

pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;
int buffer = 0;

void* producer(void *ptr) {
    for (int i = 0; i < NUM_TRIAL; i++) {
        // start time
        RESET_CCNT;
        GET_CCNT(time_start);

        for (int j = 0; j < NUM_ITER / 2; j++) {
            pthread_mutex_lock(&the_mutex); // protect buffer
            while (buffer != 0) // if there is something in the buffer then wait
                pthread_cond_wait(&condp, &the_mutex);
            buffer = 1;
            // std::cout << "producer " << j << std::endl;
            // std::cout.flush();
            pthread_cond_signal(&condc); // wake up consumer
            pthread_mutex_unlock(&the_mutex); // release the buffer
        }

        // end time
        GET_CCNT(time_end);
        if (time_end > time_start) {
            time_trials[i] = time_end - time_start;
        } else {
            i--;
        }
    }
    pthread_exit(0);
}

void* consumer(void *ptr) {
    for (int i = 0; i < NUM_TRIAL; i++) {
        for (int j = 0; j < NUM_ITER / 2; j++) {
            pthread_mutex_lock(&the_mutex); // protect buffer
            while (buffer == 0) // if there is nothing in the buffer then wait
                pthread_cond_wait(&condc, &the_mutex);
            buffer = 0;
            // std::cout << "consumer " << j << std::endl;
            // std::cout.flush();
            pthread_cond_signal(&condp); // wake up consumer
            pthread_mutex_unlock(&the_mutex); // release the buffer
        }
    }
    pthread_exit(0);
}

int main() {
    pthread_t pro, con;

    // initialize the mutex and condition variables
    pthread_mutex_init(&the_mutex, NULL);
    pthread_cond_init(&condc, NULL); // initialize consumer condition variable
    pthread_cond_init(&condp, NULL); // initialize producer condition variable

    // create the threads
    pthread_create(&con, NULL, consumer, NULL);
    pthread_create(&pro, NULL, producer, NULL);

    // wait for the threads to finish
    // otherwise main might run to the end
    // and kill the entire process when it exits.
    pthread_join(con, NULL);
    pthread_join(pro, NULL);

    // cleanup -- would happen automatically at end of program
    pthread_mutex_destroy(&the_mutex); // free up the_mutex
    pthread_cond_destroy(&condc); // free up consumer condition variable
    pthread_cond_destroy(&condp); // free up producer condition variable

    print_all_stats(time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);

    return 0;
}