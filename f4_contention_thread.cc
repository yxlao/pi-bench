#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h> // for fstat
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

pthread_barrier_t barrier;
struct thread_params {
  long long overhead_block;
  int i;
};

void* file_read_thread(void* void_params) {
  thread_params* params = (thread_params*) void_params;
  int page_size = sysconf(_SC_PAGESIZE);
  long* data;
  long long time1, time2;

  char filename[50];
  sprintf(filename, "/home/pi/contention_%d", params->i);
  int fd = open(filename, O_RDONLY | O_DIRECT);
  struct stat s;
  fstat (fd, & s);
  size_t file_size = s.st_size;

  posix_memalign((void**) &data, page_size, file_size);

  pthread_barrier_wait(&barrier);

  RESET_CCNT;
  GET_CCNT(time1);
  read(fd, data, file_size);
  GET_CCNT(time2);
  close(fd);
  free(data);

  params->overhead_block = (time2 - time1) * block_size / file_size;

  return NULL;
}


int main() {
  for (int count = 1; count <= MAX_THREAD; ++count) {
    pthread_t* threads = (pthread_t*) calloc( count, sizeof(pthread_t) );
    pthread_barrier_init(&barrier, NULL, count);
    thread_params* arr_params = (thread_params*) calloc( count, sizeof(thread_params) );

    for (int i = 0; i < count; ++i) {
      arr_params[i].overhead_block = 0;
      arr_params[i].i = i;
      pthread_create(&(threads[i]), NULL, file_read_thread, (void*) (&(arr_params[i])));
    }

    long long overhead = 0;
    for (int i = 0; i < count; ++i) {
      pthread_join(threads[i], NULL);
      overhead += arr_params[i].overhead_block;
    }

    free( threads );
    free( arr_params );

    std::cout << count << " threads: cycles per block: " << overhead / count << std::endl;
  }
  return 0;
}