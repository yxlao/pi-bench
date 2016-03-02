#include "utils_tcp.h"
#include "utils.h"

#define PORT "3490"  // the port users will be connecting to

int main(void) {
    int new_fd;

    // bind to port
    char port[] = PORT;
    int sockfd = tcp_server_bind(port);

    while (1) {
        // get incoming connection
        new_fd = tcp_server_accept(sockfd);
        if (new_fd == -1) {
            continue;
        } else {
            break;
        }
    }

    // chlid send message
    tcp_send(new_fd, MSG_INIT);

    // parent clean up
    tcp_shutdown_close(new_fd);
    tcp_shutdown_close(sockfd);

    return 0;
}
