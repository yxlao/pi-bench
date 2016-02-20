#include "utils.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // for sync, write, and close


int main(int argc, char *argv[]){
    int fd = open("/home/pi/page_file.img", O_RDONLY);
    struct stat s;
    fstat (fd, & s);
    size_t size = s.st_size;
    std::cout << "size of file: " << size << std::endl;
    char* data = (char*) mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);
    int x;

    std::cout << "address of data: " << (unsigned long) data << std::endl;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        RESET_CCNT;
        GET_CCNT(time_start);
        //Loop on mem size
        for (unsigned j = 0, i1; i1 < 1; j += 40960, ++i1 ){
            x += data[j];
        }
        GET_CCNT(time_end);

        int fd2;
        char* data = "3";

        sync();
        fd2 = open("/proc/sys/vm/drop_caches", O_WRONLY);
        write(fd2, data, sizeof(char));
        close(fd2);

        time_trials[i] = time_end - time_start;
        if (i < 10)
            std::cout << time_trials[i] << std::endl;
    }
    std::cout << "x = " << x << std::endl;
    std::cout << "## Page fault " << std::endl;
    print_all_stats(time_trials, NUM_TRIAL, 1, 1);
    return 0;
}
