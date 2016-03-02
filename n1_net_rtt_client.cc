#include "utils_tcp.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h> // for sleep
#include <assert.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define PORT "3490" // the port client will be connecting to
#define NUM_TRIAL  100
#define NUM_ITER   2
#define NUM_UNROLL 5
unsigned long time_trials[NUM_TRIAL];

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: client hostname\n");
        exit(1);
    }

    // int num_bytes;
    char port[] = PORT;
    char send_buf[MAX_DATA_SIZE];
    char recv_buf[MAX_DATA_SIZE];

    // connect tcp
    int server_fd = tcp_client_connect(argv[1], port);

    for (int size = 1; size <= MAX_RTT_DATA_SIZE; size = size * 2) {
        // memset bytes to create string length size
        memset(send_buf, '-', MAX_DATA_SIZE);
        send_buf[size] = '\0';

        for (int i = 0; i < NUM_TRIAL; ++i) {
            RESET_CCNT;
            GET_CCNT(time_start);
            for (int j = 0; j < NUM_ITER; ++j) {
                write(server_fd,"-",1);
                read(server_fd,&recv_buf,1);
                write(server_fd,"-",1);
                read(server_fd,&recv_buf,1);
                write(server_fd,"-",1);
                read(server_fd,&recv_buf,1);
                write(server_fd,"-",1);
                read(server_fd,&recv_buf,1);
                write(server_fd,"-",1);
                read(server_fd,&recv_buf,1);
                // tcp_send(server_fd, send_buf);
                // tcp_receive(server_fd, recv_buf);
                // tcp_send(server_fd, send_buf);
                // tcp_receive(server_fd, recv_buf);
                // tcp_send(server_fd, send_buf);
                // tcp_receive(server_fd, recv_buf);
                // tcp_send(server_fd, send_buf);
                // tcp_receive(server_fd, recv_buf);
                // tcp_send(server_fd, send_buf);
                // tcp_receive(server_fd, recv_buf);
            }
            GET_CCNT(time_end);
            time_trials[i] = time_end - time_start;
        }
        std::cout << "#### size: " << size << std::endl;
        print_all_stats(time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);

        // num_bytes = tcp_send(server_fd, send_buf);
        // printf("sent size %d\n", num_bytes);
        // assert(num_bytes == size);
        // num_bytes = tcp_receive(server_fd, recv_buf);
        // printf("received size %d\n", num_bytes);
        // assert(num_bytes == size);
    }

    tcp_shutdown_close(server_fd);

    return 0;
}
