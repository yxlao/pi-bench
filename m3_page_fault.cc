#include "utils.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[]){
    int x;
    char * data;
    int fd = open("/home/pi/page_file.img", O_RDONLY);
    struct stat s;
    fstat (fd, & s);
    size_t size = s.st_size;
    std::cout << "size of file: " << size << std::endl;
    data = (char*) mmap(0, size, PROT_READ, MAP_PRIVATE, fd, 0);

    std::cout << "number of iterations: " << NUM_ITER << std::endl;
    for (int i = 0; i < NUM_TRIAL; ++i) {
        RESET_CCNT;
        GET_CCNT(time_start);
        //Loop on mem size
        for (unsigned j = 0, i1; i1 < NUM_ITER; j += 1048576, ++i1 ){
            x += data[j];
        }
        GET_CCNT(time_end);
        time_trials[i] = time_end - time_start;
    }
    std::cout << "x = " << x << std::endl;
    std::cout << "## Page fault " << std::endl;
    print_all_stats(time_trials, NUM_TRIAL, NUM_ITER, 1);
    return 0;
}
