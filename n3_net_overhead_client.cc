#include "utils_tcp.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#define PORT "3490" // the port client will be connecting to
#define NUM_TRIAL  1
#define NUM_ITER   1
#define NUM_UNROLL 1
unsigned long setup_time_trials[NUM_TRIAL];
unsigned long teardown_time_trials[NUM_TRIAL];

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: client hostname\n");
        exit(1);
    }

    // int num_bytes;
    char port[] = PORT;
    char *send_buf = (char *)malloc(sizeof(char) * MAX_DATA_SIZE);

    // connect tcp
    int server_fd;

    // set message size in bytes
    int size = 16;
    memset(send_buf, '-', size);
    send_buf[size] = '\0';

    for (int i = 0; i < NUM_TRIAL; ++i) {
        // setup
        RESET_CCNT;
        GET_CCNT(time_start);
        server_fd = tcp_client_connect(argv[1], port);
        GET_CCNT(time_end);
        setup_time_trials[i] = time_end - time_start;

        // send dummy packet
        tcp_send(server_fd, send_buf);

        // teardown time
        RESET_CCNT;
        GET_CCNT(time_start);
        tcp_shutdown_close(server_fd);
        GET_CCNT(time_end);
        teardown_time_trials[i] = time_end - time_start;

        // print
        printf("trail %d\n", i);
    }
    std::cout << "#### size: " << size << std::endl;

    // say goodbye
    size = GOODBYE_DATA_SIZE;
    memset(send_buf, '-', size);
    send_buf[size] = '\0';
    server_fd = tcp_client_connect(argv[1], port);
    tcp_send(server_fd, send_buf);
    tcp_shutdown_close(server_fd);
    
    // print stats
    print_all_stats(setup_time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);
    print_all_stats(teardown_time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);

    // clean up
    free(send_buf);
    return 0;
}
