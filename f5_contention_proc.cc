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
#define MAX_THREAD 32
unsigned long time_trials[NUM_TRIAL];
const long long block_size = 4096;
const long long buffer_size = 8388608; // 8M * 32 = 256M, manageable
const long long max_file_size = 16777216;
pthread_barrier_t barrier;
struct thread_params {
  unsigned long long overhead_block;
  int i;
};

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


  RESET_CCNT;
  GET_CCNT(time1);
  for (size_t i = 0; i < file_size; i += buffer_size) {
    read(fd, data, buffer_size);
  }
  GET_CCNT(time2);
  close(fd);
  free(data);

  // unsigned long time_block = (time2 - time1) / file_size * block_size;
  // std::cout << params->i << ": (" << time2 << ", " << time1 << ") -> " <<time_block << std::endl;
  unsigned long overhead_block = (time2 - time1) / file_size * block_size;
  std::cout << sequence << ": " << overhead_block << std::endl;
  write(pout[1], &overhead_block, sizeof(unsigned long));

  close(pout[1]);
}


int main() {
  int pin[2], pout[2];
  pipe(pin);
  pipe(pout);
  for (int count = 1; count <= MAX_THREAD; ++count) {
    for (int i = 0; i < count; ++i) {
      int pid = fork();
      if (!pid) { // child process
        child_proc(i, pin, pout);
        exit(EXIT_SUCCESS);
      }
    }


// Only parent process can reach here.
    close(pout[1]);
    close(pin[0]);
    unsigned long overhead = 0;
    char dummy[] = "g";
    unsigned long overhead_proc;
    for (int i = 0; i < count; ++i) {
      write(pin[1], &dummy, 1);
    }
    for (int i = 0; i < count; ++i) {
      read(pout[0], &overhead_proc, sizeof(unsigned long));
      std::cout << i << ": " << overhead_proc << std::endl;
      overhead += overhead_proc;
    }

    for (int i = 0; i < count; ++i) {
      wait(NULL);
    }
    close(pin[1]);
    close(pout[0]);
    std::cout << count << " processes: cycles per block: " << overhead / count << " speed: " << block_size * count * 7e8 / overhead / 1024 << "kB/s"<< std::endl;
  }
  return 0;
}