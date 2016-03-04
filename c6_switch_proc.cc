#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>
#include "utils.h"

// experiment repetitions
#define NUM_TRIAL  1000
#define NUM_ITER   200
#define NUM_UNROLL 5
unsigned long time_trials[NUM_TRIAL];

int main() {
    // pipes
    int child_to_parent[2];
    int parent_to_child[2];
    pipe(child_to_parent);
    pipe(parent_to_child);

    // msic vars
    int unsigned_long_size = sizeof(unsigned long);
    int msg_temp;
    int msg_parent = 100;
    int msg_child = 200;
    assert(NUM_ITER % 2 == 0);
    int half_num_iter = NUM_ITER / 2;

    // pid_t
    pid_t cpid;

    // fork
    cpid = fork();

    // parent
    if (cpid != 0) {
        // parent clean up
        close(child_to_parent[1]);
        close(parent_to_child[0]);

        for (int i = 0; i < NUM_TRIAL; ++i) {
            // start time
            RESET_CCNT;
            GET_CCNT(time_start);

            // operation
            for (int j = 0; j < half_num_iter; ++j) {
                read(child_to_parent[0], &msg_temp, unsigned_long_size);
                write(parent_to_child[1], &msg_parent, unsigned_long_size);
                read(child_to_parent[0], &msg_temp, unsigned_long_size);
                write(parent_to_child[1], &msg_parent, unsigned_long_size);
                read(child_to_parent[0], &msg_temp, unsigned_long_size);
                write(parent_to_child[1], &msg_parent, unsigned_long_size);
                read(child_to_parent[0], &msg_temp, unsigned_long_size);
                write(parent_to_child[1], &msg_parent, unsigned_long_size);
                read(child_to_parent[0], &msg_temp, unsigned_long_size);
                write(parent_to_child[1], &msg_parent, unsigned_long_size);
            }

            // end time
            GET_CCNT(time_end);
            if (time_end > time_start) {
                time_trials[i] = time_end - time_start;
            } else {
                i--;
            }
        }

        wait(NULL); // wait all child process to finish
    }

    // chilid
    else {
        // children clean up
        close(child_to_parent[0]);
        close(parent_to_child[1]);

        for (int i = 0; i < NUM_TRIAL; ++i) {
            for (int j = 0; j < half_num_iter; ++j) {
                write(child_to_parent[1], &msg_child, unsigned_long_size);
                read(parent_to_child[0], &msg_temp, unsigned_long_size);
                write(child_to_parent[1], &msg_child, unsigned_long_size);
                read(parent_to_child[0], &msg_temp, unsigned_long_size);
                write(child_to_parent[1], &msg_child, unsigned_long_size);
                read(parent_to_child[0], &msg_temp, unsigned_long_size);
                write(child_to_parent[1], &msg_child, unsigned_long_size);
                read(parent_to_child[0], &msg_temp, unsigned_long_size);
                write(child_to_parent[1], &msg_child, unsigned_long_size);
                read(parent_to_child[0], &msg_temp, unsigned_long_size);
            }
        }

        exit(1);
    }

    print_all_stats(time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);

    return 0;
}
