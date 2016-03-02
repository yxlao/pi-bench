#include "utils_tcp.h"
#include "utils.h"

#define PORT "3490"  // the port users will be connecting to

int main(void) {
    int client_fd;

    // bind to port
    char port[] = PORT;
    int sockfd = tcp_server_bind(port);

    while (1) {
        // get incoming connection
        client_fd = tcp_server_accept(sockfd);
        if (client_fd == -1) {
            continue;
        } else {
            break;
        }
    }

    // chlid send message
    tcp_send(client_fd, MSG_INIT);

    // parent clean up
    tcp_shutdown_close(client_fd);
    tcp_shutdown_close(sockfd);

    return 0;
}
