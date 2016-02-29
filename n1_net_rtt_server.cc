#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include "utils_tcp.h"
#include "utils.h"

#define PORT "3490"  // the port users will be connecting to

// get sockaddr, IPv4 or IPv6:
void *get_in_addr_server(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

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
        if (!fork()) { // this is the child process
            tcp_close(sockfd); // child doesn't need the listener
            tcp_send(new_fd, hello_message);
            tcp_close(new_fd);
            exit(0);
        }

        // parent clean up
        tcp_close(new_fd);
    }

    return 0;
}