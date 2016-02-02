#include <iostream>
// #include "raspbian-ccr/cycles.c"
#include "cycles.h"
// #include <cstdint>
using namespace std;
void fun0() {
    GET_CCNT(end_time);
}

void fun1(int arg) {
    GET_CCNT(end_time);
}

void fun2(int arg1, int arg2) {
    GET_CCNT(end_time);
}

void fun3(int arg1, int arg2, int arg3) {
    GET_CCNT(end_time);
}

void fun4(int arg1, int arg2, int arg3, int arg4) {
    GET_CCNT(end_time);
}

void fun5(int arg1, int arg2, int arg3, int arg4, int arg5) {
    GET_CCNT(end_time);
}

void fun6(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6) {
    GET_CCNT(end_time);
}

void fun7(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7) {
    GET_CCNT(end_time);
}

int main() {
    // ccnt_clr();
    RESET;
    unsigned total = 0;
    for (int i = 0; i < STD_ITER; ++i) {
        GET_CCNT(start_time);
        fun0();
        total += end_time - start_time;
        //cout << start - start << "," << end << "," << end - start << endl;
    }
    cout << "procedure call 0: " << 1. * total / STD_ITER << endl;
    
    RESET;
    total = 0;
    for (int i = 0; i < STD_ITER; ++i) {
    	GET_CCNT(start_time);
        fun1(0);
        total += end_time - start_time;
    }
    cout << "procedure call 1: " << 1. * total / STD_ITER << endl;
    
    RESET;
    total = 0;
    for (int i = 0; i < STD_ITER; ++i) {
    	GET_CCNT(start_time);
        fun2(0, 0);
        total += end_time - start_time;
    }
    cout << "procedure call 2: " << 1. * total / STD_ITER << endl;
    
    RESET;
    total = 0;
    for (int i = 0; i < STD_ITER; ++i) {
    	GET_CCNT(start_time);
        fun3(0, 0, 0);
        total += end_time - start_time;
    }
    cout << "procedure call 3: " << 1. * total / STD_ITER << endl;
    
    RESET;
    total = 0;
    for (int i = 0; i < STD_ITER; ++i) {
    	GET_CCNT(start_time);
        fun4(0, 0, 0, 0);
        total += end_time - start_time;
    }
    cout << "procedure call 4: " << 1. * total / STD_ITER << endl;
    
    RESET;
    total = 0;
    for (int i = 0; i < STD_ITER; ++i) {
    	GET_CCNT(start_time);
        fun5(0, 0, 0, 0, 0);
        total += end_time - start_time;
    }
    cout << "procedure call 5: " << 1. * total / STD_ITER << endl;
    
    RESET;
    total = 0;
    for (int i = 0; i < STD_ITER; ++i) {
    	GET_CCNT(start_time);
        fun6(0, 0, 0, 0, 0, 0);
        total += end_time - start_time;
    }
    cout << "procedure call 6: " << 1. * total / STD_ITER << endl;
    
    RESET;
    total = 0;
    for (int i = 0; i < STD_ITER; ++i) {
    	GET_CCNT(start_time);
        fun7(0, 0, 0, 0, 0, 0, 0);
        total += end_time - start_time;
    }
    cout << "procedure call 7: " << 1. * total / STD_ITER << endl;
    
    return 0;
}
