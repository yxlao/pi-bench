#include "utils_tcp.h"
#include "utils.h"

#define PORT "3490"  // the port users will be connecting to

int main(void) {
    int new_fd;

    // hello message
    char hello_message[] = "Hello, world!";

    // bind to port
    char port[] = PORT;
    int sockfd = tcp_server_bind(port);

    while (1) {
        // get incoming connection
        new_fd = tcp_server_accept(sockfd);
        if (new_fd == -1) {
            continue;
        }

        // chlid send message
        tcp_fork_and_send(sockfd, new_fd, hello_message);

        // parent clean up
        tcp_close(new_fd);
    }

    return 0;
}
