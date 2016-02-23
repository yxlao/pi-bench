#include "utils.h"

// experiment repetitions
#define NUM_TRIAL  10000
#define NUM_ITER   200
#define NUM_UNROLL 5
unsigned long time_trials[NUM_TRIAL];

void fun0() {}
void fun1(int arg1) {}
void fun2(int arg1, int arg2) {}
void fun3(int arg1, int arg2, int arg3) {}
void fun4(int arg1, int arg2, int arg3, int arg4) {}
void fun5(int arg1, int arg2, int arg3, int arg4, int arg5) {}
void fun6(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {}
void fun7(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7) {}

int main() {

    RESET_CCNT;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        GET_CCNT(time_start);
        for (int j = 0; j < NUM_ITER; ++j) {
            fun0();
            fun0();
            fun0();
            fun0();
            fun0();
        }
        GET_CCNT(time_end);
        time_trials[i] = time_end - time_start;
    }
    std::cout << "##### Procedure call fun0" << std::endl;
    // print_all_stats(time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);
    print_trimmed_mean_std(time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);

    RESET_CCNT;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        GET_CCNT(time_start);
        for (int j = 0; j < NUM_ITER; ++j) {
            fun1(0);
            fun1(0);
            fun1(0);
            fun1(0);
            fun1(0);
        }
        GET_CCNT(time_end);
        time_trials[i] = time_end - time_start;
    }
    std::cout << "##### Procedure call fun1" << std::endl;
    // print_all_stats(time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);
    print_trimmed_mean_std(time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);


    RESET_CCNT;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        GET_CCNT(time_start);
        for (int j = 0; j < NUM_ITER; ++j) {
            fun2(0, 0);
            fun2(0, 0);
            fun2(0, 0);
            fun2(0, 0);
            fun2(0, 0);
        }
        GET_CCNT(time_end);
        time_trials[i] = time_end - time_start;
    }
    std::cout << "##### Procedure call fun2" << std::endl;
    // print_all_stats(time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);
    print_trimmed_mean_std(time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);

    RESET_CCNT;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        GET_CCNT(time_start);
        for (int j = 0; j < NUM_ITER; ++j) {
            fun3(0, 0, 0);
            fun3(0, 0, 0);
            fun3(0, 0, 0);
            fun3(0, 0, 0);
            fun3(0, 0, 0);
        }
        GET_CCNT(time_end);
        time_trials[i] = time_end - time_start;
    }
    std::cout << "##### Procedure call fun3" << std::endl;
    // print_all_stats(time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);
    print_trimmed_mean_std(time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);

    RESET_CCNT;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        GET_CCNT(time_start);
        for (int j = 0; j < NUM_ITER; ++j) {
            fun4(0, 0, 0, 0);
            fun4(0, 0, 0, 0);
            fun4(0, 0, 0, 0);
            fun4(0, 0, 0, 0);
            fun4(0, 0, 0, 0);
        }
        GET_CCNT(time_end);
        time_trials[i] = time_end - time_start;
    }
    std::cout << "##### Procedure call fun4" << std::endl;
    // print_all_stats(time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);
    print_trimmed_mean_std(time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);

    RESET_CCNT;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        GET_CCNT(time_start);
        for (int j = 0; j < NUM_ITER; ++j) {
            fun5(0, 0, 0, 0, 0);
            fun5(0, 0, 0, 0, 0);
            fun5(0, 0, 0, 0, 0);
            fun5(0, 0, 0, 0, 0);
            fun5(0, 0, 0, 0, 0);
        }
        GET_CCNT(time_end);
        time_trials[i] = time_end - time_start;
    }
    std::cout << "##### Procedure call fun5" << std::endl;
    // print_all_stats(time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);
    print_trimmed_mean_std(time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);

    RESET_CCNT;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        GET_CCNT(time_start);
        for (int j = 0; j < NUM_ITER; ++j) {
            fun6(0, 0, 0, 0, 0, 0);
            fun6(0, 0, 0, 0, 0, 0);
            fun6(0, 0, 0, 0, 0, 0);
            fun6(0, 0, 0, 0, 0, 0);
            fun6(0, 0, 0, 0, 0, 0);
        }
        GET_CCNT(time_end);
        time_trials[i] = time_end - time_start;
    }
    std::cout << "##### Procedure call fun6" << std::endl;
    // print_all_stats(time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);
    print_trimmed_mean_std(time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);

    RESET_CCNT;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        GET_CCNT(time_start);
        for (int j = 0; j < NUM_ITER; ++j) {
            fun7(0, 0, 0, 0, 0, 0, 0);
            fun7(0, 0, 0, 0, 0, 0, 0);
            fun7(0, 0, 0, 0, 0, 0, 0);
            fun7(0, 0, 0, 0, 0, 0, 0);
            fun7(0, 0, 0, 0, 0, 0, 0);
        }
        GET_CCNT(time_end);
        time_trials[i] = time_end - time_start;
    }
    std::cout << "##### Procedure call fun7" << std::endl;
    // print_all_stats(time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);
    print_trimmed_mean_std(time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);

    return 0;
}
