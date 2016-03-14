#include "utils_tcp.h"
#include "utils.h"

#define PORT "3490"  // the port users will be connecting to

int main(void) {
    int client_fd;
    int num_bytes;

    // bind to port
    char port[] = PORT;
    char *recv_buf = (char *)malloc(sizeof(char) * MAX_DATA_SIZE);
    int sockfd = tcp_server_bind(port);

    while (1) {
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

        num_bytes = tcp_receive(client_fd, recv_buf);
        tcp_shutdown_close(client_fd);
        tcp_shutdown_close(sockfd);

        std::cout << "server setup, receive, teardown" << std::endl;

        if (num_bytes == GOODBYE_DATA_SIZE) {
            break;
        }
    }

    free(recv_buf);

    return 0;
}
