#include "utils_tcp.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#define PORT "3490" // the port client will be connecting to
#define NUM_TRIAL  100
#define NUM_ITER   20
#define NUM_UNROLL 5
unsigned long time_trials[NUM_TRIAL];

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: client hostname\n");
        exit(1);
    }

    // int num_bytes;
    char port[] = PORT;
    char *send_buf = (char *)malloc(sizeof(char) * MAX_DATA_SIZE);
    char *recv_buf = (char *)malloc(sizeof(char) * MAX_DATA_SIZE);

    // struct timeval tval_before, tval_after, tval_result;
    struct timeval tval_start, tval_end;
    unsigned long tval_diff;
    double bytes_per_sec;

    // connect tcp
    int server_fd = tcp_client_connect(argv[1], port);

    // set message size in bytes
    int size = 1024 * 256;

    // memset bytes to create string length size
    memset(send_buf, '-', size);
    send_buf[size] = '\0';

    for (int i = 0; i < NUM_TRIAL; ++i) {
        gettimeofday(&tval_start, NULL);
        for (int j = 0; j < NUM_ITER / 2; ++j) {
            tcp_send(server_fd, send_buf);
            tcp_receive(server_fd, recv_buf);
            tcp_send(server_fd, send_buf);
            tcp_receive(server_fd, recv_buf);
            tcp_send(server_fd, send_buf);
            tcp_receive(server_fd, recv_buf);
            tcp_send(server_fd, send_buf);
            tcp_receive(server_fd, recv_buf);
            tcp_send(server_fd, send_buf);
            tcp_receive(server_fd, recv_buf);
        }
        gettimeofday(&tval_end, NULL);
        // convert time diff in usec directly to bandwidth
        tval_diff = tval_diff_to_usec(tval_start, tval_end);
        bytes_per_sec = (double) size * (double) NUM_ITER * (double) NUM_UNROLL
                        / (double) tval_diff * (double) 1000000;
        printf("tval_diff: %lu, bytes_per_sec: %f\n", tval_diff, bytes_per_sec);
        // save it in time_trials
        time_trials[i] = (unsigned long) bytes_per_sec;
        printf("trail %d\n", i);
    }
    std::cout << "#### size: " << size << std::endl;
    // a HACK for outputing the time correctly, set both to 1
    print_all_stats(time_trials, NUM_TRIAL, 1, 1);

    tcp_shutdown_close(server_fd);

    free(send_buf);
    free(recv_buf);

    return 0;
}
