#ifndef TCP_UTILS_H_
#define TCP_UTILS_H_

#define MAX_DATA_SIZE 2048
#define MAX_TRIAL_DATA_SIZE 16
#define STATE_INIT 1
#define STATE_RUN  2
#define STATE_BYE  3
#define BACKLOG 10 // how many pending connections queue will hold, for server

extern char MSG_INIT[];
extern char MSG_EMPTY[];

// basic funtions
int tcp_send(int sockfd, char *buf);
void tcp_fork_and_send(int sockfd, int new_fd, char *buf);
int tcp_receive(int sockfd, char *buf);
void tcp_close(int sockfd);
void tcp_shutdown_close(int sockfd);

// server
int tcp_server_bind(char *port);
int tcp_server_accept(int sockfd);

// client
int tcp_client_connect(char *addr, char *port);

#endif