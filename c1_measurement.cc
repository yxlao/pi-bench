#include <iostream>
#include "utils.h"
using namespace std;

int main() {
    // ccnt_clr();
    RESET_CCNT;
    unsigned start;
    unsigned end;
    unsigned total = 0;
    for (int i = 0; i < 1000000; ++i) {
        GET_CCNT(start);
        GET_CCNT(end);
        total += end - start;
    }
    cout << 1. * total / 1000000 << endl;
    return 0;
}
