#include <iostream>
#include <unistd.h>
#include <sys/syscall.h>
#include "cycles.h"
using namespace std;

int main() {
    RESET;
    unsigned start;
    unsigned end;
    unsigned total = 0;
    for (int i = 0; i < STD_ITER; ++i) {
        GET_CCNT(start);
        getpid();
        GET_CCNT(end);
        total += end - start;
    }
    cout << 1. * total / STD_ITER << endl;
    return 0;
}
