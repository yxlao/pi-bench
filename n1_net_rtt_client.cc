#include "utils_tcp.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h> // for sleep
#include <assert.h>
#include <string.h>

#define PORT "3490" // the port client will be connecting to

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: client hostname\n");
        exit(1);
    }

    int num_bytes;
    char port[] = PORT;
    char send_buf[MAX_DATA_SIZE];
    char recv_buf[MAX_DATA_SIZE];

    // connect tcp
    int server_fd = tcp_client_connect(argv[1], port);


    for (int s = 1; s <= MAX_RTT_DATA_SIZE; s = s * 2) {
        // memset bytes to create string length s
        memset(send_buf, '-', MAX_DATA_SIZE);
        send_buf[s] = '\0';

        num_bytes = tcp_send(server_fd, send_buf);
        printf("sent size %d\n", num_bytes);
        assert(num_bytes == s);

        num_bytes = tcp_receive(server_fd, recv_buf);
        printf("received size %d\n", num_bytes);
        assert(num_bytes == s);
    }

    tcp_shutdown_close(server_fd);

    return 0;
}
