#include <unistd.h>
#include <sys/syscall.h>
#include "utils.h"
using namespace std;

int main() {
    RESET_CCNT;
    unsigned start;
    unsigned end;

    for (int i = 0; i < NUM_ITER; ++i) {
        GET_CCNT(start);
        getpid();
        GET_CCNT(end);
        time_total += end - start;
    }
    cout << 1. * time_total / NUM_ITER << endl;
    return 0;
}
