#ifndef TCP_UTILS_H_
#define TCP_UTILS_H_

#define MAX_PACKET_SIZE 1024
#define STATE_INIT 1
#define STATE_RUN  2
#define STATE_BYE  3

int tcp_send(int sockfd, char *buf);
int tcp_receive(int sockfd, char *buf);
int tcp_connect (char *addr, char *port);
void tcp_close(int sockfd);

#endif