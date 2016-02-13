#include <iostream>
#include "utils.h"
using namespace std;

int main() {
    // ccnt_clr();
    RESET_CCNT;
    for (int i = 0; i < 1000000; ++i) {
        GET_CCNT(time_start);
        GET_CCNT(time_end);
        time_total += time_end - time_start;
    }
    cout << 1. * time_total / 1000000 << endl;
    return 0;
}
