#include <iostream>
// #include "raspbian-ccr/cycles.c"
#include "cycles.h"
// #include <cstdint>
using namespace std;

int main() {
    // ccnt_clr();
    RESET;
    unsigned start;
    unsigned end;
    unsigned total = 0;
    for (int i = 0; i < 1000000; ++i) {
        GET_CCNT(start);
        GET_CCNT(end);
        total += end - start;
        // cout << start << "," << end << "," << end - start << endl;
    }
    cout << "average: " << 1. * total / 1000000 << endl;
    return 0;
}
