#ifndef TCP_UTILS_H_
#define TCP_UTILS_H_

#define MAX_PACKET_SIZE 1024

void tcp_send(int sockfd, void* buf);
int tcp_receive(int sockfd, char *buf);
int tcp_connect (char *addr, char *port);
void tcp_close(int sockfd);

#endif