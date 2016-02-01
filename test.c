#include "raspbian-ccr/cycles.c"
#include <stdio.h>

int main() {
    for (int i = 0; i < 100; ++i) {
        ccnt_init();
        for (int j = 0; j < 100; ++j);
        printf("%d\n", ccnt_read());
    }
    return 0;
}
