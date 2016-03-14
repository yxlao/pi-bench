#ifndef TCP_UTILS_H_
#define TCP_UTILS_H_

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
#include <sys/wait.h>
#include <signal.h>

#define MAX_DATA_SIZE 33554432  // 32MB
#define MAX_RTT_DATA_SIZE 1024
#define MAX_NUMMY_DATA_SIZE 32
#define GOODBYE_DATA_SIZE 71
#define STATE_INIT 1
#define STATE_RUN  2
#define STATE_BYE  3
#define BACKLOG 10 // how many pending connections queue will hold, for server

extern char MSG_INIT[];
extern char MSG_EMPTY[];

// basic funtions
int tcp_send(int sockfd, char *buf);
// int tcp_simple_send(int sockfd, char *buf);
void tcp_fork_and_send(int sockfd, int new_fd, char *buf);
int tcp_receive(int sockfd, char *buf);
// int tcp_simple_receive(int sockfd, char *buf);
void tcp_close(int sockfd);
void tcp_shutdown_close(int sockfd);

// server
int tcp_server_bind(char *port);
int tcp_server_accept(int sockfd);

// client
int tcp_client_connect(char *addr, char *port);

#endif