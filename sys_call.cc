#include <iostream>
#include <unistd.h>
#include "cycles.h"
using namespace std;

int main() {
    RESET;
    int temp;
    unsigned start;
    unsigned end;
    unsigned total = 0;
    for (int i = 0; i < 1000000; ++i) {
        GET_CCNT(start);
        temp = getpid();
        GET_CCNT(end);
        total += end - start;
    }
    cout << temp << endl;
    cout << "average: " << 1. * total / 1000000 << endl;
    return 0;
}
