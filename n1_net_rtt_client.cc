#include "utils_tcp.h"
#include "utils.h"
#include <unistd.h> // for sleep
#include <assert.h>
#include <string.h>

#define PORT "3490" // the port client will be connecting to
#define MAXDATASIZE 100 // max number of bytes we can get at once


int main(int argc, char *argv[]) {
    // check args
    if (argc != 2) {
        fprintf(stderr, "usage: client hostname\n");
        exit(1);
    }

    int num_bytes;
    char port[] = PORT;
    char buf[MAXDATASIZE];
    unsigned int microseconds = 1000000;

    // connect tcp
    int server_fd = tcp_client_connect(argv[1], port);

    num_bytes = tcp_send(server_fd, MSG_INIT);
    assert(num_bytes == 4);
    printf("sent init packet\n");

    num_bytes = tcp_receive(server_fd, buf);
    assert(num_bytes == 4);
    printf("received init packet\n");

    num_bytes = tcp_send(server_fd, MSG_INIT);
    assert(num_bytes == 4);
    printf("sent init packet\n");

    num_bytes = tcp_receive(server_fd, buf);
    assert(num_bytes == 4);
    printf("received init packet\n");

    tcp_shutdown_close(server_fd);

    return 0;
}
