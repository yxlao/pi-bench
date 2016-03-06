#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"
// experiment repetitions
#define NUM_TRIAL 100
unsigned long time_trials[NUM_TRIAL];
using namespace std;

#define MAX_INT_ARRAY_SIZE 16777216 / 2 // 32M Bytes
#define CACHE_FLUSH_SIZE 4194304 / 4
#define BLOCK_SIZE 4096

void file_read_thread(int n, int) {

}

int main() {
    return 0;
}