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
    struct sockaddr_storage their_addr; // connector's address information
    char s[INET6_ADDRSTRLEN];
    socklen_t sin_size;

    // hello message
    char hello_message[] = "Hello, world!";

    // bind to port
    char port[] = PORT;
    int sockfd = tcp_server_bind(port);

    while (1) { // main accept() loop
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
                  get_in_addr_server((struct sockaddr *)&their_addr),
                  s, sizeof s);
        printf("server: got connection from %s\n", s);

        if (!fork()) { // this is the child process
            close(sockfd); // child doesn't need the listener
            tcp_send(new_fd, hello_message);
            // if (send(new_fd, "Hello, world!", 13, 0) == -1)
            //     perror("send");
            close(new_fd);
            exit(0);
        }
        close(new_fd);  // parent doesn't need this
    }

    return 0;
}