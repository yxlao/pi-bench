#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h> // for fstat
#include <sys/wait.h> // for wait
#include <fcntl.h>
#include <stdlib.h> // for posix_memalign
#include <unistd.h> // for sync, write, sysconf and close
#include <pthread.h>
#include "utils.h"
// experiment repetitions
#define NUM_TRIAL 100
#define MAX_COUNT 32
unsigned long time_trials[NUM_TRIAL];
const long long block_size = 4096;
size_t buffer_size = 8388608; // 8M * 32 = 256M, manageable
// size_t buffer_size = block_size; // match block_size;
size_t max_file_size = 16777216;

void child_proc(int sequence, int* pin, int* pout) { // pd = pipe_descriptor
  int page_size = sysconf(_SC_PAGESIZE);
  long* data;
  unsigned long time1, time2;

  char filename[50];
  sprintf(filename, "/home/pi/contention_%d", sequence);
  int fd = open(filename, O_RDONLY | O_DIRECT);
  struct stat s;
  fstat (fd, & s);
  size_t file_size = s.st_size;
  if (file_size > max_file_size) {
    file_size = max_file_size;
  }
  posix_memalign((void**) &data, page_size, buffer_size);
  close(pin[1]);
  close(pout[0]);
  read(pin[0], NULL, 1);
  close(pin[0]);
  // RESET_CCNT;
  GET_LOW_CCNT(time1);
  for (size_t i = 0; i < file_size; i += buffer_size) {
  // for (size_t i = file_size - buffer_size; i > 0; i -= buffer_size) {
    read(fd, data, buffer_size);
  }
  GET_LOW_CCNT(time2);
  close(fd);
  free(data);

  // unsigned long time_block = (time2 - time1) / file_size * block_size;
  // std::cout << params->i << ": (" << time2 << ", " << time1 << ") -> " <<time_block << std::endl;
  unsigned long overhead_block = (time2 - time1) * block_size / file_size;
  write(pout[1], &overhead_block, sizeof(unsigned long));
  close(pout[1]);
}


int main() {
  int file_no = 0;
  for (int count = 1; count <= MAX_COUNT; ++count) {
    int pin[2], pout[2];
    pipe(pin);
    pipe(pout);
    for (int i = 0; i < count; ++i) {
      int pid = fork();
      // for (buffer_size = 8 * 1048576; buffer_size < 128 * 1048576 && buffer_size * count < 256 * 1048576; buffer_size <<= 1);
      // if (buffer_size > 16777216) {
      //   max_file_size = buffer_size;
      // }
      if (!pid) { // child process
        child_proc(file_no, pin, pout);
        exit(EXIT_SUCCESS);
      }
      file_no = (file_no + 1) % 64;
    }

// Only parent process can reach here.
    close(pout[1]);
    close(pin[0]);
    unsigned long overhead = 0;
    char dummy[] = "11111111111111111111111111111111";
    unsigned long overhead_proc;
    RESET_CCNT;
    write(pin[1], &dummy, count);
    for (int i = 0; i < count; ++i) {
      read(pout[0], &overhead_proc, sizeof(unsigned long));
      overhead += overhead_proc;
    }

    for (int i = 0; i < count; ++i) {
      wait(NULL);
    }
    std::cout << " #proc, #cycles, speed/block/thread: " << count << "\t" << overhead / count << "\t" << block_size * count * 7e8 / 64 / overhead / 1024 << " kB/s"<< std::endl;
    close(pin[1]);
    close(pout[0]);
  }


  return 0;
}