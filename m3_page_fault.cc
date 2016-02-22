#include "utils.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include "utils.h"
#include <unistd.h> // for sync, write, and close
#include <fstream>

int main(int argc, char *argv[]){
    // random number
    time_t t;
    srand((unsigned)time(&t));

    // open file and test size
    int fd = open("/home/pi/page_file.img", O_RDONLY);
    struct stat s;
    fstat (fd, & s);
    size_t size = s.st_size;
    std::cout << "size of file: " << size << std::endl;
    char* data = (char*) mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);

    std::cout << "address of data: " << (unsigned long) data << std::endl;

    unsigned addr;
    int temp;
    int i = 0;
    for (i = 0; i < 1000; ++i) {
        addr = (unsigned) ((float)rand() / (float)RAND_MAX * (float) size);

        RESET_CCNT;
        GET_CCNT(time_start);
        temp += data[addr];
        GET_CCNT(time_end);

        int fdx;
        char* datax = "3";
        sync();
        fdx = open("/proc/sys/vm/drop_caches", O_WRONLY);
        write(fdx, datax, sizeof(char));
        close(fdx);

        time_trials[i] = time_end - time_start;
        std::cout << time_trials[i] << std::endl;
    }
    close(fd);

    std::ofstream ofs;

    ofs.open ("m3_output.txt", std::ofstream::out | std::ofstream::app);
    for (int k = 0; k < i; ++k) {
    ofs << time_trials[k] << std::endl;
    }
    ofs.close();

    std::cout << "x = " << temp << std::endl;
    std::cout << "## Page fault " << std::endl;
    print_all_stats(time_trials, i, 1, 1);
    return 0;
}
