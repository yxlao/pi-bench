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

    while (1) {
        // read(client_fd, &recv_buf,1);
        // write(client_fd,"-",1);
        num_bytes = tcp_receive(client_fd, recv_buf);
        // printf("received size %d\n", num_bytes);
        // num_bytes = tcp_send(client_fd, recv_buf);
        // printf("sent size %d\n", num_bytes);
        if (num_bytes == 0) { // client is offline
            break;
        }
    }

    tcp_shutdown_close(client_fd);
    tcp_shutdown_close(sockfd);

    free(recv_buf);

    return 0;
}
