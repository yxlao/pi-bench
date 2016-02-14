#include <iostream>
// #include "raspbian-ccr/cycles.c"
#include "utils.h"
// #include <cstdint>
using namespace std;
void fun0() {
    GET_CCNT(time_end);
}

void fun1(int arg) {
    GET_CCNT(time_end);
}

void fun2(int arg1, int arg2) {
    GET_CCNT(time_end);
}

void fun3(int arg1, int arg2, int arg3) {
    GET_CCNT(time_end);
}

void fun4(int arg1, int arg2, int arg3, int arg4) {
    GET_CCNT(time_end);
}

void fun5(int arg1, int arg2, int arg3, int arg4, int arg5) {
    GET_CCNT(time_end);
}

void fun6(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
    GET_CCNT(time_end);
}

void fun7(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6,
          int arg7) {
    GET_CCNT(time_end);
}

int main() {
    RESET_CCNT;

    for (int i = 0; i < NUM_TRIAL; ++i) {
        GET_CCNT(time_start);
        fun0();
        time_total += time_end - time_start;
    }
    cout << "procedure call 0: " << 1. * time_total / NUM_TRIAL << endl;

    RESET_CCNT;
    time_total = 0;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        GET_CCNT(time_start);
        fun1(0);
        time_total += time_end - time_start;
    }
    cout << "procedure call 1: " << 1. * time_total / NUM_TRIAL << endl;

    RESET_CCNT;
    time_total = 0;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        GET_CCNT(time_start);
        fun2(0, 0);
        time_total += time_end - time_start;
    }
    cout << "procedure call 2: " << 1. * time_total / NUM_TRIAL << endl;

    RESET_CCNT;
    time_total = 0;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        GET_CCNT(time_start);
        fun3(0, 0, 0);
        time_total += time_end - time_start;
    }
    cout << "procedure call 3: " << 1. * time_total / NUM_TRIAL << endl;

    RESET_CCNT;
    time_total = 0;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        GET_CCNT(time_start);
        fun4(0, 0, 0, 0);
        time_total += time_end - time_start;
    }
    cout << "procedure call 4: " << 1. * time_total / NUM_TRIAL << endl;

    RESET_CCNT;
    time_total = 0;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        GET_CCNT(time_start);
        fun5(0, 0, 0, 0, 0);
        time_total += time_end - time_start;
    }
    cout << "procedure call 5: " << 1. * time_total / NUM_TRIAL << endl;

    RESET_CCNT;
    time_total = 0;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        GET_CCNT(time_start);
        fun6(0, 0, 0, 0, 0, 0);
        time_total += time_end - time_start;
    }
    cout << "procedure call 6: " << 1. * time_total / NUM_TRIAL << endl;

    RESET_CCNT;
    time_total = 0;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        GET_CCNT(time_start);
        fun7(0, 0, 0, 0, 0, 0, 0);
        time_total += time_end - time_start;
    }
    cout << "procedure call 7: " << 1. * time_total / NUM_TRIAL << endl;

    return 0;
}
