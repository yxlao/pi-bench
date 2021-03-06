#include "utils.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // for sync, write, sysconf and close
#include <fstream> // for ofstream

// experiment repetitions
#define NUM_TRIAL  10000
#define NUM_ITER   1
#define NUM_UNROLL 1
unsigned long time_trials[NUM_TRIAL];

int main(int argc, char *argv[]) {
    int fd = open("/home/pi/random.img", O_RDONLY);
    struct stat s;
    fstat (fd, & s);
    size_t size = s.st_size;
    std::cout << "size of file: " << size << std::endl;
    char* data = (char*) mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);
    int x = 123;

    int j = size - 1;
    int i;
    long page_size = sysconf(_SC_PAGESIZE);
    std::cout << "page size: " << page_size << " address of data: " << (unsigned long) data << std::endl;
    for (i = 0; i < NUM_TRIAL && j >= 0; ++i) {
        RESET_CCNT;
        GET_CCNT(time_start);
        //Loop on mem size
        x += data[j];
        GET_CCNT(time_end);
        j -= 524288;

        // int fd2;
        // char const* data = "3";

        // sync();
        // fd2 = open("/proc/sys/vm/drop_caches", O_WRONLY);
        // write(fd2, data, sizeof(char));
        // close(fd2);

        time_trials[i] = time_end - time_start;
        // if (i < 100)
        //     std::cout << time_trials[i] << std::endl;
    }
    std::cout << "x = " << x << std::endl;
    std::cout << "## Page fault " << std::endl;

    std::ofstream ofs;
    ofs.open ("m3_output.txt", std::ofstream::out | std::ofstream::app);
    for (int k = 0; k < i; ++k) {
        ofs << time_trials[k] << std::endl;
    }

    ofs.close();

    print_all_stats(time_trials, i, NUM_ITER, NUM_UNROLL);
    return 0;
}
