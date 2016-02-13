#include <iostream>
#include <unistd.h>
#include <sys/syscall.h>
#include "utils.h"
using namespace std;

int main() {
    RESET_CCNT;
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
