#include "utils_tcp.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#define PORT "3490" // the port client will be connecting to
#define NUM_TRIAL  10000
#define NUM_ITER   1
#define NUM_UNROLL 1
unsigned long setup_time_trials[NUM_TRIAL];
unsigned long teardown_time_trials[NUM_TRIAL];

// get sockaddr, IPv4 or IPv6:
void *get_in_addr_safe(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// client connect to addr and port
int tcp_client_connect_with_time(char *addr, char *port) {
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
        GET_CCNT(time_start);
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("client: connect");
            continue;
        }
        GET_CCNT(time_end);
        break;
    }

    if (p == NULL) {
        fprintf(stderr, "client: failed to connect\n");
        return 2;
    }

    inet_ntop(p->ai_family, get_in_addr_safe((struct sockaddr *)p->ai_addr),
              s, sizeof s);
    printf("client: connecting to %s\n", s);

    freeaddrinfo(servinfo);
    return sockfd;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "usage: client hostname\n");
        exit(1);
    }

    // int num_bytes;
    char port[] = PORT;
    char *send_buf = (char *)malloc(sizeof(char) * MAX_DATA_SIZE);

    // connect tcp
    int server_fd;

    // set message size in bytes
    int size = 16;
    memset(send_buf, '-', size);
    send_buf[size] = '\0';

    for (int i = 0; i < NUM_TRIAL; ++i) {
        // setup
        RESET_CCNT;
        // GET_CCNT(time_start);
        server_fd = tcp_client_connect_with_time(argv[1], port);
        // GET_CCNT(time_end);
        setup_time_trials[i] = time_end - time_start;

        // send dummy packet
        tcp_send(server_fd, send_buf);

        // teardown time
        RESET_CCNT;
        GET_CCNT(time_start);
        tcp_shutdown_close(server_fd);
        GET_CCNT(time_end);
        teardown_time_trials[i] = time_end - time_start;

        // print
        printf("trail %d\n", i);
    }
    std::cout << "#### size: " << size << std::endl;

    // say goodbye
    size = GOODBYE_DATA_SIZE;
    memset(send_buf, '-', size);
    send_buf[size] = '\0';
    server_fd = tcp_client_connect(argv[1], port);
    tcp_send(server_fd, send_buf);
    tcp_shutdown_close(server_fd);

    // print stats
    print_all_stats(setup_time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);
    print_all_stats(teardown_time_trials, NUM_TRIAL, NUM_ITER, NUM_UNROLL);

    // clean up
    free(send_buf);
    return 0;
}
