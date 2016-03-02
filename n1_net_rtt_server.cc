#include "utils_tcp.h"
#include "utils.h"
#include <assert.h>

#define PORT "3490"  // the port users will be connecting to
#define MAXDATASIZE 100 // max number of bytes we can get at once

int main(void) {
    int client_fd;
    int num_bytes;

    // bind to port
    char port[] = PORT;
    char buf[MAXDATASIZE];
    int sockfd = tcp_server_bind(port);

    // accept client connection
    while (1) {
        // get incoming connection
        client_fd = tcp_server_accept(sockfd);
        if (client_fd == -1) {
            continue;
        } else {
            break;
        }
    }

    num_bytes = tcp_receive(client_fd, buf);
    assert(num_bytes == 4);
    printf("received init packet\n");

    num_bytes = tcp_send(client_fd, MSG_INIT);
    assert(num_bytes == 4);
    printf("sent init packet\n");

    num_bytes = tcp_receive(client_fd, buf);
    assert(num_bytes == 4);
    printf("received init packet\n");

    num_bytes = tcp_send(client_fd, MSG_INIT);
    assert(num_bytes == 4);
    printf("sent init packet\n");

    tcp_shutdown_close(client_fd);
    tcp_shutdown_close(sockfd);

    return 0;
}
