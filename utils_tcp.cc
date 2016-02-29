#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>      // POSIX library
#include <errno.h>       // error Number, variable errno
#include <netdb.h>       // network database
#include <sys/types.h>   // system datatypes, like pthread
#include <netinet/in.h>  // internet address family, sockaddr_in, in_addr
#include <sys/socket.h>  // socket library
#include <arpa/inet.h>   // internet operations, in_addr_t, in_addr
#include "utils_tcp.h"

void tcp_send(int sockfd, char *buf) {
    int len, numbytes;
    len = strlen(buf);
    if ((numbytes = send(sockfd, buf, len, 0)) == -1) {
        perror("send");
        exit(1);
    }
    if (numbytes != len) {
        fprintf(stderr, "send: sending incomplete\n");
    }
}

int tcp_receive(int sockfd, char *buf) {
    int numbytes = -1;
    if ((numbytes = recv(sockfd, buf, MAX_PACKET_SIZE - 1, 0)) == -1) {
        perror("recv");
        exit(1);
    }
    buf[numbytes] = '\0';
    return numbytes;
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int tcp_connect(char *addr, char *port) {
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    int status;
    char s[INET6_ADDRSTRLEN];

    // set hints to the desired value, and get struct addrinfo
    memset(&hints, 0, sizeof hints); // memset does not allocate memory
    hints.ai_family = AF_UNSPEC; // don't care IsockfdPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; // TCP stream socket
    hints.ai_flags = AI_PASSIVE; // fill in my IP automatically

    // set up connection
    if ((status = getaddrinfo(addr, port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    // loop through all and connect to the first one
    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("client: socket");
            continue;
        }
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }
        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr),
              s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo);
    return sockfd;
}

void tcp_close(int sockfd) {
    shutdown(sockfd, SHUT_RDWR);
    close(sockfd);
}